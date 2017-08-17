#include "quark.h"

class Dummy : public Resource {
public:
    int value;
    Dummy(int value):value(value){
    }

    virtual bool Load() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return true;
    }

    virtual void onLoad() override {}

    virtual void onFail() override {}
};


Quark eng{"Hello", 1080, 720};

int main(){
    eng.Start();

    eng.LoadResource<Dummy>("One", 1);
    eng.WaitForResources();

    Dummy* one = eng.GetResource<Dummy>("One");

    if(one == nullptr || one->value != 1){
        eng.Stop();
        return 1;
    }
    eng.Stop();
    return 0;
}
