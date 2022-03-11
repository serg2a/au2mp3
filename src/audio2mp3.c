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

/* Default value the application runing */
static unsigned char MIN_ARG	= 2U;
static char* const NAME		= "audio2mp3";
static char* const APP		= "ffmpeg";
static char* const FORMAT	= "mp3";
static char* const ARG		= "-hide_banner -loglevel error -n -i";

int 
main(int argc, char **argv)
{ 
    set_name(NAME); /* This application name */
    if(argc < MIN_ARG)
        usage();

    init_au2mp3(argc, argv);

    set_app(APP);	/* application name for call execvp(). 	*/
    set_format(FORMAT); /* new format encoding.			*/

    sapp app; /* app.c */
    set_list(&app, argc, argv);

    if(!strcmp(get_app(), APP))
      __set_app(&app, set_arg(ARG));  

    const char* format		= get_format();
    const int	cpu_max		= get_cpu();
    char** 	value		= get_list();

    int jobs = 0;
    char new_name[BUFF]; 
    pid_t pid[BUFF];
    memset(pid, 0, sizeof(pid_t)*BUFF); 
    u_int16_t i = 1;

    while(*value) {
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

		  memset(new_name, 0, BUFF);
                  sprintf(new_name, "%s.%s", *value, format);
	
		  __add_app(&app, *value);
		  __add_app(&app, new_name);

                  print_debug("call app", *value); 
                  if(execvp(get_app(), app.parg) == -1)
			  perror("execvp");
		  break;
		}

	      default: {
        	print_debug("setlist", *value);
            	jobs++;  /*   Parent.      */
            	value++; /*   Next file.   */
		i++;	 /*   counter pid  */
	      }
	  }
        } else if(wait(NULL)) /*   jobs > cpu_max   */
        /*   If the are no free CPU we are waiting for the first free.   */
        {
  	    i--;
            jobs--;
        }
        
    }

    /*    Wait close jobs   */
    for(;i > 0; i--)
      wait(NULL);

    _exit(EXIT_SUCCESS); 
}
