#include "looping_thread.h"


void LoopingThread::Start(){
    worker = std::thread{
    	[this]() {
            while(this->controller->isRunning())
    		      this->Loop();
    }};
}

void LoopingThread::Join(){
    worker.join();
}
