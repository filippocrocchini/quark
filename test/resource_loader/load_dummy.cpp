#include "resource_loader.h" 

#include <chrono>
#include <thread>

class Dummy : public Resource {
public:
    Dummy(){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

int main(){
    LoopController c;
    ResourceLoader loader(&c);
    
    loader.Load<Dummy>("Dummy");
    
    loader.Start();
    
    c.Stop();
    
    loader.Join();
    loader.Clear();
    return 0;   
}
