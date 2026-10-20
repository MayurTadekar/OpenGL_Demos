// header files
#include "../../include/common.h"
#include "../../modules/Camera/Camera.h"
#include "Ocean.h"
#include <complex>
#include <cmath>

// -------------------------------------------------------------------
// FFT Ocean Config
// -------------------------------------------------------------------
#define OCEAN_GRID_FFT 128
const int N = OCEAN_GRID_FFT;
const int Nplus1 = N + 1;
const int VERTS = Nplus1 * Nplus1;
const int INDS  = N * N * 6;

typedef std::complex<double> Complex;

// Fast Fourier Transform logic adapted from reference
class cFFT {
public:
	unsigned int N_, which;
	unsigned int log_2_N;
	unsigned int* reversed;
	Complex** W;
	Complex* c[2];
	double pi2;

	cFFT(unsigned int N) : N_(N), reversed(0), W(0), pi2(2.0 * 3.14159265358979323846) {
		log_2_N = (unsigned int)(log(N) / log(2));
		reversed = new unsigned int[N];
		for (unsigned int i = 0; i < N; i++) reversed[i] = reverse(i);
		int pow2 = 1;
		W = new Complex *[log_2_N];
		for (unsigned int i = 0; i < log_2_N; i++) {
			W[i] = new Complex[pow2];
			for (int j = 0; j < pow2; j++) W[i][j] = Complex(cos(pi2 * j / (pow2 * 2)), sin(pi2 * j / (pow2 * 2)));
			pow2 *= 2;
		}
		c[0] = new Complex[N];
		c[1] = new Complex[N];
		which = 0;
	}

	~cFFT() {
		delete[] c[0]; delete[] c[1];
		for (unsigned int i = 0; i < log_2_N; i++) delete[] W[i];
		delete[] W;
		delete[] reversed;
	}

	unsigned int reverse(unsigned int i) {
		unsigned int res = 0;
		for (unsigned int j = 0; j < log_2_N; j++) {
			res = (res << 1) + (i & 1);
			i >>= 1;
		}
		return res;
	}

	void fft(Complex *input, Complex *output, int stride, int offset) {
		for (unsigned int i = 0; i < N_; i++) c[which][i] = input[reversed[i] * stride + offset];
		int loops = N_ >> 1;
		int size = 1 << 1;
		int size_over_2 = 1;
		int w_ = 0;
		for (unsigned int i = 1; i <= log_2_N; i++) {
			which ^= 1;
			for (int j = 0; j < loops; j++) {
				for (int k = 0; k < size_over_2; k++) {
					c[which][size * j + k] = c[which ^ 1][size * j + k] + c[which ^ 1][size * j + size_over_2 + k] * W[w_][k];
				}
				for (int k = size_over_2; k < size; k++) {
					c[which][size * j + k] = c[which ^ 1][size * j - size_over_2 + k] - c[which ^ 1][size * j + k] * W[w_][k - size_over_2];
				}
			}
			loops >>= 1; size <<= 1; size_over_2 <<= 1; w_++;
		}
		for (unsigned int i = 0; i < N_; i++) output[i * stride + offset] = c[which][i];
	}
};

struct vertex_ocean {
	GLfloat x, y, z;
	GLfloat nx, ny, nz;
	GLfloat u, v;
	GLfloat a, b;
	GLfloat _a, _b;
	GLfloat ox, oy, oz;
};

// -------------------------------------------------------------------
// Global variables
// -------------------------------------------------------------------
static GLuint shaderProgramObject    = 0;
static GLuint modelMatrixUniform     = 0;
static GLuint viewMatrixUniform      = 0;
static GLuint projectionMatrixUniform= 0;

static GLuint uDuDvSamplerUniform    = 0;
static GLuint uMoveFactorUniform     = 0;
static GLuint uWaveStrengthUniform   = 0;
static GLuint uTilingUniform         = 0;

static GLuint uShallowColorUniform       = 0;
static GLuint uDeepColorUniform          = 0;
static GLuint uColorBlendSharpnessUniform= 0;
static GLuint uFoamColorUniform          = 0;
static GLuint uFoamThresholdUniform      = 0;

static GLuint uLightDirUniform       = 0;
static GLuint uSpecularStrengthUniform= 0;
static GLuint uShininessUniform      = 0;
static GLuint uSunColorUniform       = 0;
static GLuint uCameraPositionUniform = 0;
static GLuint uSkyboxSamplerUniform  = 0;

static GLuint vao  = 0;
static GLuint vbo  = 0;
static GLuint ebo  = 0;

static GLuint g_dudvMapTexture    = 0;
static GLuint g_skyboxTexture     = 0;

static float g_oceanTime = 0.0f;

// CPU FFT Buffers
static vertex_ocean* vertices = nullptr;
static GLuint* indices = nullptr;
static Complex *h_tilde = nullptr, *h_tilde_slopex = nullptr, *h_tilde_slopez = nullptr, *h_tilde_dx = nullptr, *h_tilde_dz = nullptr;
static cFFT *fft = nullptr;
static float length_scale = 1000.0f; // Increased to match true OceanFFT physical domain scale
static float G_gravity = 9.81f;

static float prev_waveHeight = -1.0f;
static float prev_waveDir = -1.0f;
static float prev_tideSpeed = -1.0f;

// -------------------------------------------------------------------
// FFT Math Helpers
// -------------------------------------------------------------------
float uniformRandomVariable() {
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

Complex gaussianRandomVariable() {
	float x1, x2, w;
	do {
		x1 = 2.f * uniformRandomVariable() - 1.f;
		x2 = 2.f * uniformRandomVariable() - 1.f;
		w = x1 * x1 + x2 * x2;
	} while (w >= 1.f);
	w = sqrt((-2.f * log(w)) / w);
	return Complex(x1 * w, x2 * w);
}

float phillips(int n_prime, int m_prime, float A, vmath::vec2 w_wind) {
	vmath::vec2 k(M_PI * (2 * n_prime - N) / length_scale, M_PI * (2 * m_prime - N) / length_scale);
	float k_length = sqrt(k[0]*k[0] + k[1]*k[1]);
	if (k_length < 0.000001f) return 0.0f;

	float k_length2 = k_length * k_length;
	float k_length4 = k_length2 * k_length2;

	float w_len = sqrt(w_wind[0]*w_wind[0] + w_wind[1]*w_wind[1]);
	if (w_len < 0.000001f) return 0.0f;
	
	vmath::vec2 k_norm = vmath::vec2(k[0]/k_length, k[1]/k_length);
	vmath::vec2 w_norm = vmath::vec2(w_wind[0]/w_len, w_wind[1]/w_len);

	float k_dot_w = k_norm[0]*w_norm[0] + k_norm[1]*w_norm[1];
	float k_dot_w2 = k_dot_w * k_dot_w;

	float L = w_len * w_len / G_gravity;
	float L2 = L * L;
	float damping = 0.001f;
	float l2 = L2 * damping * damping;

	float phillips_value = A * exp(-1.0f / (k_length2 * L2)) / k_length4 * k_dot_w2 * exp(-k_length2 * l2);

	// Optional directional filtering: suppresses waves moving exactly against the wind
	if (k_dot_w < 0.0f)
		phillips_value *= 0.05f;

	return phillips_value;
}

Complex hTilde_0(int n_prime, int m_prime, float A, vmath::vec2 w_wind) {
	Complex r = gaussianRandomVariable();
	return r * sqrt(phillips(n_prime, m_prime, A, w_wind) / 2.0);
}

float dispersion(int n_prime, int m_prime) {
	float kx = (float)M_PI * (2 * n_prime - N) / length_scale;
	float kz = (float)M_PI * (2 * m_prime - N) / length_scale;
	return sqrt(G_gravity * sqrt(kx * kx + kz * kz));
}

void recalculate_hTilde_0(OceanParams& p) {
	float A = p.waveHeight * 1e-7f;
	float rad = p.waveDirectionAngle * (float)M_PI / 180.0f;
	float V = p.tideSpeed * 10.0f;
	vmath::vec2 w_wind(cos(rad) * V, sin(rad) * V);

	int index;
	for (int m_prime = 0; m_prime < Nplus1; m_prime++) {
		for (int n_prime = 0; n_prime < Nplus1; n_prime++) {
			index = m_prime * Nplus1 + n_prime;
			Complex ht0 = hTilde_0(n_prime, m_prime, A, w_wind);
			// CRITICAL FIX: The opposite wave vector of 'n' in a discrete grid is 'N - n', not '-n'!
			Complex ht0mk = std::conj(hTilde_0(N - n_prime, N - m_prime, A, w_wind));
			vertices[index].a = ht0.real();
			vertices[index].b = ht0.imag();
			vertices[index]._a = ht0mk.real();
			vertices[index]._b = ht0mk.imag();
		}
	}
}

void evaluateWavesFFT(float t, float lambda) {
	float kx, kz, len;
	int index, index1;

	// Populate un-transformed buffers
	for (int m_prime = 0; m_prime < N; m_prime++) {
		for (int n_prime = 0; n_prime < N; n_prime++) {
			kz = (float)M_PI * (2.0f * m_prime - N) / length_scale;
			kx = (float)M_PI * (2 * n_prime - N) / length_scale;
			len = sqrt(kx * kx + kz * kz);
			index = m_prime * N + n_prime;

			int vIdx = m_prime * Nplus1 + n_prime;
			Complex htilde0(vertices[vIdx].a, vertices[vIdx].b);
			Complex htilde0mkconj(vertices[vIdx]._a, vertices[vIdx]._b);
			float omegat = dispersion(n_prime, m_prime) * t;
			float cos_ = cos(omegat);
			float sin_ = sin(omegat);
			Complex c0(cos_, sin_);
			Complex c1(cos_, -sin_);
			h_tilde[index] = htilde0 * c0 + htilde0mkconj * c1;

			h_tilde_slopex[index] = h_tilde[index] * Complex(0, kx);
			h_tilde_slopez[index] = h_tilde[index] * Complex(0, kz);
			if (len < 0.000001f) {
				h_tilde_dx[index] = Complex(0.0f, 0.0f);
				h_tilde_dz[index] = Complex(0.0f, 0.0f);
			} else {
				h_tilde_dx[index] = h_tilde[index] * Complex(0, -kx / len);
				h_tilde_dz[index] = h_tilde[index] * Complex(0, -kz / len);
			}
		}
	}

	// 2D FFT
	for (int m_prime = 0; m_prime < N; m_prime++) {
		fft->fft(h_tilde, h_tilde, 1, m_prime * N);
		fft->fft(h_tilde_slopex, h_tilde_slopex, 1, m_prime * N);
		fft->fft(h_tilde_slopez, h_tilde_slopez, 1, m_prime * N);
		fft->fft(h_tilde_dx, h_tilde_dx, 1, m_prime * N);
		fft->fft(h_tilde_dz, h_tilde_dz, 1, m_prime * N);
	}
	for (int n_prime = 0; n_prime < N; n_prime++) {
		fft->fft(h_tilde, h_tilde, N, n_prime);
		fft->fft(h_tilde_slopex, h_tilde_slopex, N, n_prime);
		fft->fft(h_tilde_slopez, h_tilde_slopez, N, n_prime);
		fft->fft(h_tilde_dx, h_tilde_dx, N, n_prime);
		fft->fft(h_tilde_dz, h_tilde_dz, N, n_prime);
	}

	float signs[] = {1.0f, -1.0f};

	// Map FFT results to Grid Vertices (and normalize to [-1, 1])
	for (int m_prime = 0; m_prime < N; m_prime++) {
		for (int n_prime = 0; n_prime < N; n_prime++) {
			index = m_prime * N + n_prime;
			index1 = m_prime * Nplus1 + n_prime;
			int sign = (int)signs[(n_prime + m_prime) & 1];

			h_tilde[index] = h_tilde[index] * (double)sign;
			h_tilde_dx[index] = h_tilde_dx[index] * (double)sign;
			h_tilde_dz[index] = h_tilde_dz[index] * (double)sign;
			h_tilde_slopex[index] = h_tilde_slopex[index] * (double)sign;
			h_tilde_slopez[index] = h_tilde_slopez[index] * (double)sign;

			// Scale displacement to match the [-1, 1] rendering grid
			float sScale = 2.0f / length_scale;

			vertices[index1].y = (float)h_tilde[index].real() * sScale;
			vertices[index1].x = vertices[index1].ox + (float)h_tilde_dx[index].real() * lambda * sScale;
			vertices[index1].z = vertices[index1].oz + (float)h_tilde_dz[index].real() * lambda * sScale;

			vmath::vec3 n = vmath::normalize(vmath::vec3(0.0f - (float)h_tilde_slopex[index].real(), 1.0f, 0.0f - (float)h_tilde_slopez[index].real()));
			vertices[index1].nx = n[0];
			vertices[index1].ny = n[1];
			vertices[index1].nz = n[2];

			// Edge tiling wrap-around
			if (n_prime == 0 && m_prime == 0) {
				vertices[index1 + N + Nplus1 * N].y = vertices[index1].y;
				vertices[index1 + N + Nplus1 * N].x = vertices[index1 + N + Nplus1 * N].ox + (float)h_tilde_dx[index].real() * lambda * sScale;
				vertices[index1 + N + Nplus1 * N].z = vertices[index1 + N + Nplus1 * N].oz + (float)h_tilde_dz[index].real() * lambda * sScale;
				vertices[index1 + N + Nplus1 * N].nx = n[0]; vertices[index1 + N + Nplus1 * N].ny = n[1]; vertices[index1 + N + Nplus1 * N].nz = n[2];
			}
			if (n_prime == 0) {
				vertices[index1 + N].y = vertices[index1].y;
				vertices[index1 + N].x = vertices[index1 + N].ox + (float)h_tilde_dx[index].real() * lambda * sScale;
				vertices[index1 + N].z = vertices[index1 + N].oz + (float)h_tilde_dz[index].real() * lambda * sScale;
				vertices[index1 + N].nx = n[0]; vertices[index1 + N].ny = n[1]; vertices[index1 + N].nz = n[2];
			}
			if (m_prime == 0) {
				vertices[index1 + Nplus1 * N].y = vertices[index1].y;
				vertices[index1 + Nplus1 * N].x = vertices[index1 + Nplus1 * N].ox + (float)h_tilde_dx[index].real() * lambda * sScale;
				vertices[index1 + Nplus1 * N].z = vertices[index1 + Nplus1 * N].oz + (float)h_tilde_dz[index].real() * lambda * sScale;
				vertices[index1 + Nplus1 * N].nx = n[0]; vertices[index1 + Nplus1 * N].ny = n[1]; vertices[index1 + Nplus1 * N].nz = n[2];
			}
		}
	}
}

// -------------------------------------------------------------------
// initializeOcean
// -------------------------------------------------------------------
BOOL initializeOcean(GLuint dudvMapTexture, GLuint skyboxCubemapTexture)
{
	// Setup FFT variables
	h_tilde = new Complex[N * N];
	h_tilde_slopex = new Complex[N * N];
	h_tilde_slopez = new Complex[N * N];
	h_tilde_dx = new Complex[N * N];
	h_tilde_dz = new Complex[N * N];
	fft = new cFFT(N);
	vertices = new vertex_ocean[VERTS];
	indices = new GLuint[INDS];

	// Init grid
	int vi = 0;
	for (int m_prime = 0; m_prime < Nplus1; m_prime++) {
		for (int n_prime = 0; n_prime < Nplus1; n_prime++) {
			int index = m_prime * Nplus1 + n_prime;
			vertices[index].ox = vertices[index].x = (n_prime - N / 2.0f) * 2.0f / N;
			vertices[index].oy = vertices[index].y = 0.0f;
			vertices[index].oz = vertices[index].z = (m_prime - N / 2.0f) * 2.0f / N;
			vertices[index].nx = 0.0f;
			vertices[index].ny = 1.0f;
			vertices[index].nz = 0.0f;
			vertices[index].u = (float)n_prime / (float)N;
			vertices[index].v = (float)m_prime / (float)N;
			vertices[index].a = vertices[index].b = 0.0f;
			vertices[index]._a = vertices[index]._b = 0.0f;
		}
	}

	int ii = 0;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			GLuint tl = row       * Nplus1 + col;
			GLuint tr = row       * Nplus1 + col + 1;
			GLuint bl = (row + 1) * Nplus1 + col;
			GLuint br = (row + 1) * Nplus1 + col + 1;
			indices[ii++] = tl; indices[ii++] = bl; indices[ii++] = tr;
			indices[ii++] = tr; indices[ii++] = bl; indices[ii++] = br;
		}
	}

	// -----------------------------------------------------------
	// Vertex Shader (Now accepts dynamic VBO positions/normals)
	// -----------------------------------------------------------
	const GLchar *vertexShaderSourceCode =
		"#version 460 core\n"
		"in vec3 aPosition;\n"
		"in vec3 aNormal;\n"
		"in vec2 aTexCoord;\n"
		"uniform mat4 uModelMatrix;\n"
		"uniform mat4 uViewMatrix;\n"
		"uniform mat4 uProjectionMatrix;\n"
		"uniform float uTiling;\n"
		"out vec2  oTexCoord;\n"
		"out vec3  oWorldPos;\n"
		"out vec3  oNormal;\n"
		"out float oDisplacedHeight;\n"
		"void main(void)\n"
		"{\n"
		"   vec4 worldPos4 = uModelMatrix * vec4(aPosition, 1.0);\n"
		"   oWorldPos      = worldPos4.xyz;\n"
		"   oNormal        = normalize(mat3(transpose(inverse(uModelMatrix))) * aNormal);\n"
		"   oTexCoord      = aTexCoord * uTiling;\n"
		"   oDisplacedHeight = worldPos4.y;\n"
		"   gl_Position    = uProjectionMatrix * uViewMatrix * worldPos4;\n"
		"}";

	GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, (const GLchar **)&vertexShaderSourceCode, NULL);
	glCompileShader(vertexShaderObject);

	// -----------------------------------------------------------
	// Fragment Shader
	// -----------------------------------------------------------
	const GLchar *fragmentShaderCode =
		"#version 460 core\n"
		"in vec2  oTexCoord;\n"
		"in vec3  oWorldPos;\n"
		"in vec3  oNormal;\n"
		"in float oDisplacedHeight;\n"

		"uniform sampler2D   uDuDvMapTextureSampler;\n"
		"uniform samplerCube uSkyboxSampler;\n"
		"uniform float uMoveFactor;\n"
		"uniform float uWaveStrength;\n"
		"uniform vec3  uShallowColor;\n"
		"uniform vec3  uDeepColor;\n"
		"uniform float uColorBlendSharpness;\n"
		"uniform vec3  uFoamColor;\n"
		"uniform float uFoamThreshold;\n"
		"uniform vec3  uLightDir;\n"
		"uniform float uSpecularStrength;\n"
		"uniform float uShininess;\n"
		"uniform vec3  uSunColor;\n"
		"uniform vec3  uCameraPosition;\n"
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		"   vec2 distort1 = (texture(uDuDvMapTextureSampler, vec2(oTexCoord.x + uMoveFactor, oTexCoord.y)).rg * 2.0 - 1.0) * uWaveStrength;\n"
		"   vec2 distort2 = (texture(uDuDvMapTextureSampler, vec2(-oTexCoord.x + uMoveFactor, oTexCoord.y + uMoveFactor)).rg * 2.0 - 1.0) * uWaveStrength;\n"
		"   vec2 totalDistortion = distort1 + distort2;\n"
		"   vec3 N = normalize(oNormal + vec3(totalDistortion.x, 0.0, totalDistortion.y));\n"
		"   float depthBlend = clamp(oDisplacedHeight * uColorBlendSharpness, 0.0, 1.0);\n"
		"   vec3  waterColor = mix(uDeepColor, uShallowColor, depthBlend);\n"
		"   vec3  viewDir = normalize(uCameraPosition - oWorldPos);\n"
		"   vec3  R       = reflect(-viewDir, N);\n"
		"   vec3  reflectColor = texture(uSkyboxSampler, R).rgb;\n"
		"   // Physically based Fresnel for water (Schlick's approximation with R0 roughly 0.02)\n"
		"   float fresnel = 0.02 + 0.98 * pow(1.0 - max(dot(N, viewDir), 0.0), 5.0);\n"
		"   fresnel       = clamp(fresnel, 0.0, 1.0);\n"
		"   waterColor    = mix(waterColor, reflectColor, fresnel);\n"
		"   vec3  L       = normalize(-uLightDir);\n"
		"   vec3  H       = normalize(L + viewDir);\n"
		"   float spec    = pow(max(dot(N, H), 0.0), uShininess) * uSpecularStrength;\n"
		"   float diff    = max(dot(N, L), 0.0) * 0.3;\n"
		"   float foamMask = smoothstep(uFoamThreshold * 0.8, uFoamThreshold, oDisplacedHeight);\n"
		"   waterColor     = mix(waterColor, uFoamColor, foamMask);\n"
		"   vec3 finalColor = waterColor * (0.7 + diff) + (uSunColor * spec);\n"
		"   FragColor = vec4(finalColor, 0.92);\n"
		"}";

	GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, (const GLchar **)&fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderObject);

	// -----------------------------------------------------------
	// Shader Program
	// -----------------------------------------------------------
	shaderProgramObject = glCreateProgram();
	glAttachShader(shaderProgramObject, vertexShaderObject);
	glAttachShader(shaderProgramObject, fragmentShaderObject);
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_POSITION, "aPosition");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_NORMAL,   "aNormal");
	glBindAttribLocation(shaderProgramObject, AMC_ATTRIBUTE_TEXCOORD, "aTexCoord");
	glLinkProgram(shaderProgramObject);

	modelMatrixUniform          = glGetUniformLocation(shaderProgramObject, "uModelMatrix");
	viewMatrixUniform           = glGetUniformLocation(shaderProgramObject, "uViewMatrix");
	projectionMatrixUniform     = glGetUniformLocation(shaderProgramObject, "uProjectionMatrix");
	uDuDvSamplerUniform         = glGetUniformLocation(shaderProgramObject, "uDuDvMapTextureSampler");
	uMoveFactorUniform          = glGetUniformLocation(shaderProgramObject, "uMoveFactor");
	uWaveStrengthUniform        = glGetUniformLocation(shaderProgramObject, "uWaveStrength");
	uTilingUniform              = glGetUniformLocation(shaderProgramObject, "uTiling");
	uShallowColorUniform        = glGetUniformLocation(shaderProgramObject, "uShallowColor");
	uDeepColorUniform           = glGetUniformLocation(shaderProgramObject, "uDeepColor");
	uColorBlendSharpnessUniform = glGetUniformLocation(shaderProgramObject, "uColorBlendSharpness");
	uFoamColorUniform           = glGetUniformLocation(shaderProgramObject, "uFoamColor");
	uFoamThresholdUniform       = glGetUniformLocation(shaderProgramObject, "uFoamThreshold");
	uLightDirUniform            = glGetUniformLocation(shaderProgramObject, "uLightDir");
	uSpecularStrengthUniform    = glGetUniformLocation(shaderProgramObject, "uSpecularStrength");
	uShininessUniform           = glGetUniformLocation(shaderProgramObject, "uShininess");
	uSunColorUniform            = glGetUniformLocation(shaderProgramObject, "uSunColor");
	uCameraPositionUniform      = glGetUniformLocation(shaderProgramObject, "uCameraPosition");
	uSkyboxSamplerUniform       = glGetUniformLocation(shaderProgramObject, "uSkyboxSampler");

	// -----------------------------------------------------------
	// VBO setup
	// -----------------------------------------------------------
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_ocean) * VERTS, vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(AMC_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_ocean), (void*)0);
	glEnableVertexAttribArray(AMC_ATTRIBUTE_POSITION);

	glVertexAttribPointer(AMC_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_ocean), (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(AMC_ATTRIBUTE_NORMAL);

	glVertexAttribPointer(AMC_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_ocean), (void*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(AMC_ATTRIBUTE_TEXCOORD);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * INDS, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	g_dudvMapTexture = dudvMapTexture;
	g_skyboxTexture  = skyboxCubemapTexture;

	return(TRUE);
}

// -------------------------------------------------------------------
// renderOcean
// -------------------------------------------------------------------
void renderOcean(OceanParams &params, Camera *pCamera, vmath::mat4 projectionMatrix)
{
	// FFT Re-computation check
	if (params.waveHeight != prev_waveHeight || params.waveDirectionAngle != prev_waveDir || params.tideSpeed != prev_tideSpeed) {
		recalculate_hTilde_0(params);
		prev_waveHeight = params.waveHeight;
		prev_waveDir = params.waveDirectionAngle;
		prev_tideSpeed = params.tideSpeed;
	}

	params.moveFactor += params.tideSpeed * 0.0005f;
	if (params.moveFactor > 1.0f) params.moveFactor -= 1.0f;

	g_oceanTime += params.tideSpeed * 0.005f;

	// Execute FFT and update CPU vertices
	evaluateWavesFFT(g_oceanTime, -params.waveChoppiness);

	// Update GPU VBO dynamically
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_ocean) * VERTS, vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// code
	glUseProgram(shaderProgramObject);

	vmath::mat4 modelMatrix = vmath::translate(params.translation) * vmath::scale(params.scale);

	glUniformMatrix4fv(modelMatrixUniform,      1, GL_FALSE, modelMatrix);
	glUniformMatrix4fv(viewMatrixUniform,       1, GL_FALSE, pCamera->getLookAtMatrix());
	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, projectionMatrix);

	glUniform1i(uDuDvSamplerUniform,    0);
	glUniform1f(uMoveFactorUniform,     params.moveFactor);
	glUniform1f(uWaveStrengthUniform,   params.waveStrength);
	glUniform1f(uTilingUniform,         params.tiling);

	glUniform3fv(uShallowColorUniform,       1, params.shallowColor);
	glUniform3fv(uDeepColorUniform,          1, params.deepColor);
	glUniform1f(uColorBlendSharpnessUniform,    params.colorBlendSharpness);
	glUniform3fv(uFoamColorUniform,          1, params.foamColor);
	glUniform1f(uFoamThresholdUniform,          params.foamThreshold);

	float azimuthRad = vmath::radians(params.sunAzimuth);
	float elevationRad = vmath::radians(params.sunElevation);
	vmath::vec3 sunDir = vmath::vec3(cos(elevationRad) * sin(azimuthRad),
									 sin(elevationRad),
									 cos(elevationRad) * cos(azimuthRad));
	vmath::vec3 lightDir = -sunDir;

	glUniform3fv(uLightDirUniform,           1, lightDir);
	glUniform1f(uSpecularStrengthUniform,       params.specularStrength);
	glUniform1f(uShininessUniform,              params.shininess);
	glUniform3fv(uSunColorUniform,           1, params.sunColor);

	vmath::vec3 camPos = pCamera->m_position; 
	glUniform3fv(uCameraPositionUniform,     1, camPos);
	glUniform1i(uSkyboxSamplerUniform, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_dudvMapTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_skyboxTexture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, INDS, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
	glUseProgram(0);
}

// -------------------------------------------------------------------
// displayOceanImGui 
// -------------------------------------------------------------------
void displayOceanImGui(OceanParams &params)
{
	// Uses the exact same interface as before, but powers FFT internally
	if (ImGui::CollapsingHeader("FFT Ocean", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();
		ImGui::Text("--- Geometry ---");
		ImGui::DragFloat3("Ocean Translation", &params.translation[0], 0.5f);
		ImGui::DragFloat3("Ocean Scale",       &params.scale[0],       0.5f);

		ImGui::Separator();
		ImGui::Text("--- Tide & Wave (CUSTOMIZABLE) ---");
		ImGui::DragFloat("Tide/Wind Speed",     &params.tideSpeed,          0.01f, 0.0f,  10.0f);
		ImGui::DragFloat("Wave Height (A)",     &params.waveHeight,         0.05f, 0.0f,  20.0f);
		ImGui::DragFloat("Wave Choppiness",     &params.waveChoppiness,     0.01f, 0.0f,  2.0f);
		ImGui::DragFloat("Wind Direction",      &params.waveDirectionAngle, 1.0f,  0.0f,  360.0f);

		ImGui::Separator();
		ImGui::Text("--- DuDv Distortion ---");
		ImGui::DragFloat("Wave Strength", &params.waveStrength, 0.005f, 0.0f, 1.0f);
		ImGui::DragFloat("Tiling",        &params.tiling,       0.1f,  0.1f, 20.0f);

		ImGui::Separator();
		ImGui::Text("--- Color & Foam ---");
		ImGui::ColorEdit3("Shallow Color",       &params.shallowColor[0]);
		ImGui::ColorEdit3("Deep Color",          &params.deepColor[0]);
		ImGui::DragFloat("Color Blend Sharpness",&params.colorBlendSharpness, 0.1f, 0.0f, 10.0f);
		ImGui::ColorEdit3("Foam Color",          &params.foamColor[0]);
		ImGui::DragFloat("Foam Threshold",       &params.foamThreshold, 0.05f, 0.0f, 5.0f);

		ImGui::Separator();
		ImGui::Text("--- Lighting ---");
		ImGui::DragFloat("Sun Elevation",     &params.sunElevation,     0.5f, -90.0f,  90.0f);
		ImGui::DragFloat("Sun Azimuth",       &params.sunAzimuth,       1.0f,   0.0f, 360.0f);
		ImGui::DragFloat("Specular Strength", &params.specularStrength, 0.05f, 0.0f, 5.0f);
		ImGui::DragFloat("Shininess",         &params.shininess,        1.0f,  2.0f, 256.0f);
		ImGui::ColorEdit3("Sun Color",        &params.sunColor[0]);
	}
}

// -------------------------------------------------------------------
// uninitializeOcean
// -------------------------------------------------------------------
void uninitializeOcean(void)
{
	if (ebo) glDeleteBuffers(1, &ebo);
	if (vbo) glDeleteBuffers(1, &vbo);
	if (vao) glDeleteVertexArrays(1, &vao);

	if (shaderProgramObject) {
		glUseProgram(shaderProgramObject);
		GLint numShader = 0;
		glGetProgramiv(shaderProgramObject, GL_ATTACHED_SHADERS, &numShader);
		if (numShader > 0) {
			GLuint *pShader = (GLuint *)malloc(numShader * sizeof(GLuint));
			if (pShader != NULL) {
				glGetAttachedShaders(shaderProgramObject, numShader, NULL, pShader);
				for (GLint i = 0; i < numShader; i++) {
					glDetachShader(shaderProgramObject, pShader[i]);
					glDeleteShader(pShader[i]);
					pShader[i] = NULL;
				}
				free(pShader); pShader = NULL;
			}
		}
		glUseProgram(0);
		glDeleteProgram(shaderProgramObject);
		shaderProgramObject = 0;
	}

	delete[] vertices;
	delete[] indices;
	delete[] h_tilde;
	delete[] h_tilde_slopex;
	delete[] h_tilde_slopez;
	delete[] h_tilde_dx;
	delete[] h_tilde_dz;
	delete fft;
}
