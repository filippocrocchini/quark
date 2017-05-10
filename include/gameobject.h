/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <unordered_set>
#include <memory>

class GameObject;

class Component : public Toggleable {
protected:
    Component(const GameObject& parent) : parent(&parent) {}
    virtual bool isEnabled() override;
private:
    GameObject* parent;
};

class GameObject : public Toggleable {
public:
    void AddChild();
    void RemoveChild();
    void AddComponent();
    void RemoveComponent();

    //GameObj

    virtual bool isEnabled() override;
private:
    GameObject* parent;
    std::unordered_set<GameObject*> children;
    std::unordered_set<Component*> components;
};

#endif  // GAMEOBJECT_H
