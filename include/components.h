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
#include "sprite.h"
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
    Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation, glm::vec3 pivot) :
         position(position), scale(scale), rotation(rotation), pivot(pivot) {}

    Transform(glm::vec3 position, glm::vec3 scale, glm::quat rotation) :
         Transform(position, scale, rotation, glm::vec3(0)){}

    const glm::mat4& GetMatrix();
    const glm::vec3& GetPosition() { return position; }
    const glm::vec3& GetPivot() { return pivot; }
    const glm::vec3& GetScale() { return scale; }
    const glm::quat& GetRotation() { return rotation; }

    void SetPosition(const glm::vec3& position) { dirty = true; this->position = position; }
    void SetPivot(const glm::vec3& pivot) { dirty = true; this->pivot = pivot; }
    void SetScale(const glm::vec3& scale) { dirty = true; this->scale = scale; }
    void SetRotation(const glm::quat& rotation) { dirty = true; this->rotation = rotation; }
private:
    bool dirty = true;

    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 pivot;

    glm::mat4 matrix;
};

class RectangleMesh : public Component {
public:
    float x, y, width, height;
    float r, g, b;
    Shader* shader;

    RectangleMesh(float x, float y, float width, float height, float r, float g, float b, Shader* shader) :
         x(x), y(y), width(width), height(height), r(r), g(g), b(b), shader(shader){}
    virtual ~RectangleMesh() = default;
};

class SpriteRenderer : public Component {
public:
    Sprite* sprite;
    Material* material;
    glm::vec3 color;

    SpriteRenderer(Sprite* sprite, Material* material, glm::vec3 color) : sprite(sprite), material(material), color(color) {}
    SpriteRenderer(Sprite* sprite, Material* material) : SpriteRenderer(sprite, material, glm::vec3(1)) {}
    virtual ~SpriteRenderer() = default;
};

#endif  // COMPONENTS_H
