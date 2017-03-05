package it.filippocrocchini.engine.common;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import it.filippocrocchini.engine.common.component.Component;
import it.filippocrocchini.engine.common.graphics.Transform;

public abstract class GameObject extends Toggleable{
	public volatile Transform transform;
	
	protected GameObject parent;
	protected List<GameObject> children;
	protected Map<String, Component> components;
	
	protected GameObject(GameObject parent) {
		transform = new Transform();
		this.parent = parent;
		children = new ArrayList<GameObject>();
		components = new HashMap<String, Component>();
	}
	
	public boolean isEnabled() {
		if(parent != null)
			return isEnabled && parent.isEnabled();
		return isEnabled;
	}
	
	public abstract void onLoad();
	public abstract void cleanup();

	
	public GameObject getParent() {
		return parent;
	}

	protected void setParent(GameObject parent) {
		this.parent.removeChild(this);
		
		this.parent = parent;
		
		this.parent.addChild(this);
	}

	public List<GameObject> getChildren() {
		return children;
	}

	public void addChild(GameObject child) {
		children.add(child);
	}
	
	public void removeChild(GameObject child) {
		while(children.remove(child));
		Engine.getGameObjectManager().detachGameObject(child);
	}

	public Collection<Component> getComponents() {
		return components.values();
	}
	
	public void addComponent(Component component) {
		components.put(component.getName(), component);
	}
	
	public Component getComponentByName(String name) {
		return components.get(name);
	}
	
	public void removeComponent(Component component) {
		while(components.remove(component.getName()) != null);
		Engine.getGameObjectManager().detachComponent(component);
	}

}
