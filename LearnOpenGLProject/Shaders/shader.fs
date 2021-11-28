#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec3 vPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float alpha;

void main()
{
    vec2 TexCoord1=vec2(1-TexCoord.s,TexCoord.t);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord1), alpha);
    //FragColor = vec4(1.0,0.0,0.0,1.0);
    //FragColor=texture(texture2, TexCoord);
}