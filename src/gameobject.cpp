#include "../include/core/object/gameobject.h"

const std::string Component::name = "Component";

//_________________Component_________________
Component::Component(GameObject* parent) {
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
Component* GameObject::getComponentByName(std::string name) {
	Component* c = nullptr;
	try {
		c = components[name];
	}
	catch (std::out_of_range e) {
		return nullptr;
	}
	return c;
}

void GameObject::addComponent(Component* c) {
	components.insert(std::pair<std::string, Component*>(c->name, c));
}

void GameObject::removeComponent(Component* c) {
	components.erase(c->name);
}
	
void GameObject::addChild(GameObject* child) {
	children.insert(child);
}

void GameObject::removeChild(GameObject* child) {
	children.erase(child);
}