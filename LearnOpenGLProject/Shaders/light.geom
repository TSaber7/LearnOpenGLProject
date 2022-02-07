#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;

void build_house(vec4 position)
{    
    gs_out.fColor = vec3(1.0, 1.0, 1.0);
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:左下
    EmitVertex(); 
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:右下
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:左上
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:右上
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:顶部
    
    EmitVertex();

    EndPrimitive();
}

void main() { 
    gl_PointSize=10.0f;
    build_house(gl_in[0].gl_Position);
}