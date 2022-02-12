#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform float exposure;
uniform bool hdr;

const float offset = 1.0 / 300.0;  

void main()
{

    vec3 hdrColor=texture(scene,TexCoords.st).rgb;
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    FragColor.rgb=hdrColor+bloomColor;
    // reinhard
    //FragColor.rgb = FragColor.rgb / (FragColor.rgb + vec3(10.0));
     //exposure
    FragColor.rgb = vec3(1.0) - exp(-FragColor.rgb * exposure);
     //apply gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));



    //后处理，屏幕左右红绿双色
//    if(gl_FragCoord.x < 400)
//        FragColor = vec4(1.0, 0.8, 0.8, 1.0);
//    else
//        FragColor = vec4(0.8, 1.0, 0.8, 1.0);  
//    FragColor=FragColor*texture(screenTexture,TexCoords);
}