package it.filippocrocchini.engine.common;

import java.util.HashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.python.util.PythonInterpreter;

import it.filippocrocchini.engine.common.graphics.Camera;
import it.filippocrocchini.engine.common.graphics.shaders.ShaderProgram;
import it.filippocrocchini.engine.common.resource.FutureResource;
import it.filippocrocchini.engine.common.resource.Resource;
import it.filippocrocchini.engine.core.GameObjectManager;
import it.filippocrocchini.engine.core.Renderer;
import it.filippocrocchini.engine.core.Updater;
import it.filippocrocchini.engine.core.particles.ParticleManager;
import it.filippocrocchini.engine.core.resource.ResourceLoader;

//TODO: This class shouldn't be a GameObject and Component factory, implement proper classes to do so.
//TODO: Maybe it would be a good idea if I implemented a DESTROY_ENGINE thread that waits until all threads exit. 
public final class Engine {
	public static final Logger LOGGER = Logger.getLogger(Engine.class.getName());
	 
	private static Thread mainThread;
	public static PythonInterpreter python;
	private static GameObjectManager objectManager;
	private static ResourceLoader resourceLoader;
	
	public static Updater updater;
	public static Renderer renderer;
	public static ParticleManager particleManager;
	
	public static HashMap<String, FutureResource<Resource>> shaders; 

	public static Camera mainCamera;
	
	private static boolean isRunning;
	private static boolean isShowingDebugInfo = false;

	private static ShaderProgram debugShader;

	public static void create(String windowTitle, int width, int height, boolean vsSync) {
		if(objectManager != null) return;
		
		python = new PythonInterpreter();
		python.setOut(System.err);
		python.exec("import sys");
		python.exec("sys.path.insert(0, './shaderutils')");
		python.exec("try:\n	from myparser import *\nexcept ImportError:\n	print('Failed loading Shader Utils scripts!!!!')");
		python.exec("script = None");
		
		mainThread = Thread.currentThread();

		resourceLoader = new ResourceLoader("RESOURCE_LOADER_THREAD", 20);
		renderer = new Renderer(windowTitle, width, height, vsSync, "RENDER_THREAD");
		updater = new Updater("GAME_LOOP_THREAD");

		objectManager = new GameObjectManager();
		particleManager = new ParticleManager();
	}
	
	public static void start() {
		LOGGER.log(Level.INFO, "Starting the Engine...");
		isRunning = true;
		shaders = new HashMap<>();
		mainCamera = null;
		
		resourceLoader.start();
		renderer.start();
		updater.start();
		
		loadShader("Debug");
		loadShader("Particle");
	}
	
	public static boolean isRunning() {
		if(isRunning && renderer.windowExists())
			return !renderer.windowShouldClose();
		return isRunning;
	}
	
	public double getDelta() {
		return updater.getDeltaTime();
	}

	public static GameObjectManager getGameObjectManager() {
		return objectManager;
	}

	public static FutureResource<Resource> loadResource(Resource r) {
		FutureResource<Resource> resource = new FutureResource<Resource>(r);
		resourceLoader.loadResource(resource);
		return resource;
	}
	
	public static void loadShader(String shaderName) throws AssertionError {
		if(isRunning()) {
			shaders.put(shaderName, loadResource(new ShaderProgram(shaderName)));
		} else {
			throw new AssertionError("The Engine must be running to load the shader");
		}
	}
	
	public static void stop() {
		isRunning = false;
		
		if(mainThread.isAlive())
			mainThread.interrupt();
		
		if(resourceLoader.isAlive())
			resourceLoader.interrupt();
		//renderer.stop()
		//updater.stop()
	}
	
	public static float getWindowAspectRatio() {
		return renderer.getWindowAspectRatio();
	}

	public static void setMainCamera(Camera camera) {
		mainCamera = camera;
	}

	public static long getWindow() {
		return renderer.getWindow();
	}

	public static boolean isMouseCaptured() {
		return renderer.isMouseCaptured();
	}
	
	public static ShaderProgram getShader(String name) {
		try {
			return (ShaderProgram) shaders.get(name).get(10, TimeUnit.MILLISECONDS);
		} catch (InterruptedException | ExecutionException | TimeoutException e) {
			e.printStackTrace();
			return null;
		}
	}

	public static ShaderProgram getDebugShader() {
		return debugShader;
	}
	
	public static boolean hasShader(String shaderName) {
		return shaders.containsKey(shaderName);
	}
	
	public static boolean isShowingDebugInfo() {
		if(debugShader == null) {
			debugShader = getShader("Debug");
		}
		return isShowingDebugInfo && debugShader != null;
	}
	
	public static void setShowDebugInfo(boolean showDebugInfo) {
		isShowingDebugInfo = showDebugInfo;
	}

	public static void toggleDebugInfo() {
		isShowingDebugInfo = !isShowingDebugInfo;
	}
}
