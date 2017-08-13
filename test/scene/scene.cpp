#include <memory>

#include "stage.h"

class TestBehaviour : public Behaviour{
public:
    bool updated = false, late_updated = false;
    double time = 0;
    virtual void Update(double delta) {
        updated = true;
        time += delta;
        if(time > 1){
            time-=1;
            std::cout << "One second passed away\n";
        }
    }
    virtual void LateUpdate(double delta) {
        late_updated = updated;
    }

    bool isUpdated(){
        return updated && late_updated;
    }
};

int main(){
    LoopController lc;
    Stage stage{&lc};

    Scene* s = stage.CreateScene("start");
    GameObject* go = s->CreateGameObject("Go");

    go->AddComponent<TestBehaviour>();
    go->AddComponent<RectangleMesh>(-.2f, -.5f, 1.f, 1.f, 1.f, 0.f, 1.f);


    stage.SetCurrentScene("start");
    stage.Start();
    stage.Join();

    if(s->GetGameObject("Go")->GetComponent<TestBehaviour>()->isUpdated()) return 0;
    return 1;
}
