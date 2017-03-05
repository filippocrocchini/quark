uniforms <
	mat4 uModelMatrix;
	mat4 uNormalMatrix;
	mat4 uViewMatrix;
	mat4 uProjectionMatrix;
	vec3 uColor;
>

attributes <
	vec3 position;
>

vertex_output <
	vec3 color;
>

vertex[450 core] -> ()<

	void main(void) {
		vertex_output.color = uColor;
	    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0);
	}
>

fragment[450 core] -> (vec4 o_color) <
	precision highp float;

	void main(void) {
	    o_color = vec4(vertex_output.color,1);
	}
>