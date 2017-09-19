/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./scene.h"

#include <memory>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

Scene::Scene(const std::string& name, Camera* main_camera) : name(name), main_camera(main_camera) {}
Scene::Scene(const std::string& name) : Scene(name, nullptr) {}
Scene::Scene() : Scene("Default Scene") {}

GameObject* Scene::CreateGameObject(const std::string& name) {
  gameobjects.insert(std::make_pair(name, std::unique_ptr<GameObject>(new GameObject())));
  return GetGameObject(std::move(name));
}
// After calling this method every pointer to the GameObject is invalid.
void Scene::DeleteGameObject(const std::string& name) {
  gameobjects.erase(name);
}

GameObject* Scene::GetGameObject(const std::string& name) {
  auto obj_itr = gameobjects.find(name);
  if (obj_itr == gameobjects.end()) return nullptr;
  return obj_itr->second.get();
}

// NOTE(filippocrocchini): This thread should be running updates
void Scene::Update(double delta) {
    std::vector<std::pair<Collider2D*, Transform*>> colliders;
    std::vector<std::pair<Collider2D*, Transform*>> triggers;

    for (auto go_itr = gameobjects.begin(); go_itr != gameobjects.end(); go_itr++) {
        if (go_itr->second->isEnabled()) {
            auto behaviours = go_itr->second->GetBehaviours();
            for (auto b_itr = behaviours.begin(); b_itr != behaviours.end(); b_itr++)
                (*b_itr)->Update(delta);
            for (auto b_itr = behaviours.begin(); b_itr != behaviours.end(); b_itr++)
                (*b_itr)->LateUpdate(delta);

            auto collider = go_itr->second->GetComponent<Collider2D>();
            if (collider) {
                auto transform = go_itr->second->GetComponent<Transform>();
                if (transform) {
                    if (collider->is_trigger) {
                        triggers.push_back(std::make_pair(collider, transform));
                    } else {
                        colliders.push_back(std::make_pair(collider, transform));
                    }
                }
            }
        }
    }

    for (auto c_itr = colliders.begin(); c_itr != colliders.end(); c_itr++) {
        for (auto t_itr = triggers.begin(); t_itr != triggers.end(); t_itr++) {
            float min_dist = (std::max(c_itr->second->scale.x, c_itr->second->scale.y) +
                            std::max(t_itr->second->scale.x, t_itr->second->scale.y))/2.f;
            float dist = glm::length2(c_itr->second->position - t_itr->second->position);
            if (dist < min_dist*min_dist) {
                c_itr->first->on_collision(t_itr->first);
            }
        }
    }
}

// NOTE(filippocrocchini): This thread should be running graphics
void Scene::Render(Renderer* renderer) {
    for (auto go_itr = gameobjects.begin(); go_itr != gameobjects.end(); go_itr++) {
        if (go_itr->second->isEnabled()) {
            auto transform = go_itr->second->GetComponent<Transform>();
            if (transform) {
                auto sprite = go_itr->second->GetComponent<Sprite>();
                if (sprite)
                    renderer->SubmitSprite(sprite, transform);
            }
        }
    }
}
