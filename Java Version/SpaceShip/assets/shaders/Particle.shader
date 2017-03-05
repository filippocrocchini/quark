uniforms <
	mat4 uModelMatrix;
	mat4 uNormalMatrix;
	mat4 uViewMatrix;
	mat4 uProjectionMatrix;
	vec3 uColor;
>

attributes <
	vec3 position;
	vec3 offset;
>

vertex_output <
	vec3 color;
>

vertex[450 core]<

	void main(void) {
		vec3 camera = (uViewMatrix * vec4(0,0,0,1)).xyz;
		vec3 pos = (uViewMatrix * vec4(position + offset,1)).xyz;
		
		float dist = distance(vec3(0,0,0),pos);
		float damping = exp(-dist * 0.01);
		vertex_output.color = uColor * damping;
				
	    gl_Position = uProjectionMatrix * uViewMatrix * vec4(position + offset, 1.0);
	}
>

fragment[450 core] -> (vec4 o_color) <
	precision highp float;

	void main(void) {
	    	o_color = vec4(vertex_output.color ,1);
	}
>