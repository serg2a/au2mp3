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

#ifndef _UTIL
#define _UTIL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define _BUFF 255

void print_debug(char* const restrict where, char* const restrict msg);

static char prog_name[_BUFF];
static bool debug = false;

void set_name(char *_name){
    strcpy(prog_name, _name);
}

char* get_name(void){
    return prog_name;
}

void usage(void){
    printf("Using: %s filename\n"
           "----\nKey:\n"
    	   "\t-j cpu max\n"
           "\t-f format\n"
           "\t-p application\n"
           "\t-v debug print\n", get_name());
    exit(EXIT_FAILURE);
}

bool is_format(char* const restrict name, char* const restrict newformat){
    if(!strcmp(&name[strlen(name)-strlen(newformat)], newformat))
    {
        print_debug("name is_format()", name);
        return true;
    }
    print_debug("name not is_format()", name);
    return false;
}

void debugs(void){ debug = true; };

void print_debug(char* const restrict where, char* const restrict msg){
    if(debug)
        printf("%s: %s\n", where, msg);
}
#endif
