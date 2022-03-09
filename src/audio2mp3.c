/* This file is part of audio2mp3.

    Author  : S. A. Kravchuk 2021.
    email   : serg2ak@ya.ru, spam.reg.box@ya.ru
    License : GAttribution 4.0 International (CC BY 4.0)
*/

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

#define APP "ffmpeg"
#define FORMAT "mp3" 


char* ffmpeg_arg[] = {
 "-hide_banner",
 "-loglevel", 
 "error",
 "-n",
 "-i",
 NULL
};

typedef struct {char opt[BUFF];} sapp_arg;
typedef struct {
	sapp_arg arg[BUFF]; 
	const char* name;
	int size;
} sapp;

sapp app;

int __set_arg(sapp* dest, char** source){
	int i = 0;
	if(*source != NULL)
	  for(; source[i] != NULL; i++)
	    strcpy(dest->arg[i].opt, source[i]);
	//dest->parg[++i].opt = (char*) NULL;
	dest->size = i;
	dest->name = get_app();
	return i;
}

int __add_arg(sapp* dest, char* source){
	strcpy(dest->arg[++(dest->size)].opt, source);
	sapp_arg* parg = dest->arg;
	return 0;
}


int 
main(int argc, char **argv)
{


    set_name("audio2mp3");
    if(argc < 2)
        usage();

    int jobs = 0;
    char new_name[BUFF]; 

    set_app(APP);
    set_format(FORMAT);

    init_au2mp3(argc, argv);

    const char* format		= get_format();
    const int	cpu_max		= get_cpu();
    char** 	value		= get_list();
    //const char* app		= get_app();

    __set_arg(&app, ffmpeg_arg);  
    __add_arg(&app, "new str");

    while(*value) /*   if value != NULL   */
    {
        if (jobs < cpu_max) {
            if (is_format(*value, format)){
                print_debug("skip format: ", *value); 
                value++;  /*   No need to precode, next file.   */
                continue;
            }

            switch(fork()){
                case -1: {
		  perror("Error fork (create new process)");
		  sleep(10);
		  continue;
		}

                case 0: {/*   Children.   */
                  if(!redirect_oerror("out.log", STDOUT_FILENO) ||
                     !redirect_oerror("err.log", STDERR_FILENO))
                    fprintf(stderr,"redirect out children\n");

		  memset(new_name, 0, BUFF);
                  sprintf(new_name, "%s.%s", *value, format);
	
		  __add_arg(&app, *value);
		  __add_arg(&app, new_name);

                  char* app_arg[] = {
                    "-hide_banner",
                    "-loglevel", 
                    "error",
		    "-n",
                    "-i",
                    *value,
                    new_name,
                    (char*) NULL
		  };

                  execvp(app.name, app_arg);
                  perror("error call ffmpeg (transcoding)"); 
		}

	      default: {
        	print_debug("setlist", *value);
            	jobs++;  /*   Parent.      */
            	value++; /*   Next file.   */
	      }
	  }
        } else if(wait(NULL)) /*   jobs > cpu_max   */
        /*   If the are no free CPU we are waiting for the first free.   */
        {
            jobs--;
        }
        
    }

    /*    Wait close jobs   */
    while(wait(NULL) != -1)
      if(errno == ECHILD)
    	_exit(EXIT_SUCCESS);

    _exit(EXIT_FAILURE); 
}
