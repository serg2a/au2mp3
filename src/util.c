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
#include <sys/stat.h>
#include <fcntl.h>
#include "audio2mp3.h"

#define _BUFF 255

static char prog_name[_BUFF];
static char prog_arg[_BUFF];
static bool debug = false;

void init_au2mp3(int const argc, char** const argv){
    set_cpu(CPU_MAX); 
    set_list(argc, argv);
}

void usage(void){
    printf("Using: %s filename\n"
           "----\nKey:\n"
    	   "\t-j cpu max\n"
           "\t-f format\n"
           "\t-p application\n"
    	   "\t-a add argument call app\n"
           "\t-v debug print\n", get_name());
    _Exit(EXIT_FAILURE);
}

const int get_cpu(void){return au2mp3.cpu_max;}
const char* get_format(void){return au2mp3.newformat;}
const char* get_app(void){return au2mp3.app;}
char** get_list(void){return au2mp3.value;}

void set_cpu(int cpu_max){au2mp3.cpu_max = (cpu_max)?cpu_max:CPU_MAX;}
void set_format(char* format){au2mp3.newformat = format;}
void set_app(char* app){au2mp3.app = app;}


void set_name(const char *_name){
    strcpy(prog_name, _name);
}

const char* get_arg(void){
    return prog_arg;
}

const char* get_name(void){
    return prog_name;
}

bool is_format(const char* name, const char* newformat){
    if(!strcmp(&name[strlen(name)-strlen(newformat)], newformat))
    {
        print_debug("name is_format()", name);
        return true;
    }
    print_debug("name not is_format()", name);
    return false;
}

void debugs(void){ debug = true; }

void print_debug(const char* where, const char* msg){
    if(debug)
        printf("%s: %s\n", where, msg);
}

bool redirect_oerror(const char* filename, int handle){
    static const mode_t filemode = S_IRUSR | S_IWUSR | S_IRGRP
                                 | S_IROTH;
    static const int fileflags   = O_APPEND | O_CREAT | O_WRONLY;

    int fd = open(filename, fileflags, filemode);
    if( fd == -1){
        perror("open");
	return false;
    }
    if(dup2(fd, handle) < 0){
      close(fd);
      perror("dup2");
      return false;
    }
    close(fd);
    return true;
}

char* set_arg(const char* arg){
	int len = strlen(arg);
	if(_BUFF < len){
		perror("Is it long app arguments");
		return (char*) NULL;
	}
	memset(prog_arg, 0, sizeof(char)*len);
	strcpy(prog_arg, arg);
	char* parg[len];
	parg[0] = prog_arg;
	int k = 1;
	for(int i = 0; i < len; i++)
		if(prog_arg[i] == ' '){
			prog_arg[i] = '\0';
			parg[k++] = &prog_arg[++i];
		}
	parg[k] = NULL;
	return *parg;
}
