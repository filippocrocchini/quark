/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#ifndef REGISTRY_H
#define REGISTRY_H

#include <memory>
#include <unordered_map>

template <typename Key, typename Value>
class Registry {
public:

    bool Register(const Key& key, std::unique_ptr<Value> value_pointer){
        return cache.emplace(key, std::move(value_pointer)).second;
    }

    template<typename T>
    bool Register(const Key& key, std::unique_ptr<T> value_pointer){
        return cache.emplace(key, std::move(std::unique_ptr<Value>(static_cast<Value*>(value_pointer.release())))).second;
    }

    template<typename T, typename... Args>
    bool Emplace(const Key& key, Args&&... args){
        return Register(key, new Value{std::forward<Args>(args)...});
    }

    Value* Get(const Key& key){
        auto res = cache.find(key);
        if(res == cache.end()) return nullptr;
        return (res->second).get();
    }

    template<typename T>
    T* Get(const Key& key){
        return static_cast<T*>(Get(key));
    }

    std::unique_ptr<Value> Release(const Key& key){
        auto removed_itr = cache.find(key);
        if(removed_itr == cache.end()) return nullptr;
        Value* removed = removed_itr->second.release();
        cache.erase(key);
        return std::move(std::unique_ptr<Value>{removed});
    }

    template<typename T>
    std::unique_ptr<T> Release(const Key& key){
        Value* ptr = Release(key).release();
        return std::move(std::unique_ptr<T>(static_cast<T*>(ptr)));
    }

    void Remove(const Key& key){
        cache.erase(key);
    }

    void Clear(){
        cache.clear();
    }

    const int size(){
        return cache.size();
    }

private:
    std::unordered_map<Key, std::unique_ptr<Value>> cache;
};

#endif  // REGISTRY_H
