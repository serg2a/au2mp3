#include "audio2mp3.h"

static void set_list(char** argv);

void init_au2mp3(char** argv){
    set_cpu_max(sysconf(_SC_NPROCESSORS_ONLN)); 
    set_format(FORMAT);
    set_list(argv);
}

int get_cpu_max(void){return au2mp3.cpu_max;}
char* get_format(void){return au2mp3.newformat;}
char* get_app(void){return au2mp3.app;}
char** get_list(void){return au2mp3.value;}

void set_cpu_max(int cpu_max){au2mp3.cpu_max = cpu_max;}
void set_format(char* format){au2mp3.newformat = format;}
void set_app(char* app){au2mp3.app = app;}


static void set_list(char** tmp_argv){
    char** name = au2mp3.value; 
    char** argv = tmp_argv;
    while(*++argv){
        if(**argv == '-'){
            ++*argv;
            if(**argv == 'j'){  // Count core per unit.
                set_cpu_max(atoi(++*argv));
                print_debug("cpu_max", "on");
            }
            else if(**argv == 'p'){ // Program name.
                set_app(++*argv);
                print_debug("app", "on");
            }
            else if(**argv == 'f'){ // Format string.
                set_format(++*argv);
                print_debug("format", "on");
            }
            else if(**argv == 'v'){ // Debug print.
                printf("Debug: on");
                debug = true;
            }
        } else {// Value 
            *name = *argv;
            name++;
        }
     } // End while.
}
