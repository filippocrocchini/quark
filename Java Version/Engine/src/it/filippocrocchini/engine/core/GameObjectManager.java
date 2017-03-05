package it.filippocrocchini.engine.core;

import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import it.filippocrocchini.engine.common.Engine;
import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.component.Component;
import it.filippocrocchini.engine.common.component.Renderable;
import it.filippocrocchini.engine.common.component.Updatable;
import it.filippocrocchini.engine.common.graphics.particles.ParticleSystem;

//FIXME: This class needs a serious cleanup job.
public class GameObjectManager{
	public static final Logger LOGGER = Logger.getLogger(GameObjectManager.class.getName());

	private List<GameObject> gameObjects;
	
	
	public GameObjectManager() {
		gameObjects = new ArrayList<GameObject>();
	}
	
//	//: useless method
//	@Deprecated
//	public GameObject createGameObject(Class<? extends GameObject> T){
//		GameObject object = null;
//		
//		try {
//			object = T.newInstance();
//		} catch (Exception e) {
//			LOGGER.log(Level.SEVERE, "Error instantiating new GameObject.", e);
//			return null;
//		}
//		LOGGER.log(Level.INFO, "Created new instance of GameObject, class type: " + T.getSimpleName());
//		return object;
//	}
//	
//	//: useless method
//	@Deprecated
//	public Component createComponent(GameObject parent, Class<? extends Component> T){
//		Component component = null;
//		
//		try {
//			component = T.newInstance();
//		} catch (Exception e) {
//			LOGGER.log(Level.SEVERE, "Error instantiating new Component.", e);
//			return null;
//		}
//		component.setParentGameObject(parent);
//		parent.addComponent(component);
//		
//		LOGGER.log(Level.INFO, "Created new instance of Component, class type: " + T.getSimpleName());
//		return component;
//	}
	
	public void detachGameObject(GameObject go) {
		removeGameObject(go);
	}
	
	public void detachComponent(Component c) {
		unRegisterComponent(c);
	}

	
	public void addGameObject(GameObject object) {
		for(GameObject gameObject : object.getChildren()) {
			addGameObject(gameObject);
		}

		gameObjects.add(object);

		for(Component component : object.getComponents()) {
			registerComponent(component);
		}
				
		LOGGER.log(Level.INFO, "Added new GameObject, class type: " + object.getClass().getSimpleName());
		object.onLoad();
	}
	
	/*TODO: Should this class handle GameObject and Component addition and deletion?
	There could be a GameObject Factory that handles stuff like "Engine.updater.registerUpdatable((Updatable) comp);",
	otherwise that could be handled directly by the GameObject constructor.
	*/
	public void removeGameObject(GameObject object) {
		object.cleanup();
		
		for(Component c : object.getComponents()) {
			object.removeComponent(c);
		}
		
		while(gameObjects.remove(object));
	}
	
	
	public void registerComponent(Component comp) {
		if(checkComponent(comp)) {
			LOGGER.log(Level.INFO, "Added new Component, class type: " + comp.getClass().getSimpleName());

			if(comp instanceof Updatable){
				Engine.updater.registerUpdatable((Updatable) comp);
			}
			if(comp instanceof Renderable){
				Engine.renderer.registerRenderable((Renderable) comp);
			}
			if(comp instanceof ParticleSystem){
				Engine.particleManager.addParticleSystem((ParticleSystem) comp);
			}
		}
	}

	public void unRegisterComponent(Component comp) {
		if(comp instanceof Updatable){
			Engine.updater.unRegisterUpdatable((Updatable) comp);
		}
		if(comp instanceof Renderable){
			Engine.renderer.unRegisterRenderable((Renderable) comp);
		}
		if(comp instanceof ParticleSystem){
			Engine.particleManager.removeParticleSystem((ParticleSystem) comp);
		}
	}
	
	private boolean checkComponent(Component comp) {
		if(comp.getParentGameObject() == null) {
			LOGGER.log(Level.WARNING, comp.toString() + " <- This Component is not attached to any GameObject.");
			return false;
		}
		return true;
	}
}
