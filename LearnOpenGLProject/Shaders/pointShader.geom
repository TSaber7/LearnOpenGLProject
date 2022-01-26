#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out GS_OUT{
    vec3 fColor;
}gs_out;
void build_house(vec4 position)
{    
    gs_out.fColor = gs_in[0].color; // gs_in[0] ��Ϊֻ��һ�����붥��
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:����
    EmitVertex(); 
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:����
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:����
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:����
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:����
    gs_out.fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main() { 
    gl_PointSize=10.0f;
    build_house(gl_in[0].gl_Position);
}