#include "looping_thread.h"

int main(){
    LoopController l;
    if(!l.isRunning()) return 1;
    l.Stop();
    if(l.isRunning()) return 1;
    return 0;
}
