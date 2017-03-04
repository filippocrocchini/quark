#include "../include/core/object/gameobject.h"

const std::string Component::name = "Component";

//_________________Component_________________
Component::Component(std::shared_ptr<GameObject> parent) {
	this->parent = parent;
}


//_________________Toggleable_________________
void Toggleable::toggle() {
	enabled = !enabled;
}

void Toggleable::enable() {
	enabled = true;
}

void Toggleable::disable() {
	enabled = false;
}



//_________________GameObject_________________
GameObject::GameObject(std::shared_ptr<GameObject> parent)
{
	this->parent = parent;
}

std::shared_ptr<Component> GameObject::getComponentByName(std::string name) {
	std::shared_ptr<Component> c = nullptr;
	try {
		c = components[name];
	}
	catch (std::out_of_range e) {
		return nullptr;
	}
	return c;
}

void GameObject::addComponent(std::shared_ptr<Component> c) {
	components.insert(std::pair<std::string, std::shared_ptr<Component>>(c->name, c));
}

void GameObject::removeComponent(std::shared_ptr<Component> c) {
	components.erase(c->name);
}
	
void GameObject::addChild(std::shared_ptr<GameObject> child) {
	children.insert(child);
}

void GameObject::removeChild(std::shared_ptr<GameObject> child) {
	children.erase(child);
}