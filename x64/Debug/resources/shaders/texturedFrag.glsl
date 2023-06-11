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
uniform vec3 lightDirection;
uniform float ambient;
uniform float specularStrenght;
uniform float lightIntensityFalloff;
uniform float lightEffectiveRangeInverse;
uniform float lightInnerCone;
uniform float lightOuterCone;
uniform int lightType;

uniform vec3 cameraPos;


vec4 PointLight()
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
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrenght);
    float specular = specularAmount * specularLight;

    return texture(tex, texCoord) * objColor * vec4(objEmission, 1.0f) * lightColor * (diffuse * lightIntensity + specular * lightIntensity + ambient);
}

vec4 DirectionalLight()
{
    vec3 nNormal = normalize(normal); 
    float diffuse = max(dot(nNormal, -lightDirection), 0.0f);

    float specularLight = 0.5f;
    vec3 viewDirection = normalize(cameraPos - currentPos);
    vec3 reflectionDirection = reflect(lightDirection, nNormal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrenght);
    float specular = specularAmount * specularLight;

    return texture(tex, texCoord) * objColor * vec4(objEmission, 1.0f) * lightColor * (diffuse + specular + ambient);
}

vec4 SpotLight()
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
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), specularStrenght);
    float specular = specularAmount * specularLight;

    float angle = dot(lightDirection, -lightDirectionRelative);
    float spotIntensity = clamp((angle - lightOuterCone) / (lightInnerCone - lightOuterCone), 0.0f, 1.0f);

    return texture(tex, texCoord) * objColor * vec4(objEmission, 1.0f) * lightColor * (diffuse * lightIntensity * spotIntensity + specular * lightIntensity * spotIntensity + ambient);
}

void main()
{   
    if (lightType == 0)
        FragColor = PointLight();
        
    if (lightType == 1)
        FragColor = DirectionalLight();
        
    if (lightType == 2)
        FragColor = SpotLight();
}