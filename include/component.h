#ifndef COMPONENT_H
#define COMPONENT_H

#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <cxxabi.h>

#include "toggleable.h"

class GameObject;

class Component : public Toggleable {
public:
    void SetParent(GameObject* parent);
    const std::string& GetName() const { return name; }
    virtual bool isEnabled() override;
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

#endif  // COMPONENT_H
