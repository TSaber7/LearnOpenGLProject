#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 vPos;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 ambient = material.ambient * light.ambient;
    vec2 TexCoord1=vec2(1-TexCoord.s,TexCoord.t);

    //vec3 objectColor=mix(texture(texture1, TexCoord), texture(texture2, TexCoord1), alpha).xyz;
    vec3 objectColor=vec3(1.0f, 0.5f, 0.31f);
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse*diff * light.diffuse;

    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = material.specular * spec * light.specular;

    vec3 result=ambient + diffuse+specular;
    FragColor = vec4(result,1.0f);
}