#include "core/managers/scene.h"

void Scene::addRootGameObject(GameObject& object) {
	rootGameObjects.push_back(&object);
	registerGameObject(object);
}

void Scene::removeRootGameObject(GameObject& object) {
	//@Implement
}

void Scene::registerGameObject(GameObject& object) {
	for each (GameObject* child in object.children)
	{
		registerGameObject(*child);
	}

	for each (Component* comp in object.components)
	{
		registerComponent(*comp);
	}
}

void Scene::unregisterGameObject(GameObject& object) {
	//@Implement
}

void Scene::registerComponent(Component& comp) {
	Renderable* rend = dynamic_cast<Renderable*>(&comp);
	if (rend != nullptr) {
		renderables.insert(rend);
	}

	Updatable* upd = dynamic_cast<Updatable*>(&comp);
	if (upd != nullptr) {
		updatables.insert(upd);
	}
}

void Scene::unregisterComponent(Component& comp) {
	//@Implement
}