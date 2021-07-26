#include "audio2mp3.h"
#include "test.h"

bool test_cpu(int cpu_max){
    cpu_max = (cpu_max > 0)?cpu_max:CPU_MAX;
    set_cpu(cpu_max);
    bool ok = (get_cpu() == cpu_max ? true : false);
    return ok;
}

int main(void){
    bool cpu_ok = false;
    char* check;
    for(int i = 0; i < 20; i++){
        cpu_ok = test_cpu(i);
    }
    
    printf("test cpu: %s!\n", check = (cpu_ok ? "OK" : "FALL"));
   
    return 0;
}
