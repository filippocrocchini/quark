#version 400 core

in vec4 frag_color;
in vec2 frag_pos;

out vec4 color;

uniform sampler2D u_texture;
uniform int u_has_texture;

void main() {
  vec4 texture_color;
  if(u_has_texture == 1) {
    texture_color = texture(u_texture, frag_pos);
  } else {
    texture_color = vec4(1,1,1,1);
  }
  color = frag_color * texture_color;
}
