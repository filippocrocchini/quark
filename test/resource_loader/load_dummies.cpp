#include "resource_loader.h"

#include <chrono>
#include <thread>

class Dummy : public Resource {
public:
    int value;
    Dummy(int value):value(value){
    }

    virtual bool Load(){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return true;
    }

    virtual void onLoad(){}

    virtual void onFail(){}
};

int main(){
    LoopController c;
    ResourceLoader loader(&c);

    for(int i = 0; i< 10; ++i)
        loader.LoadResource<Dummy>(std::string("Dummy") + std::to_string(i), i);

    loader.Start();

    loader.WaitUntilDone(110);

    c.Stop();


    loader.Join();

    for(int i = 0; i< 10; ++i){
        auto dummy = loader.GetResource<Dummy>(std::string("Dummy") + std::to_string(i));
        if(dummy == nullptr){
            return 1;
        }
        if(dummy->value != i) return 1;
    }

    auto rem = loader.ReleaseResource<Dummy>("Dummy0");

    if(rem.get() == nullptr)
        return 1;
    if(rem->value != 0)
        return 1;
    if(loader.size() != 9)
        return 1;

    loader.Clear();
    if(loader.size() != 0) return 1;

    return 0;
}
