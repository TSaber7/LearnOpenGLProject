#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
// ִ��͸�ӳ���
//��ʹ������ͶӰ���󣬶���wԪ���Ա��ֲ��䣬������һ��ʵ���Ϻ�������
//���ǣ���ʹ��͸��ͶӰ��ʱ����Ǳ�����ˣ�����Ϊ�˱�֤������ͶӰ�����¶���Ч�͵��������С�
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    //Ϊ�˺������ͼ�������Ƚϣ�z������Ҫ�任��[0,1]��Ϊ����Ϊ�������ͼ�в��������꣬xy����Ҳ��Ҫ�任��[0,1]
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.z > 1.0)
        return 0.0;

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 lightDir=lightPos-fs_in.FragPos;
    float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightDir)), 0.02); 
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

//    int blockerSize=1;
//    int tmp=(blockerSize-1)/2;
//    float dBlocker=0.0;
//    for(int x = -tmp; x <= tmp; ++x)
//    {
//        for(int y = -tmp; y <= tmp; ++y)
//        {
//            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
//            dBlocker += currentDepth - bias > pcfDepth ? pcfDepth : 0.0;        
//        }    
//    }
//    dBlocker /= blockerSize*blockerSize;
//    if(dBlocker<0.01)
//        return 0.0;
    float wLight=1;
    float wPenumbra=currentDepth - bias > closestDepth ? (currentDepth-bias-closestDepth)*wLight/closestDepth : 0.0;
    //FragColor = vec4(vec3(closestDepth), 1.0f);
//    if(wPenumbra>4){
//        return 0.0;
//    }
//    //int filterSize=max(int(wPenumbra*4)*2+1,3);
    int filterSize=5;
    int tmp=(filterSize-1)/2;
    for(int x = -tmp; x <= tmp; ++x)
    {
        for(int y = -tmp; y <= tmp; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0: 0.0;        
        }    
    }
    shadow /= filterSize*filterSize;
    return shadow;
}

void main()
{           
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(1.0);
    // Ambient
    vec3 ambient = 0.15 * color;
    // Diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // Specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // ������Ӱ
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    

    FragColor = vec4(lighting, 1.0f);
}