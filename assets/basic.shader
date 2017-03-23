#version 440 core

uniform mat4 bla;

in vec4 icolor;

out vec4 ocolor;
out vec2 a;

void main() {
	ocolor = icolor;
	gl_Vertex = vec4(1, 1, 1, 0);
}

//-----

#version 440 core

uniform mat4 bla;

out vec4 color;
in vec2 a;

void main() {
	color = vec4(0, 0, 0, 0);
}

//______________________

uniform {
	mat4 bla;
}

vertex (vec4 color) {
	vec2 a = color.xy;
}
-> geometry(a, color) {

}
-> fragment(a, color) {

}
-> (color)

#uniforms
mat4 bla;

#attributes
vec4 color;

vertex{
	vec2 a = color.rg;
	gl_Vertex = vec4(0,0,0,0);
	pass color, a;
}

geometry{
	pass color, a; 
}

fragment{
	pass color + vec4(a,0,0);
}
