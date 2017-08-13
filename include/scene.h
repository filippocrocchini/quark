/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"
#include "renderer.h"

class Stage;

class Scene {
public:
    GameObject* CreateGameObject(const std::string& name);
    void DeleteGameObject(const std::string& name);
    GameObject* GetGameObject(const std::string& name);

    void Update(double delta);
    void Render(Renderer* renderer);

    const std::string& GetName() { return name; }
private:
    friend class Stage;
    Scene(const std::string& name);
    Scene();

    std::string name;
    std::map<std::string, std::unique_ptr<GameObject>> gameobjects;
};

#endif  // SCENE_H
