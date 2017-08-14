#include <memory>
#include <chrono>

#include "stage.h"

class TestBehaviour : public Behaviour{
public:
    bool updated = false, late_updated = false;

    virtual void Update(double delta) {
        updated = true;
    }
    virtual void LateUpdate(double delta) {
        late_updated = updated;
    }

    bool isUpdated(){
        return updated && late_updated;
    }
};

class MyStage : public Stage {
public:
    MyStage(LoopController* lc) : Stage(lc) {}
};

int main(){
    LoopController lc;
    MyStage stage{&lc};

    Scene* s = stage.CreateScene("start");
    GameObject* go = s->CreateGameObject("Go");

    go->AddComponent<TestBehaviour>();

    stage.SetCurrentScene("start");
    stage.Start();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    lc.Stop();

    stage.Join();

    if(s->GetGameObject("Go")->GetComponent<TestBehaviour>()->isUpdated()) return 0;
    return 1;
}
