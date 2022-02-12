#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
void main()
{            

    FragColor = texture(screenTexture,TexCoords.st);
    // Check whether fragment output is higher than threshold, if so output as brightness color
    float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 2.0)
        BrightColor = vec4(FragColor.rgb, 1.0);
}