/* audio2mp3.c -audio2mp3 application.   */
/* Author: S. A. Kravchuk 2021.           */
/* License: GPLv3                         */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include "audio2mp3.h"
#include "s_audio2mp3.h"

#define APP "ffmpeg"
#define FORMAT ".mp3"

int 
main(int argc, char **argv){

    set_name("audio2mp3");
    if(argc < 2)
        usage();

    int status;
    int jobs = 0;
    char new_name[BUFF];
    pid_t pid;

    set_app(APP);
    set_format(FORMAT);

    init_au2mp3(argv);

    char* newformat = get_format();
    int cpu_max = get_cpu();
    char** value = get_list();
    char* app = get_app();

    while(*value) /*   value != NULL   */
    {
        if (jobs < cpu_max)
        {
            if (is_format(*value, newformat))
            {
                print_debug("skip format: ", *value); 
                value++;  /*   No need to precode, next file.   */
                continue;
            }

	        errno = 0;

            if((pid = fork()) < 0)
                perror("Error fork (create new process)");

            if(!pid) /*   Children.   */
            {
		memset(new_name, 0, BUFF);
                strcat(new_name, *value);
                strcat(new_name, newformat);

                char* app_arg[] = {
                    "-hide_banner",
                    "-loglevel", 
                    "8",
                    "-i",
                    *value,
                    "-b:a", 
                    "192k", 
                    new_name,
                    (char*) NULL
                };

                execvp(app, app_arg);
                perror("error call ffmpeg (transcoding)"); 
            }

            jobs++;  /*   Parent.      */
            value++; /*   Next file.   */
        }
        else if(wait(&status)) /*   jobs > cpu_max   */
        /*   If the are no free CPU we are waiting for the first free.   */
        {
            jobs--;
        }
        
    }

    /*    Wait close jobs   */
    while((jobs--) >= 0)
        wait(&status);

    exit(EXIT_SUCCESS);
}
