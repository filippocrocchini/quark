/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "scene.h"

#include <memory>

Scene::Scene(const std::string& name) : name(name) {}
Scene::Scene() : Scene("Default Scene") {}

GameObject* Scene::CreateGameObject(const std::string& name){
  gameobjects.insert(std::make_pair(name, std::unique_ptr<GameObject>(new GameObject())));
  return GetGameObject(std::move(name));
}
//After calling this method every pointer to the GameObject is invalid.
void Scene::DeleteGameObject(const std::string& name){
  gameobjects.erase(name);
}

GameObject* Scene::GetGameObject(const std::string& name){
  auto obj_itr = gameobjects.find(name);
  if(obj_itr==gameobjects.end()) return nullptr;
  return obj_itr->second.get();
}

//NOTE: This thread should be running updates
void Scene::Update(double delta){
  for(auto go_itr = gameobjects.begin(); go_itr != gameobjects.end(); go_itr++){
      if(go_itr->second->isEnabled()){
        auto behaviours = go_itr->second->GetBehaviours();
        for(auto b_itr = behaviours.begin(); b_itr != behaviours.end(); b_itr++)
            (*b_itr)->Update(delta);
        for(auto b_itr = behaviours.begin(); b_itr != behaviours.end(); b_itr++)
          (*b_itr)->LateUpdate(delta);
      }
  }
}

//NOTE: This thread should be running graphics
void Scene::Render(Renderer* renderer){
    for(auto go_itr = gameobjects.begin(); go_itr != gameobjects.end(); go_itr++){
        if(go_itr->second->isEnabled()){
        auto transform = go_itr->second->GetComponent<Transform>();

        if(transform){
            auto sprite = go_itr->second->GetComponent<Sprite>();
            if(sprite)
                renderer->SubmitSprite(sprite, transform);
        }
    }
    }
}
