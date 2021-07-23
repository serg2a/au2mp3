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

#define BUFF 255
#define FORMAT ".mp3"

struct s_au2mp3
{
    char* list_file[1024];  //FIXME!!! auto or argc!
    char* newformat;   // Add tail original name.
    int cpu_max;    // Using CPU.
} au2mp3;

bool 
is_format(const char* name, const char* newformat);

void 
print_debug(const char* restrict where, const char* restrict  msg);

// Getting structure s_au2mp3.
void init_au2mp3(void);
int get_cpu_max(void);
char* get_format(void);
char** get_list_file(void);

// Setting structure s_au2mp3.
void set_cpu_max(int cpu_max);
void set_format(char* newfromat);
void set_list_file(char* name);

// Test structure s_au2mp3.
bool test_cpu_max(void);
bool test_format(void);
bool test_list_file(void);
#endif
