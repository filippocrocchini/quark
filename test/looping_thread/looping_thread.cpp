#include "looping_thread.h"
#include <chrono>
#include <ctime>
#include <iostream>

class LoopingDummy : public LoopingThread {
public:
    LoopingDummy(LoopController* controller) : LoopingThread(controller) {
    }

protected:
    virtual void Loop() override;
};

void LoopingDummy::Loop() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    LoopController c;
    LoopingDummy l(&c);
    auto t = std::chrono::steady_clock::now().time_since_epoch(), now = t;

    l.Start();

    now = std::chrono::steady_clock::now().time_since_epoch();
    if(std::chrono::duration_cast<std::chrono::microseconds>(now-t).count() >= 1000000) {
        l.Join();
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //I stop the thread, i.e because i clicked the Exit button.
    c.Stop();
    now = std::chrono::steady_clock::now().time_since_epoch();

    //Then the thread has to be joined otherwise std::terminate() is called by std::thread::~thread()
    l.Join();

    long delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()-now).count();

    //The time passed between Stop and Join must be less than or equal to the time a Loop takes (Fixed at 1 second).
    if(delta >= 1000000) {
        return 1;
    }


    now = std::chrono::steady_clock::now().time_since_epoch();

    if(std::chrono::duration_cast<std::chrono::microseconds>(now-t).count() < 1000000) {
        return 1;
    }
    return 0;
}
