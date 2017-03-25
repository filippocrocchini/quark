uniforms:
	mat4 bla;

attributes:
	vec4 color;

vertex[440 core]:
	vec2 a = color.rg;
	gl_Vertex = vec4(0,0,0,0);
	pass color, a;

geometry[440 core]:
	pass color, a; 

fragment[440 core]:
	pass color + vec4(a,0,0);