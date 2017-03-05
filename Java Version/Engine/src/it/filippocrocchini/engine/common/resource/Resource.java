package it.filippocrocchini.engine.common.resource;

import java.io.IOException;

public interface Resource {
	/***
	 * Called when loading the resource from a file.
	 * <strong>OpenGL context: NO.<strong>
	 * @throws IOException 
	 */
	void onRawLoad() throws AssertionError, IOException;
	
	/***
	 * Called when loading the resource to OpenGL (if needed, otherwise leave it empty)
	 * <strong>OpenGL context: YES.<strong>
	 * @throws IOException 
	 */
	void onGlLoad() throws AssertionError;
	
	/***
	 * Called when cleaning up the resource with OpenGL (if needed, otherwise leave it empty)
	 * <strong>OpenGL context: YES.<strong>
	 * @throws IOException 
	 */
	void glCleanup();
	
}
