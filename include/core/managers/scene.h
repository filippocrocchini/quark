#pragma once
#include <vector>
#include <memory>

#include "../object/gameobject.h"

struct Scene {
	std::map<uint32_t, std::shared_ptr<GameObject>> gameObjects;
};


//This class interfaces directly with the engine.
class SceneManager {
public:
	std::shared_ptr<Scene> currentScene;
	

	//TODO: Find a (fast) way to update the scene graph on GameObject::addChild and GameObject::removeChild
	/*
	Adds/Removes the Object to the 'root' of the scene, and updates both the renderer and the updater.
	*/
	void addGameObject(std::shared_ptr<GameObject>);
	void removeGameObject(std::shared_ptr<GameObject>);
};