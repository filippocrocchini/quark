#include <memory>

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

int main(){
    LoopController lc;
    Stage stage{&lc};

    Scene* s = stage.CreateScene("start");
    s->CreateGameObject("Go")->AddComponent<TestBehaviour>();

    stage.SetCurrentScene("start");
    stage.Start();
    stage.Join();

    if(s->GetGameObject("Go")->GetComponent<TestBehaviour>()->isUpdated()) return 0;
    return 1;
}
