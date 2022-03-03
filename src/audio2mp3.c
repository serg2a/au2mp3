/* This file is part of audio2mp3.

    audio2mp3 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    audio2mp3 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with audio2mp3.  If not, see <https://www.gnu.org/licenses/>.

    Author  : S. A. Kravchuk 2021.
    email   : serg2ak@ya.ru
    License : GPLv3                         
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
#include <sys/prctl.h>

#include "audio2mp3.h"

#define APP "ffmpeg"
#define FORMAT "mp3" 

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
    const char* app		= get_app();


    if(prctl(PR_SET_CHILD_SUBREAPER, 1lu))
	perror("prctl");

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
		}

                case 0: {/*   Children.   */
                  if(!redirect_oerror("out.log", STDOUT_FILENO) ||
                     !redirect_oerror("err.log", STDERR_FILENO))
                    fprintf(stderr,"redirect out children\n");

		  memset(new_name, 0, BUFF);
                  sprintf(new_name, "%s.%s", *value, format);
		
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

                  execvp(app, app_arg);
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
