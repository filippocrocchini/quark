#pragma once
#include <vector>
#include <memory>

#include "../object/gameobject.h"

/*
Scene {
	shared->GameObject vector;
	When an object is added/removed to the scene, update all the fields "Scene" in
	every child and register/unregister all their components.
}

GameObject {
	shared->Scene;
	When a child is added/removed to this GameObject tell the scene that a
	new GameObject has been added/removed.
}
*/

class Scene {
public:
	std::vector<GameObject*> rootGameObjects;

	std::unordered_set<Renderable*> renderables;
	std::unordered_set<Updatable*> updatables;

	//TODO: Find a (fast) way to update the scene graph on GameObject::addChild and GameObject::removeChild
	/*
	Adds/Removes the Object to the 'root' of the scene, and updates both the renderer and the updater.
	*/
	void addRootGameObject(GameObject&);
	void removeRootGameObject(GameObject&);

	void registerGameObject(GameObject&);
	void unregisterGameObject(GameObject&);

	void registerComponent(Component&);
	void unregisterComponent(Component&);
};