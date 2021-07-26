#include "audio2mp3.h"


static void set_list(char** const argv);

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

static void 
set_list(char** const argv){
    /*   Key:
     *   -j max call programm 
     *   -f new format file name
     *   -p call programm name
     *   -v enable debug priunt    */

    char** name = au2mp3.value; 
    char** _argv = argv;

    while(*++_argv){
        if(**_argv == '-'){
            ++*_argv;

	    /*   Set max cpu   */
            if(**_argv == 'j'){ 
                print_debug("cpu_max", "on");

	        (atoi(++*_argv)) ? set_cpu(atoi(*_argv)):
	                           set_cpu(atoi(*++_argv));

		(*_argv)?_argv:--_argv;
	    }

	    /*   Set program name   */
            else if(**_argv == 'p'){
                print_debug("app", "on");

                (strlen(*_argv) > 1) ? set_app(++*_argv):
		                       set_app(*++_argv);

		(*_argv)?_argv:--_argv;
            }

	    /*   Set new format   */
            else if(**_argv == 'f'){
                print_debug("format", "on");

                (strlen(*_argv) > 1) ? set_format(++*_argv):
		                       set_format(*++_argv);

		(*_argv)?_argv:--_argv;
            }

	    /*   Enable debug print   */
            else if(**_argv == 'v'){
                printf("Debug: on");
                debug = true;

		(*_argv)?_argv:--_argv;
            }

        } else {// Value 
            *name = *_argv;
            name++;
        }
     } // End while.
}

bool is_format(char* const restrict name, char* const restrict newformat){
    if(!strcmp(&name[strlen(name)-strlen(newformat)], newformat))
    {
        print_debug("name is_format()", name);
        return true;
    }
    print_debug("name not is_format()", name);
    return false;
}

void print_debug(char* const restrict where, char* const restrict msg){
    /*  FIXME!!! Include stdarg.h using "..." and other value   */
    if(debug)
        printf("%s: %s\n", where, msg);
}
