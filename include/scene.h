/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef SCENE_H  // NOLINT()
#define SCENE_H

#include <map>
#include <string>
#include <memory>

#include "./gameobject.h"
#include "./renderer.h"
#include "./camera.h"

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
    Scene(const std::string& name, Camera* main_camera);
    explicit Scene(const std::string& name);
    Scene();

    std::string name;
    Camera* main_camera;
    std::map<std::string, std::unique_ptr<GameObject>> gameobjects;
};

#endif  // NOLINT() SCENE_H
