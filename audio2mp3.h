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
#define APP "ffmpeg"
#define CPU_MAX sysconf(_SC_NPROCESSORS_ONLN) 

bool debug;

struct s_au2mp3
{
    char* value[BUFF];
    char* newformat;
    char* app;
    int cpu_max; 
} au2mp3;

bool 
is_format(char* const  name, char* const newformat);

void 
print_debug(char* const where, char* const msg);

void
usage(char* name);

void init_au2mp3(char **argv);
// Getting structure s_au2mp3.
int get_cpu(void);
char* get_format(void);
char** get_list(void);
char* get_app(void);

// Setting structure s_au2mp3.
void set_cpu(int cpu_max);
void set_format(char* newfromat);
void set_app(char* app);

#endif
