uniforms <
	mat4 uModelMatrix;
	mat4 uNormalMatrix;
	mat4 uViewMatrix;
	mat4 uProjectionMatrix;
	vec3 uColor;
>

attributes <
	vec3 position;
	vec3 normal;
>

vertex_output <
	vec3 normal;
>

vertex[450 core]<

	void main() {
		vertex_output.normal = normalize((uNormalMatrix * vec4(normal,1)).xyz);

	    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0);
	}
>

fragment[450 core] -> (vec4 o_color) <
	precision highp float;
	
	vec3 sunColor = vec3(1,1,0.9);
	vec3 backColor = vec3(0.9,1,1);
	
	void main() {
		vec3 color = uColor;
		color += sunColor * max(0.05, dot(vertex_output.normal , normalize(vec3(.5,1,-.5)))) * 0.2;
		color += backColor * max(0.05, dot(vertex_output.normal , normalize(vec3(-.5,-1,.5)))) * 0.05;
		
	    o_color = vec4(color,1);
	}
>