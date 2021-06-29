/* audio2mp3.c - audio2mp3 application.   */
/* Author: S. A. Kravchuk 2021.           */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFF 255
#define CPU_MAX sysconf(_SC_STREAM_MAX)
#define FORMAT ".mp3"

bool debug = false;

bool 
is_format(const char* name, const char* newformat);

void 
print_debug(const char* restrict where, const char* restrict  msg);

int 
main(int argc, char **argv){

	char* newformat = FORMAT;     // Add tail original name.
	int8_t cpu_max = CPU_MAX;     // Cpu jobs;


    int status;
    int jobs = 0;
    char new_name[BUFF];
    pid_t pid;


	if(argc < 2)
	{
		printf("Using: %s filename\n", *argv);
		exit(1);
	}

	argv++;
	
    while(*argv)
    {

        if (jobs < cpu_max)
        {
		    if (is_format(*argv, newformat))
			{
				print_debug("check mp3", "is mp3");
				argv++;
				continue;
     		}

            if((pid = fork()) < 0)
            {
                fprintf(stderr, "error create fork!");
                exit(1);
            }

            if(!pid)
            {
				strcat(new_name, *argv);
				strcat(new_name, newformat);

                execlp("ffmpeg", "ffmpeg", "-hide_banner", 
                "-loglevel", "-8", "-i", *argv, new_name, (char*)NULL);
                
                exit(0);
            }

            jobs++; // Parent
			argv++;
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
	if(strcmp(&name[strlen(name)-strlen(newformat)], newformat) == 0)
	{
		print_debug("name is_format()", name);
	    return true;
	}
	print_debug("name !is_format()", name);
	return false;
}

void print_debug(const char* restrict where, const char* restrict msg){
	if(debug)
	    printf("%s: %s\n", where, msg);
}
