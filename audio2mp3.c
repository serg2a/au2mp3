/* audio2mp3.c -audio2mp3 application.   */
/* Author: S. A. Kravchuk 2021.           */
/* License: GPLv3                         */

#include "audio2mp3.h"

int 
main(int argc, char **argv){

    if(argc < 2)
    {
        printf("Using: %s filename\n", *argv);
	printf("----\nKey:\n \
   -j cpu max\n \
   -f format\n \
   -p application\n \
   -v debug print\n"
	);

        exit(1);
    }

    int status;
    int jobs = 0;
    char new_name[BUFF];
    pid_t pid;

    init_au2mp3(argv);
    char* newformat = get_format();
    int cpu_max = get_cpu();
    char** value = get_list();
    char* app = get_app();

    while(*value)
    {
        if (jobs < cpu_max)
        {
            if (is_format(*value, newformat))
            {
                value++;  // Next file name.
                continue;
            }

            if((pid = fork()) < 0)
            {
                fprintf(stderr, "error create fork!");
                exit(1);
            }

            if(!pid) // Children.
            {
                strcat(new_name, *value);
                strcat(new_name, newformat);

		char* app_arg[] = {
		    "-hide_banner",
		    "-loglevel",
		    "-8",
		    "-i",
		    *value,
		    new_name,
		    (char*) NULL
		};

                execvp(app, app_arg);
                
                exit(0);
            }

            jobs++; // Parent.
            value++; // Next file name.
        }
        else if(wait(&status))
        /* If the are no free CPU we are waiting for the first free.   */
        {
            jobs--;
        }
        
    }
    exit(0);
}
