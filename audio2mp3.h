#ifndef AU2MP3
#define AU2MP3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

#define BUFF 1024 
#define FORMAT ".mp3"

bool debug;

struct s_au2mp3
{
    char* value[BUFF];
    char* newformat;
    char* app;
    int cpu_max; 
} au2mp3;

bool 
is_format(const char* name, const char* newformat);

void 
print_debug(const char* restrict where, const char* restrict  msg);

void init_au2mp3(char **argv);
// Getting structure s_au2mp3.
int get_cpu_max(void);
char* get_format(void);
char** get_list(void);

// Setting structure s_au2mp3.
void set_cpu_max(int cpu_max);
void set_format(char* newfromat);

#endif
