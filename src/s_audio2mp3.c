#include "audio2mp3.h"

extern void set_list(char** const argv);

struct s_au2mp3 au2mp3;

void init_au2mp3(char** const argv){
    set_cpu(CPU_MAX); 
    set_app(APP);
    set_format(FORMAT);
    set_list(argv);
}

int get_cpu(void){return au2mp3.cpu_max;}
char* get_format(void){return au2mp3.newformat;}
char* get_app(void){return au2mp3.app;}
char** get_list(void){return au2mp3.value;}

void set_cpu(int cpu_max){au2mp3.cpu_max = (cpu_max)?cpu_max:CPU_MAX;}
void set_format(char* format){au2mp3.newformat = format;}
void set_app(char* app){au2mp3.app = app;}
