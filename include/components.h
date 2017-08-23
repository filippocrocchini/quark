/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <cxxabi.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "toggleable.h"
#include "material.h"

class GameObject;

class Component : public Toggleable {
public:
    virtual ~Component() = default;

    template<typename T, typename... Args>
    static T* Create(Args&&... args) {
      static_assert(std::is_base_of<Component, T>::value);
      T* comp = new T{std::forward<Args>(args)...};
      comp->name = abi::__cxa_demangle(typeid(T).name(), 0,0,0);
      return comp;
    }

    template<typename T, typename... Args>
    static std::unique_ptr<T> CreateUnique(Args&&... args) {
      return std::move(std::unique_ptr<T>(Create<T>(std::forward<Args>(args)...)));
    }

    void SetParent(GameObject* parent);
    const std::string& GetName() const { return name; }
    virtual bool isEnabled() override;

protected:
    GameObject* parent;
    Component() = default;
private:
    std::string name;
};

class Behaviour : public Component {
public:
  virtual ~Behaviour() = default;

  virtual void Update(double delta) = 0;
  virtual void LateUpdate(double delta) = 0;
};

class Transform : public Component {
public:
    bool dirty = true, dirty_2d = true;
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 pivot;

    Transform(const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation, const glm::vec3& pivot) :
         position(position), scale(scale), rotation(rotation), pivot(pivot) {}

    Transform(const glm::vec3& position, const glm::vec3& scale, const glm::quat& rotation) :
         Transform(position, scale, rotation, glm::vec3(0)){}

    const glm::mat4& GetMatrix();
    const glm::mat3& GetMatrix2D();
    const glm::vec3& GetPosition() { return position; }

    const glm::vec3& GetPivot() { return pivot; }
    const glm::vec3& GetScale() { return scale; }
    const glm::quat& GetRotation() { return rotation; }

    void SetPosition(const glm::vec3& position) { dirty = true; dirty_2d = true; this->position = position; }
    void SetPivot(const glm::vec3& pivot) { dirty = true; dirty_2d = true; this->pivot = pivot; }
    void SetScale(const glm::vec3& scale) { dirty = true; dirty_2d = true; this->scale = scale; }
    void SetRotation(const glm::quat& rotation) { dirty = true; dirty_2d = true; this->rotation = rotation; }

    glm::vec2 ApplyTo(const glm::vec2& vector);
private:

    glm::mat4 matrix;
    glm::mat3 matrix_2d;
};

class Sprite : public Component {
public:
    Material* material;
    glm::vec4 color;

    Sprite(Material* material, glm::vec4 color) : material(material), color(color) {}
    Sprite(Material* material) : Sprite(material, glm::vec4(1)) {}
    virtual ~Sprite() = default;
};

#endif  // COMPONENTS_H
