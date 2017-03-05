#include "core/object/gameobject.h"

//_________________Component_________________
Component::Component(GameObject& parent) {
	this->parent = &parent;
}

bool Component::isEnabled() {
	if(parent != nullptr)
		return parent->isEnabled() && enabled;
	else
		return enabled;
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

bool Toggleable::isEnabled() {
	return enabled;
}

//_________________GameObject_________________
GameObject::GameObject(GameObject* parent)
{
	this->parent = parent;
}

//Component* GameObject::getComponentByName(std::string name) {
//	Component* c = nullptr;
//	try {
//		c = components[name];
//	}
//	catch (std::out_of_range e) {
//		return nullptr;
//	}
//	return c;
//}

void GameObject::addComponent(Component& c) {
	components.insert(&c);
}

void GameObject::removeComponent(Component& c) {
	components.erase(&c);
}
	
void GameObject::addChild(GameObject& child) {
	children.insert(&child);
}

void GameObject::removeChild(GameObject& child) {
	children.erase(&child);
}

bool GameObject::isEnabled() {
	if(parent != nullptr)
		return parent->isEnabled() && enabled;
	else
		return enabled;
}