package it.filippocrocchini.engine.common.component;

import java.util.logging.Logger;

import it.filippocrocchini.engine.common.GameObject;
import it.filippocrocchini.engine.common.Toggleable;

public abstract class Component extends Toggleable{
	public static final Logger LOGGER = Logger.getLogger(Component.class.getName());

	protected GameObject parentGameObject;
		
	public Component(GameObject parent) {
		setParentGameObject(parent);
	}

	public GameObject getParentGameObject() {
		return parentGameObject;
	}
	
	public void setParentGameObject(GameObject parentGameObject) {
		this.parentGameObject = parentGameObject;
	}
	
	public boolean isEnabled() {
		return isEnabled && parentGameObject.isEnabled();
	}
	
	public String getName() { return this.getClass().getSimpleName();}
}
