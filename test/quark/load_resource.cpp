/*
* Copyright (C) 2017 Filippo Crocchini.
*/

#include "./quark.h"

class Dummy : public Resource {
 public:
    int value;
    explicit Dummy(int value): value(value) {}

    bool Load() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return true;
    }

    void onLoad() override {}
    void onFail() override {}
};

int main() {
    Quark::Start();
    Quark::LoadResource<Dummy>("One", 1);
    Quark::WaitForResources();
    Dummy* one = Quark::GetResource<Dummy>("One");
    if (one == nullptr || one->value != 1) {
        Quark::Stop();
        return 1;
    }
    Quark::Stop();
    return 0;
}
