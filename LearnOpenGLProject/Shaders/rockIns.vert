#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 instanceMatrix;


uniform mat4 projection;
uniform mat4 view;
out VS_OUT{
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
}vs_out;

void main()
{
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0); 
    vs_out.TexCoords = aTexCoords;
}