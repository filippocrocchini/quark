/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef GAMEOBJECT_H // NOLINT()
#define GAMEOBJECT_H

#include <cxxabi.h>

#include <map>
#include <unordered_set>
#include <memory>
#include <string>
#include <utility>

#include "./toggleable.h"
#include "./components.h"

class Scene;

class GameObject : public Toggleable {
 public:
    GameObject* RemoveComponent(const std::string& name);

    template <typename T, typename... Args>
    GameObject* AddComponent(Args&&... args) {
      return AddComponent(Component::CreateUnique<T>(std::forward<Args>(args)...));
    }

    template <typename T>
        T* GetComponent(const std::string& name) {
        auto cmp_itr = components.find(name);
        if (cmp_itr == components.end())
            return nullptr;
        return dynamic_cast<T*>(cmp_itr->second.get());
    }

    template <typename T>
    T* GetComponent() {
        char* name = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);
        T* result = GetComponent<T>(name);
        free(name);
      return result;
    }

    const std::string& GetName() const { return name; }
    const std::unordered_set<Behaviour*>& GetBehaviours() const { return behaviours; }

 private:
    friend class Scene;
    std::map<std::string, std::unique_ptr<Component>> components;
    std::unordered_set<Behaviour*> behaviours;
    std::string name;

    GameObject() = default;
    GameObject* AddComponent(std::unique_ptr<Component> component);
};

#endif  // NOLINT() GAMEOBJECT_H
