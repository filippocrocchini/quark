/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "gameobject.h"
#include "component.h"

bool Component::isEnabled(){
  if(!parent) return this->enabled;
  return parent->isEnabled() && this->enabled;
}

void Component::SetParent(GameObject* parent){
  this->parent = parent;
}

GameObject* GameObject::AddComponent(std::unique_ptr<Component> component){
  component->SetParent(this);

  Behaviour* b = static_cast<Behaviour*>(component.get());
  if(b) behaviours.insert(b);

  components.insert(std::make_pair(component->GetName(), std::move(component)));
  return this;
}

GameObject* GameObject::RemoveComponent(const std::string& name){
  auto com_itr = components.find(name);
  behaviours.erase(static_cast<Behaviour*>(com_itr->second.get()));
  components.erase(com_itr);
  return this;
}
