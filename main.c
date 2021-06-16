#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define FORK_MAX 12


int main(int argc, char *argv[]){
	int status;
	int run = 0;
    char tmp_str[4096];

	while(argc-1 && *argv)
	{
		argv++;
		if (run <= FORK_MAX-1)
			if(!fork())
			{
                printf("%s\n", *argv);
                strcat(tmp_str, *argv);
                strcat(tmp_str, ".mp3");
                printf("run convert: %s\n", *argv);
				execlp("ffmpeg", "ffmpeg", "-i", *argv, tmp_str, (char*)NULL);
                printf("complete convert: %s\n", tmp_str);
				exit(0);
			}
		    else
			{
				run++;
				argc--;
			}
		else
		{
			wait(&status);
			run--;
			printf("Exit children\n");
		}
	}
	exit(0);
}
