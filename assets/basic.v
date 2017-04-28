#version 430 core

uniform int hello;
uniform float ponzino;
uniform vec4 color;

out float a;

void main(){
	a = 3;
	gl_Position = vec4(0,0,0,1);
}