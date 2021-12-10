#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 vPos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = vec3(texture(material.diffuse, TexCoord)) * light.ambient;

    //vec3 objectColor=mix(texture(texture1, TexCoord), texture(texture2, TexCoord1), alpha).xyz;
    vec3 objectColor=vec3(1.0f, 0.5f, 0.31f);
    
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(texture(material.diffuse, TexCoord))*diff * light.diffuse;

    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(texture(material.specular, TexCoord)) * spec * light.specular;

    vec3 result=ambient + diffuse+specular;
    FragColor = vec4(result,1.0f);
}