#pragma once

#include <unordered_set>
#include <map>

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
	GameObject* parent = nullptr;

	Component(GameObject*);
};

class GameObject : Toggleable {
public:
	GameObject* parent;
	std::unordered_set<GameObject*> children;
	std::map<std::string, Component*> components;

	Component* getComponentByName(std::string);
	void addComponent(Component*);
	void removeComponent(Component*);
	
	void addChild(GameObject*);
	void removeChild(GameObject*);
};

