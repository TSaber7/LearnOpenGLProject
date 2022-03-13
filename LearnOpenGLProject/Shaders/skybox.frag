#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform float mipLevel;

void main()
{    
    FragColor = textureLod(skybox, TexCoords,mipLevel);
}