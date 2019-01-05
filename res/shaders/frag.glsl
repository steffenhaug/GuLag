#version 330 core
out vec4 FragColor;
in vec3 col_to_frag;
in vec2 tex_to_frag;

uniform float t;

uniform sampler2D our_texture;

void main() {
    FragColor = texture(our_texture, tex_to_frag);
}
