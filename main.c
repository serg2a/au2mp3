#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define FORK_MAX 12
#define NEWFORMAT ".mp3"



int main(int argc, char *argv[]){
    int status;
    int run = 0;
    char tmp_str[4096];
    pid_t pid;

    while(argc-1 && *argv)
    {
        argv++;
        if (run <= FORK_MAX-1)
        {
            if((pid = fork()) < 0)
                exit(1);
            if(!pid)
            {
                strcat(tmp_str, *argv);
                strcat(tmp_str, NEWFORMAT);
                printf("run convert: %s\n", *argv);

                execlp("ffmpeg", "ffmpeg", "-hide_banner", "-loglevel", "-8", "-i", *argv, tmp_str, (char*)NULL);

                printf("complete convert: %s\n", tmp_str);
                exit(0);
            }
            else
            {
                run++;
                argc--;
			}
        }
        else if(wait(&status))
            run--;
    }
    exit(0);
}
