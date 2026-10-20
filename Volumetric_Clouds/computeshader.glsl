// Compute Shader

#version 430 core
// layout(local_size_x = 4, local_size_y = 4, local_size_z = 4) in;
layout(local_size_x = 8, local_size_y = 8, local_size_z = 8) in;

// Output 3D texture
layout(rgba16f, binding = 0) uniform image3D u_OutputTex;
// layout(rgba16f, binding = 0) uniform image3D noiseTexture;

// Uniforms to control the noise properties
uniform int u_redChannel;
uniform float u_redNoiseScaleA = 5.0;
uniform float u_redNoiseScaleB = 15.0;
uniform float u_redNoiseScaleC = 18.0;
uniform float u_redpersistence = 0.0;

uniform int u_greenChannel;
uniform float u_greenNoiseScaleA = 5.0;
uniform float u_greenNoiseScaleB = 15.0;
uniform float u_greenNoiseScaleC = 18.0;
uniform float u_greenpersistence = 0.0;

uniform int u_blueChannel;
uniform float u_blueNoiseScaleA = 5.0;
uniform float u_blueNoiseScaleB = 15.0;
uniform float u_blueNoiseScaleC = 18.0;
uniform float u_bluepersistence = 0.0;

// Pseudo-random 3D hash function to place a feature point inside a cell
vec3 hash3(vec3 p) {
	p = vec3(dot(p, vec3(127.1, 311.7, 74.7)), dot(p, vec3(269.5, 183.3, 246.1)), dot(p, vec3(113.5, 271.9, 124.6)));
	return fract(sin(p) * 43758.5453123);
}

// 3D Worley Noise Function (Tileable/Periodic)
float worley3D(vec3 p, float noiseScale) {
	vec3 cell = floor(p);
	vec3 localPos = fract(p);

	float min_dist = 1.0; // Max possible distance inside a neighbor check loop

    // Loop through 3x3x3 neighboring cells
	for(int z = -1; z <= 1; z++) {
		for(int y = -1; y <= 1; y++) {
			for(int x = -1; x <= 1; x++) {
				vec3 neighbor = vec3(float(x), float(y), float(z));

                // Wrap around coordinates for seamless tiling
				vec3 wrappedCell = mod(cell + neighbor, vec3(noiseScale));

                // Retrieve the random feature point offset for this cell
				vec3 pointOffset = hash3(wrappedCell);

                // Calculate position vector from our local position to the feature point
				vec3 targetPos = neighbor + pointOffset;
				float dist = distance(localPos, targetPos);

                // Keep the minimum distance found
				min_dist = min(min_dist, dist);
			}
		}
	}
	return (min_dist);
}

void main() {
    // Get the coordinate of the current voxel
	ivec3 texelCoord = ivec3(gl_GlobalInvocationID.xyz);
	ivec3 texSize = imageSize(u_OutputTex);

    // Ensure we don't write out of bounds
	if(texelCoord.x >= texSize.x || texelCoord.y >= texSize.y || texelCoord.z >= texSize.z) {
		return;
	}

    // Normalize coordinates to [0.0, 1.0] range
	vec3 uvw = vec3(texelCoord) / vec3(texSize);

	// Red Channel
	float rednoiseVal = 1.0;
	if(1 == u_redChannel) {
	    // Scale coordinates based on frequency/density
		vec3 rednoiseInputA = uvw * u_redNoiseScaleA;
		vec3 rednoiseInputB = uvw * u_redNoiseScaleB;
		vec3 rednoiseInputC = uvw * u_redNoiseScaleC;

    	// Generate the F1 Worley Noise value
		float rednoiseValA = worley3D(rednoiseInputA, u_redNoiseScaleA);
		float rednoiseValB = worley3D(rednoiseInputB, u_redNoiseScaleB);
		float rednoiseValC = worley3D(rednoiseInputC, u_redNoiseScaleC);

		rednoiseVal = rednoiseValA + (rednoiseValB * u_redpersistence) + (rednoiseValC * u_redpersistence * u_redpersistence);
		float maxVal = 1 + (u_redpersistence) + (u_redpersistence * u_redpersistence);

		rednoiseVal /= maxVal;

		rednoiseVal = 1.0 - rednoiseVal; // Invert the noise to get standard "bubble/cloud" shapes if desired
	}

	// Green Channel
	float greennoiseVal = 1.0;
	if(1 == u_greenChannel) {
	    // Scale coordinates based on frequency/density
		vec3 greennoiseInputA = uvw * u_greenNoiseScaleA;
		vec3 greennoiseInputB = uvw * u_greenNoiseScaleB;
		vec3 greennoiseInputC = uvw * u_greenNoiseScaleC;

    	// Generate the F1 Worley Noise value
		float greennoiseValA = worley3D(greennoiseInputA, u_greenNoiseScaleA);
		float greennoiseValB = worley3D(greennoiseInputB, u_greenNoiseScaleB);
		float greennoiseValC = worley3D(greennoiseInputC, u_greenNoiseScaleC);

		greennoiseVal = greennoiseValA + (greennoiseValB * u_greenpersistence) + (greennoiseValC * u_greenpersistence * u_greenpersistence);
		float maxVal = 1 + (u_greenpersistence) + (u_greenpersistence * u_greenpersistence);

		greennoiseVal /= maxVal;

		greennoiseVal = 1.0 - greennoiseVal; // Invert the noise to get standard "bubble/cloud" shapes if desired
	}

	// Blue Channel
	float bluenoiseVal = 1.0;
	if(1 == u_blueChannel) {
	    // Scale coordinates based on frequency/density
		vec3 bluenoiseInputA = uvw * u_blueNoiseScaleA;
		vec3 bluenoiseInputB = uvw * u_blueNoiseScaleB;
		vec3 bluenoiseInputC = uvw * u_blueNoiseScaleC;

    	// Generate the F1 Worley Noise value
		float bluenoiseValA = worley3D(bluenoiseInputA, u_blueNoiseScaleA);
		float bluenoiseValB = worley3D(bluenoiseInputB, u_blueNoiseScaleB);
		float bluenoiseValC = worley3D(bluenoiseInputC, u_blueNoiseScaleC);

		bluenoiseVal = bluenoiseValA + (bluenoiseValB * u_bluepersistence) + (bluenoiseValC * u_bluepersistence * u_bluepersistence);
		float maxVal = 1 + (u_bluepersistence) + (u_bluepersistence * u_bluepersistence);

		bluenoiseVal /= maxVal;

		bluenoiseVal = 1.0 - bluenoiseVal; // Invert the noise to get standard "bubble/cloud" shapes if desired
	}

    // Store the resulting value in the 3D texture
	// imageStore(u_OutputTex, texelCoord, vec4(vec3(rednoiseVal), 1.0));
	imageStore(u_OutputTex, texelCoord, vec4(rednoiseVal, greennoiseVal, bluenoiseVal, 1.0));
}
