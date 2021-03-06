#version 330 core
out vec4 FragColor;

in VS_OUT{
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
}vs_in;


uniform vec3 cameraPos;
uniform samplerCube skybox;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;

    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
}; 

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
void main()
{
    
    FragColor = texture(material.texture_diffuse1, vs_in.TexCoords);

    //根据反射方向采集天空盒
//    vec3 I = normalize(vs_in.FragPos - cameraPos);
//    vec3 R = reflect(I, normalize(vs_in.Normal));
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);
//    //根据折射方向采集天空盒
//    float ratio = 1.00 / 1.52;
//    R = refract(I, normalize(vs_in.Normal), ratio);
//    FragColor = vec4(texture(skybox, R).rgb, 1.0);
//
    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
    //FragColor = vec4(1.0,1.0,1.0, 1.0);
//    // 属性
//    vec3 norm = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);
//
//    // 第一阶段：定向光照
//    vec3 result = CalcDirLight(dirLight, norm, viewDir);
//    // 第二阶段：点光源
//    for(int i = 0; i < NR_POINT_LIGHTS; i++)
//        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
//    // 第三阶段：聚光
//    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
//
//    FragColor = vec4(result, 1.0);
}

//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
//{
//    vec3 lightDir = normalize(-light.direction);
//    // 漫反射着色
//    float diff = max(dot(normal, lightDir), 0.0);
//    // 镜面光着色
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // 合并结果
//    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    return (ambient + diffuse + specular);
//}
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
//{
//    vec3 lightDir = normalize(light.position - fragPos);
//    // 漫反射着色
//    float diff = max(dot(normal, lightDir), 0.0);
//    // 镜面光着色
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//    // 衰减
//    float distance    = length(light.position - fragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + 
//                 light.quadratic * (distance * distance));    
//    // 合并结果
//    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
//    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
//    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
//    ambient  *= attenuation;
//    diffuse  *= attenuation;
//    specular *= attenuation;
//    return (ambient + diffuse + specular);
//}