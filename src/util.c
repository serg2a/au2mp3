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
#include <string.h>
#include <stdbool.h>
#include "audio2mp3.h"

#define _BUFF 255

void init_au2mp3(char** const argv){
    set_cpu(CPU_MAX); 
    set_list(argv);
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

int get_cpu(void){return au2mp3.cpu_max;}
char* get_format(void){return au2mp3.newformat;}
char* get_app(void){return au2mp3.app;}
char** get_list(void){return au2mp3.value;}

void set_cpu(int cpu_max){au2mp3.cpu_max = (cpu_max)?cpu_max:CPU_MAX;}
void set_format(char* format){au2mp3.newformat = format;}
void set_app(char* app){au2mp3.app = app;}


void print_debug(char* const restrict where, char* const restrict msg);

static char prog_name[_BUFF];
static bool debug = false;

void set_name(const char *_name){
    strcpy(prog_name, _name);
}

char* get_name(void){
    return prog_name;
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
