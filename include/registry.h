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
    void Register(const Key& key, Value* value_pointer){
        cache.emplace(key, std::unique_ptr<Resource>{value_pointer});
    }

    template<typename... Args>
    void Emplace(const Key& key, Args&&... args){
        Register(key, new Value{std::forward<Args>(args)...});
    }

    Value* Get(const Key& key){
        auto res = cache.find(key);
        if(res == cache.end()) return nullptr;
        return (res->second).get();
    }

    std::unique_ptr<Value> Detach(Key key){
        auto removed_itr = cache.find(key);
        if(removed_itr == cache.end()) return nullptr;
        Value* removed = removed_itr->second.release();
        cache.erase(key);
        return std::move(std::unique_ptr<Value>{removed});
    }

    void Remove(Key key){
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
