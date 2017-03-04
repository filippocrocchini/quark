#pragma once

#include <unordered_set>
#include <map>
#include <memory>

class GameObject;
class Toggleable;
class Component;


class Toggleable {
public:
	bool enabled = true;
	void toggle();
	void enable();
	void disable();
};

class Component : public Toggleable{
public:
	const static std::string name;
	std::shared_ptr<GameObject> parent = nullptr;

	Component(std::shared_ptr<GameObject>);
};

class GameObject : public Toggleable {
public:
	//Do not modify, this is only for handling instances of the same class in the scene.
	uint32_t _id;
	std::shared_ptr<GameObject> parent;
	std::unordered_set<std::shared_ptr<GameObject>> children;
	std::map<std::string, std::shared_ptr<Component>> components;

	GameObject(std::shared_ptr<GameObject> parent);

	std::shared_ptr<Component> getComponentByName(std::string);
	void addComponent(std::shared_ptr<Component>);
	void removeComponent(std::shared_ptr<Component>);
	
	void addChild(std::shared_ptr<GameObject>);
	void removeChild(std::shared_ptr<GameObject>);
};

