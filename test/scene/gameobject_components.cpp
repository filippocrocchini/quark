/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include <memory>
#include "scene.h"

class TComp : public Component{
public:
    TComp(int num) : num(num) {}
    int GetNum() { return num; }
private:
    int num;
};

int main() {
    /*GameObject* go;

    go = s.CreateGameObject("Go");
    go->AddComponent<TComp>(11);

    if(s.GetGameObject("Go")->GetComponent<TComp>()->GetNum() == 11) {
        s.DeleteGameObject("Go");
        if(s.GetGameObject("Go") == nullptr) return 0;
    }
    return 1;*/
}
