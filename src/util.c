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
