#version 330 core
out vec4 FragColor;

in GS_OUT{
    vec3 fColor;
}fs_in;
void main()
{

    FragColor = vec4(fs_in.fColor, 1.0);   
}