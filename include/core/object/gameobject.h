#pragma once

#include <unordered_set>
#include <map>
#include <memory>

class GameObject;

class Toggleable {
protected:
	bool enabled = true;
public:
	bool isEnabled();
	void toggle();
	void enable();
	void disable();
	virtual ~Toggleable() {};
};

class Component : public Toggleable{
public:
	GameObject* parent = nullptr;

	Component(GameObject&);

	bool isEnabled();
};

class Updatable : public Component {
public:
	Updatable(GameObject& parent) : Component(parent) {};
	virtual void update(double delta) = 0;
};

class Renderable : public Component {
public:
	Renderable(GameObject& parent) : Component(parent) {};
	virtual void render() = 0;
};


class GameObject : public Toggleable {
public:
	//Do not modify, this is only for handling instances of the same class in the scene.
	//uint32_t _id;
	GameObject* parent;

	//If the scene is nullptr this object is not registered in the engine,
	//therefore it's not going to be updated/rendered.
	
	std::unordered_set<GameObject*> children;
	std::unordered_set<Component*> components;

	//If the parent is nullptr then this object is a root.
	GameObject(GameObject* parent = nullptr);

	void addChild(GameObject&);
	void removeChild(GameObject&);

	//Component* getComponentByName(std::string);
	
	void addComponent(Component&);

	void removeComponent(Component&);

	bool isEnabled();
};

