#include "resource_loader.h"

#include <chrono>
#include <thread>
#include <iostream>

class Dummy : public Resource {
public:
    int value;
    Dummy(int value):value(value) {
    }

    virtual bool Load() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return true;
    }

    virtual void onLoad() override {}

    virtual void onFail() override {}
};

int main() {
    LoopController c;
    Registry<std::string, Resource> reg;
    ResourceLoader loader{&c};

    for(int i = 0; i< 10; ++i)
        loader.Load<Dummy>(&reg, std::string("Dummy") + std::to_string(i), i);

    loader.Start();

    loader.WaitUntilDone(110);

    c.Stop();

    loader.Join();

    for(int i = 0; i<10; ++i) {
        auto dummy = reg.Get<Dummy>(std::string("Dummy") + std::to_string(i));
        if(dummy == nullptr) {
            std::cout << "Dummy pointer is null\n";
            return 1;
        }
        if(dummy->value != i) {
            std::cout << "Dummy"<<i<<" value is "<< dummy->value <<", not "<<i<<"\n";
            return 1;
        }
    }

    std::unique_ptr<Dummy> rem = reg.Release<Dummy>("Dummy0");

    if(rem.get() == nullptr) {
        std::cout << "Dummy pointer is null\n";
        return 1;
    }
    if(rem->value != 0) {
        std::cout << "Dummy value not zero\n";
        return 1;
    }
    if(reg.size() != 9) {
        std::cout << "Dummy count is not 9 after loading 9\n";
        return 1;
    }

    reg.Clear();
    if(reg.size() != 0) {
        std::cout << "Register size greater than one after Clean\n";
        return 1;
    }
    return 0;
}
