#version 330 core
layout (points) in;
layout (line_strip, max_vertices = 2) out;

void build_house(vec4 position)
{    
    gs_out.fColor = vec3(1.0, 1.0, 1.0);
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:����
    EmitVertex(); 
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:����
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:����
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:����
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:����
    
    EmitVertex();

    EndPrimitive();
}

void main() { 
    gl_PointSize=10.0f;
    build_house(gl_in[0].gl_Position);
}