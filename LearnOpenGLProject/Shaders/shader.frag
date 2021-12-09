#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 vPos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float alpha;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    vec2 TexCoord1=vec2(1-TexCoord.s,TexCoord.t);

    //vec3 objectColor=mix(texture(texture1, TexCoord), texture(texture2, TexCoord1), alpha).xyz;
    vec3 objectColor=vec3(1.0f, 0.5f, 0.31f);
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result=(ambient + diffuse+specular) * objectColor;
    FragColor = vec4(result,1.0f);
}