#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

out vec3 col_to_frag;
out vec2 tex_to_frag;

uniform float t;

void main() {

    mat2 R = mat2(
        cos(t), -sin(t),
        sin(t),  cos(t)
    );
    
    gl_Position = vec4(R*pos.xy, pos.z, 1.0);

    /* Pass on to frag */
    col_to_frag = col;
    tex_to_frag = tex;
}
