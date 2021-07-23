/* audio2mp3.c - audio2mp3 application.   */
/* Author: S. A. Kravchuk 2021.           */
/* License: GPLv3                         */

#include "audio2mp3.h"

bool debug = false;


int 
main(int argc, char **argv){

    int status;
    int jobs = 0;
    char new_name[BUFF];
    pid_t pid;

    init_au2mp3();
    char* newformat = get_format();
    int cpu_max = get_cpu_max();

    if(argc < 2)
    {
        printf("Using: %s filename\n", *argv);
        exit(1);
    }

    argv++; // Skip name program.

    while(*argv)
    {
        if (jobs < cpu_max)
        {
            if (is_format(*argv, newformat))
            {
                print_debug("check mp3", "is mp3");
                argv++;  // Next file name.
                continue;
            }

            if((pid = fork()) < 0)
            {
                fprintf(stderr, "error create fork!");
                exit(1);
            }

            if(!pid) // Children.
            {
                strcat(new_name, *argv);
                strcat(new_name, newformat);

                execlp("ffmpeg", "ffmpeg", "-hide_banner", 
                "-loglevel", "-8", "-i", *argv, new_name, (char*)NULL);
                
                exit(0);
            }

            jobs++; // Parent.
            argv++; // Next file name.
        }
        else if(wait(&status))
        /* If the are no free CPU we are waiting for the first free.   */
        {
            jobs--;
        }
        
    }
    exit(0);
}

bool is_format(const char* restrict name, const char* restrict newformat){
    if(!strcmp(&name[strlen(name)-strlen(newformat)], newformat))
    {
        print_debug("name is_format()", name);
        return true;
    }
    print_debug("name not is_format()", name);
    return false;
}

void print_debug(const char* restrict where, const char* restrict msg){
    /*  FIXME!!! Include stdarg.h using "..." and other value   */
    if(debug)
        printf("%s: %s\n", where, msg);
}
