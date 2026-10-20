#version 460 core

out vec4 FragColor;

in GS_OUT
{
    vec2 textCoord;
    float colorVariation;
}fs_in;

uniform sampler2D u_textgrass;

void main(void)
{

    // very simple but we can also add lighting to get better result
    vec4 color = texture(u_textgrass, fs_in.textCoord);
    if (color.a < 0.25 ) discard;
    color.xyz = mix(color.xyz, 0.5*color.xyz, fs_in.colorVariation);
    FragColor = color;
}


/*#version 460 core

in GS_OUT
{
    vec2 oTexCoord;
    float oColorVariation;
    vec3 oTransformedNormals;
    vec3 oLightDirection;
    vec3 oViewerVector;
} fragmentShaderInput;

uniform vec3 uLightAmbient;
uniform vec3 uLightDiffuse;
uniform vec3 uLightSpecular;

uniform vec3  uMaterialAmbient;
uniform vec3  uMaterialDiffuse;
uniform vec3  uMaterialSpecular;
uniform float uMaterialShininess;

uniform sampler2D uGrassTextureSampler;

out vec4 FragColor;

void main(void)
{
    vec4 texColor = texture(uGrassTextureSampler, fragmentShaderInput.oTexCoord);
    
    if (texColor.a < 0.25) 
    {
        discard;
    }

    texColor.rgb = mix(texColor.rgb, 0.5 * texColor.rgb, fragmentShaderInput.oColorVariation);

    vec3 normalizedTransformedNormals = normalize(fragmentShaderInput.oTransformedNormals);

    vec3 normalizedLightDirection = normalize(fragmentShaderInput.oLightDirection);
    vec3 normalizedViewerVector   = normalize(fragmentShaderInput.oViewerVector);

    vec3 ambientLight     = uLightAmbient * uMaterialAmbient;
    vec3 diffuseLight     = uLightDiffuse * uMaterialDiffuse * max(dot(normalizedLightDirection, normalizedTransformedNormals), 0.0);
    vec3 reflectionVector = reflect(-normalizedLightDirection, normalizedTransformedNormals);
    vec3 specularLight    = uLightSpecular * uMaterialSpecular * pow(max(dot(reflectionVector, normalizedViewerVector), 0.0), uMaterialShininess);

    FragColor = vec4(ambientLight + diffuseLight + specularLight, 1.0) * texColor;
    FragColor = vec4(1.0);
}*/
