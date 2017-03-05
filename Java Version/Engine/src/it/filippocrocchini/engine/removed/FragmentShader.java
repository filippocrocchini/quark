package it.filippocrocchini.engine.removed;

import static org.lwjgl.opengl.ARBFragmentShader.*;

public class FragmentShader extends ShaderResource {

	public FragmentShader(String pathToFile) {
		super(GL_FRAGMENT_SHADER_ARB, pathToFile);
	}
}
