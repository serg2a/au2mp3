#include "audio2mp3.h"

void init_au2mp3(void){
    au2mp3.cpu_max = sysconf(_SC_NPROCESSORS_ONLN); 
    au2mp3.newformat = FORMAT;
}

int get_cpu_max(void){return au2mp3.cpu_max;}
char* get_format(void){return au2mp3.newformat;}
char** get_list_file(void){return au2mp3.list_file;}

void set_cpu_max(int cpu_max){au2mp3.cpu_max = cpu_max;}
void set_format(char* format){strcpy(au2mp3.newformat, format);}
void set_list_file(char* name){strcpy((*au2mp3.list_file)++, name);}
