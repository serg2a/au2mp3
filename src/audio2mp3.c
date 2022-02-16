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

#include "audio2mp3.h"

#define APP "ffmpeg"
#define FORMAT ".mp3" 
#define DEFOPT "-hide_banner -loglevel error -n -i"
#define LEN 255

typedef struct {char str[BUFF]; } sstring;
sstrintg app_arg[LEN];

char** app_opt(const char* opt, char** app_arg)
{
  char** _app_arg = app_arg;
  char value[LEN]; 
  char* pvalue = value;

  while(*opt++)
    if(' ' == *opt){
      *pvalue = '\0';
      pvalue = value;
      strcpy(*_app_arg++, pvalue);
      bzero(pvalue, LEN);
      continue;
    } else
        *pvalue++ = *opt;
  
  *_app_arg = NULL;
  _app_arg = app_arg;
  return _app_arg;
};

void print_value(char* opt, char** aarg){
 char** _app_arg = aarg; 
 app_opt(opt, _app_arg); 
 while(**_app_arg++)
   printf("app_arg: %s\n", *_app_arg);
}

int 
main(int argc, char **argv)
{
    print_value(DEFOPT, aarg); 

    set_name("audio2mp3");
    if(argc < 2)
        usage();

    int status;
    int jobs = 0;
    char new_name[BUFF]; 
    pid_t pid;

    set_app(APP);
    set_format(FORMAT);

    init_au2mp3(argc, argv);

    const char* format		= get_format();
    const int	cpu_max		= get_cpu();
    char** 	value		= get_list();
    const char* app		= get_app();


    while(*value) /*   if value != NULL   */
    {
        if (jobs < cpu_max)
        {
            if (is_format(*value, format))
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
                strcat(new_name, format);
		
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
            print_debug("setlist",*value);
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
    while(jobs--)
        wait(&status);

    exit(EXIT_SUCCESS);
}
