#version 460 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex;
uniform vec4 objColor;
uniform vec3 objEmission;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform float ambient;
uniform float specularStrenght;
uniform float lightIntensityFalloff;
uniform float lightEffectiveRangeInverse;

vec4 PointLight()
{
    vec3 lightVector = lightPos - currentPos;
    float lightDistance = length(lightVector);

    float lightIntensity = 1.0f / (lightIntensityFalloff * pow(lightDistance, 2.0f) + lightEffectiveRangeInverse * lightDistance + 1.0f);

    vec3 nNormal = normalize(normal); 
    vec3 lightDirection = normalize(lightVector);
    float diffuse = max(dot(nNormal, lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(cameraPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, nNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrenght);
    float specular = specularAmount * specularLight;

    return texture(tex, texCoord) * objColor * vec4(objEmission, 1.0f) * lightColor * (diffuse * lightIntensity + specular * lightIntensity + ambient);
}

void main()
{   
    FragColor = PointLight();
}