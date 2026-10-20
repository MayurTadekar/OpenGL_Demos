#version 450 core                         

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vTexCoord;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

uniform mat4 u_vMatrix;                 
uniform mat4 u_pMatrix;

// Fragment shader inputs
layout(location = 0) out VS_OUT
{
    vec2 texCoord;
    vec3 fragPos;           // Fragment position in world space
    vec3 normal;            // Normal in world space
    vec3 tangent;           // Tangent in world space
    vec3 bitangent;         // Bitangent in world space
    mat3 TBN;               // Tangent-Bitangent-Normal matrix
} vs_out;


// // Structure for Instancing
// struct ModelInstance
// {
//     mat4 mMatrix;               // Model matrix for this instance
//     mat4 mMatrixInvTranspose;   // Inverse transpose of model matrix for normals
// };

// layout(std430, binding = 0) readonly buffer ModelInstanceBuffer
// {
//     ModelInstance instances[]; // Array of model instances
// };

struct FlockMember {
        vec4 position;
        vec4 velocity;
};

layout(std430, binding = 0) readonly buffer Birds {
        FlockMember member[];
};


void main(void)                           
{                                         
    // Get the instance data for this instance
    // ModelInstance instance = instances[gl_InstanceID];
    
    FlockMember bird = member[gl_InstanceID];

    vec3 forward = normalize(bird.velocity.xyz);

    vec3 worldUp = vec3(0.0, 1.0, 0.0);

    if(abs(dot(worldUp, forward)) > 0.99) worldUp = vec3(1.0, 0.0, 0.0);

    vec3 right = normalize(cross(worldUp, forward));
    vec3 up = cross(forward, right);

    mat3 rotation = mat3(right, up, forward);

    vec3 worldPosition = bird.position.xyz + rotation * vPosition;
    
    // Transform position to world space
    // vec4 worldPos = instance.mMatrix * vec4(vPosition, 1.0);
    vs_out.fragPos = worldPosition.xyz;
    
    // Transform normal to world space using inverse transpose
    vs_out.normal = normalize(vNormal);//normalize(mat3(instance.mMatrixInvTranspose) * vNormal);
    
    // Transform tangent and bitangent to world space
    vs_out.tangent = normalize(mat3(1.0) * vTangent);
    vs_out.bitangent = normalize(mat3(1.0) * vBitangent);
    
    // Orthogonalize tangent with respect to normal (Gram-Schmidt process)
    vs_out.tangent = normalize(vs_out.tangent - dot(vs_out.tangent, vs_out.normal) * vs_out.normal);
    
    // Construct TBN matrix for normal mapping
    vs_out.TBN = mat3(vs_out.tangent, vs_out.bitangent, vs_out.normal);
    
    // Pass texture coordinates
    vs_out.texCoord = vTexCoord;
    
    // Transform position to clip space
    gl_Position = u_pMatrix * u_vMatrix * vec4(worldPosition, 1.0);
}
