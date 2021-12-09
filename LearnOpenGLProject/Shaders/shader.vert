#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 vPos;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

void main()
{
    gl_Position =projection * view * model *vec4(aPos.x,aPos.y,aPos.z, 1.0);
    //gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);
    vPos=aPos;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(view*model))) * aNormal;
    FragPos = vec3(view*model * vec4(aPos, 1.0));

}