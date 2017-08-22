#version 400 core

layout (location = 0) in vec2 v_pos;
layout (location = 1) in mat3 v_model;
layout (location = 4) in vec4 v_color;
layout (location = 5) in vec2 v_uv;

uniform mat4 u_projection;
uniform vec4 u_color;

out vec4 frag_color;
out vec2 frag_pos;

void main(){
  frag_pos = v_uv;
  frag_color = v_color * u_color;
  gl_Position =  u_projection * vec4(v_model * vec3(v_pos,1),1);
}
