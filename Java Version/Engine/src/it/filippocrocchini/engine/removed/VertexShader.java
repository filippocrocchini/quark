package it.filippocrocchini.engine.removed;

import static org.lwjgl.opengl.ARBVertexShader.*;

public class VertexShader extends ShaderResource {

	public VertexShader(String pathToFile) {
		super(GL_VERTEX_SHADER_ARB, pathToFile);
	}
}
