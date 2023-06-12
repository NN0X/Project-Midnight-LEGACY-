#version 460 core
#define L_NUM

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex;
uniform vec4 objColor;
uniform vec3 objEmission;

uniform vec3 lightColors[L_NUM];
uniform vec3 lightPoss[L_NUM];
uniform vec3 lightDirections[L_NUM];
uniform float lightStrengths[L_NUM];
uniform float lightAmbients[L_NUM];
uniform float specularStrengths[L_NUM];
uniform float lightIntensityFalloffs[L_NUM];
uniform float lightEffectiveRangeInverses[L_NUM];
uniform float lightInnerCones[L_NUM];
uniform float lightOuterCones[L_NUM];
uniform int lightTypes[L_NUM];

uniform vec3 cameraPos;


vec4 PointLight(vec3 lightColor, vec3 lightPos, float lightStrength, float lightAmbient, float specularStrength, float lightIntensityFalloff, float lightEffectiveRangeInverse)
{
    vec3 lightVector = lightPos - currentPos;
    float lightDistance = length(lightVector);

    float lightIntensity = 1.0f / (lightIntensityFalloff * pow(lightDistance, 2.0f) + lightEffectiveRangeInverse * lightDistance + 1.0f);

    vec3 nNormal = normalize(normal); 
    vec3 lightDirectionRelative = normalize(lightVector);
    float diffuse = max(dot(nNormal, lightDirectionRelative), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(cameraPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirectionRelative, nNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrength);
    float specular = specularAmount * specularLight;

    return vec4(lightColor * (diffuse * lightIntensity * lightStrength + specular * lightIntensity * lightStrength + lightAmbient), 1.0f);
}

vec4 DirectionalLight(vec3 lightColor, vec3 lightPos, vec3 lightDirection, float lightStrength, float lightAmbient, float specularStrength)
{
    vec3 nNormal = normalize(normal); 
    float diffuse = max(dot(nNormal, -lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(cameraPos - currentPos);
    vec3 reflectionDirection = reflect(lightDirection, nNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrength);
    float specular = specularAmount * specularLight;

    return vec4(lightColor * (diffuse * lightStrength + specular * lightStrength + lightAmbient), 1.0f);
}

vec4 SpotLight(vec3 lightColor, vec3 lightPos, vec3 lightDirection, float lightStrength, float lightAmbient, float specularStrength, float lightIntensityFalloff, float lightEffectiveRangeInverse, float lightInnerCone, float lightOuterCone)
{
    vec3 lightVector = lightPos - currentPos;
    float lightDistance = length(lightVector);

    float lightIntensity = 1.0f / (lightIntensityFalloff * pow(lightDistance, 2.0f) + lightEffectiveRangeInverse * lightDistance + 1.0f);

    vec3 nNormal = normalize(normal); 
    vec3 lightDirectionRelative = normalize(lightVector);
    float diffuse = max(dot(nNormal, lightDirectionRelative), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(cameraPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirectionRelative, nNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrength);
    float specular = specularAmount * specularLight;

    float angle = dot(lightDirection, -lightDirectionRelative);
    float spotIntensity = clamp((angle - lightOuterCone) / (lightInnerCone - lightOuterCone), 0.0f, 1.0f);

    return vec4(lightColor * (diffuse * lightIntensity * lightStrength * spotIntensity + specular * lightIntensity * lightStrength * spotIntensity + lightAmbient), 1.0f);
}

void main()
{   
    vec4 light;

    for (int index = 0; index < L_NUM; index++)
    {
        if (lightTypes[index] == 0)
            light += PointLight(lightColors[index], lightPoss[index], lightStrengths[index], lightAmbients[index], specularStrengths[index], lightIntensityFalloffs[index], lightEffectiveRangeInverses[index]);
            
        if (lightTypes[index] == 1)
            light += DirectionalLight(lightColors[index], lightPoss[index], lightDirections[index], lightStrengths[index], lightAmbients[index], specularStrengths[index]);
            
        if (lightTypes[index] == 2)
            light += SpotLight(lightColors[index], lightPoss[index], lightDirections[index], lightStrengths[index], lightAmbients[index], specularStrengths[index], lightIntensityFalloffs[index], lightEffectiveRangeInverses[index], lightInnerCones[index], lightOuterCones[index]);
    }

    FragColor = texture(tex, texCoord) * objColor * vec4(objEmission, 1.0f) * light;
}