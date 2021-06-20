/* main.c - audio2mp3 application.   */
/* Author: Sergei Kravchuk 2021.     */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define CPU_MAX 8        // Cpu jobs.
#define NEWFORMAT ".mp3"  // Add tail original name.
#define MAX_SIMBOL 4096

int 
main(int argc, char *argv[]){
    int status;
    int run = 0;
    char tmp_str[MAX_SIMBOL];
    pid_t pid;

    while(*argv)
    {
        if (run < CPU_MAX)
        {
            if((pid = fork()) < 0)
            {
                printf("error create fork!");
                exit(1);
            }

            argv++;
            if(!pid)
            {
                strcat(tmp_str, *argv);
                strcat(tmp_str, NEWFORMAT);

                execlp("ffmpeg", "ffmpeg", "-hide_banner", 
                "-loglevel", "-8", "-i", *argv, tmp_str, (char*)NULL);
                
                exit(0);
            }

            run++; // Parent
        }
        else if(wait(&status))
        /* If the are no free CPU we are waiting for the first free.   */
        {
            run--;
        }
        
    }
    exit(0);
}
