#version 450 core  

// Input from vertex shader
layout(location = 0) in VS_OUT
{
    vec2 texCoord;
    vec3 fragPos;
    vec3 normal;
    vec3 tangent;
    vec3 bitangent;
    mat3 TBN;
} fs_in;

// Material properties
struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform vec3 u_viewPos;         // Camera position
uniform vec3 u_lightPos;        // Light position
uniform vec3 u_lightColor;      // Light color

out vec4 Fragcolor;

void main(void)                               
{
    // Sample textures
    vec3 texColor = texture(material.texture_diffuse1, fs_in.texCoord).rgb;
    
    // Use normal from normal map if available, otherwise use interpolated normal
    vec3 norm = fs_in.normal;
    // Note: Uncomment below to use normal mapping
    // vec3 mappedNormal = texture(material.texture_normal1, fs_in.texCoord).rgb;
    // mappedNormal = normalize(mappedNormal * 2.0 - 1.0);  // Convert from [0,1] to [-1,1]
    // norm = normalize(fs_in.TBN * mappedNormal);
    
    // Normalize the normal vector
    norm = normalize(norm);
    
    // Calculate lighting
    // Ambient component
    vec3 ambient = material.ambient * texColor;
    
    // Diffuse component
    vec3 lightDir = normalize(u_lightPos - fs_in.fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * texColor * u_lightColor;
    
    // Specular component
    vec3 viewDir = normalize(u_viewPos - fs_in.fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularTex = texture(material.texture_specular1, fs_in.texCoord).rgb;
    vec3 specular = spec * material.specular * specularTex * u_lightColor;
    
    // Combine lighting results
    vec3 result = ambient + diffuse + specular;
    
    // Output final color
    Fragcolor = vec4(result, 1.0);
}
