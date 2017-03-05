package it.filippocrocchini.engine.core;

import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL.*;
import static org.lwjgl.opengl.GL11.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.lwjgl.glfw.GLFW;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.component.Renderable;
import it.filippocrocchini.engine.common.graphics.model.Material;
import it.filippocrocchini.engine.common.graphics.model.Model;
import it.filippocrocchini.engine.common.resource.FutureResource;
import it.filippocrocchini.engine.core.debug.FPSLogger;

public class Renderer extends Thread{
	public static final Logger LOGGER = Logger.getLogger(Renderer.class.getName());
	
	private FPSLogger fpsLogger;
	private long window;
	private boolean mouse_captured;
	
	private boolean isVSyncEnabled;
	private int width,height;
	private String windowTitle;
	
	private List<Renderable> renderables;
	private Stack<FutureResource<?>> resourcesToLoad;
	private ArrayList<FutureResource<?>> loaded  = new ArrayList<>();

	//TODO: Get rid of these, they were not a bad idea so it would not be bad to make something similar.
	//private float missingShaderTimeout;
	//private float missingCameraTimeout;

	//TODO: Make input class
	private boolean isF3down = false;
	
	public Renderer(String windowTitle, int width, int height, boolean isVSyncEnabled, String threadName) {
		super(threadName);
		this.windowTitle = windowTitle;
		this.height = height;
		this.width = width;
		this.isVSyncEnabled = isVSyncEnabled;
		this.renderables = new ArrayList<Renderable>();
		this.resourcesToLoad = new Stack<>();
		this.fpsLogger = new FPSLogger();
	}

	@Override
	public void run() {
		try{
			init();
		} catch (RuntimeException e) {
			LOGGER.log(Level.SEVERE, "Error initializing the Renderer.", e);
			return;
		}
		renderLoop();
	}
	
	public void init() throws RuntimeException{
		if(!glfwInit())
			throw new RuntimeException("Failed initializing GLFW");
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);     
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);     
	    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);    
	    glfwWindowHint(GLFW_SAMPLES, 4);
	    
//		window = glfwCreateWindow(width, height, windowTitle, glfwGetPrimaryMonitor(), 0);
		window = glfwCreateWindow(width, height, windowTitle, 0, 0);
		
		glfwMakeContextCurrent(window);
		
		if(isVSyncEnabled)
			glfwSwapInterval(-1);
		else 
			glfwSwapInterval(0);
		
		createCapabilities();
		
        glViewport(0, 0, width, height);
        glfwShowWindow(window);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	

    
	public void renderLoop() {
		while(Engine.isRunning()) {
			
			if(resourcesToLoad.size() > 0) {
				FutureResource<?> r = resourcesToLoad.pop();
				r.glLoad();
				loaded.add(r);
			}
			
			glfwPollEvents();
			
			if(GLFW.glfwGetMouseButton(Engine.getWindow(), GLFW.GLFW_MOUSE_BUTTON_1) == GLFW.GLFW_PRESS && !mouse_captured) {
				GLFW.glfwSetInputMode(Engine.getWindow(), GLFW.GLFW_CURSOR, GLFW.GLFW_CURSOR_DISABLED);
				mouse_captured = true;
			}
			
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_ESCAPE) == GLFW.GLFW_PRESS && mouse_captured) {
				mouse_captured = false;
				GLFW.glfwSetInputMode(Engine.getWindow(), GLFW.GLFW_CURSOR, GLFW.GLFW_CURSOR_NORMAL);
			}

			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_F3) == GLFW.GLFW_PRESS && !isF3down) {
				isF3down = true;
				Engine.toggleDebugInfo();
			}
			
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_F3) == GLFW.GLFW_RELEASE && isF3down) {
				isF3down = false;
			}
			
			if(GLFW.glfwGetKey(Engine.getWindow(), GLFW.GLFW_KEY_F1) == GLFW.GLFW_PRESS && !mouse_captured) {
				Engine.stop();
			}
			
			if(Engine.mainCamera != null) {
				
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
					fpsLogger.logFPS();
					
				if(Engine.isShowingDebugInfo()) {
					Engine.getDebugShader().bind();
					Engine.getDebugShader().setProjectionMatrixUniform(Engine.mainCamera.getProjectionMatrix());
					Engine.getDebugShader().setViewMatrixUniform(Engine.mainCamera.getViewMatrix());
				}
				
				for (Renderable renderable : renderables) {
					if(renderable.isEnabled()) {	
						if(Engine.isShowingDebugInfo()) {
							renderable.renderDebugInfo();
						}
						if(renderable.hasCustomRender()) {
							renderable.render();
						}
						if(renderable.isAdvancedGl()){
							//TODO: Add secure default model and shader to use when resources fail to load. 
							Model model = renderable.getModel();
							Material material = renderable.getMaterial();
							
							if(model != null && material != null)
								model.render(material, Engine.mainCamera.getProjectionMatrix(), Engine.mainCamera.getViewMatrix(), renderable.getModelMatrix());
						}
					}
				}
				Engine.particleManager.update();
				Engine.particleManager.render();
			}
			glfwSwapBuffers(window);
		}
		cleanup();
	}
	
	private void cleanup() {
		for(FutureResource<?> r : loaded) {
			r.cleanup();
		}
	}
	
//	private void renderModel(Model model) {
//		if(model == null) return;
//		for(Mesh mesh : model.meshes) {
//			glBindVertexArray(mesh.vao);
//			glDrawElements(GL_TRIANGLES, mesh.elementCount, GL_UNSIGNED_INT, 0);
//			glBindVertexArray(0);
//		}
//	}

	public boolean windowExists() {
		return window != 0L;
	}

	public boolean windowShouldClose() {
		return glfwWindowShouldClose(window);
	}

	public void registerRenderable(Renderable r) {
		renderables.add(r);
	}
	
	public void unRegisterRenderable(Renderable r) {
		while(renderables.remove(r));
	}
	
	public void registerResource(FutureResource<?> r) {
		resourcesToLoad.push(r);
	}

	public float getWindowAspectRatio() {
		return width/(float)height;
	}

	public long getWindow() {
		return window;
	}

	public boolean isMouseCaptured() {
		return mouse_captured;
	}
}
