#pragma once
#if defined(__gnu_linux__)
# define OS_GLX
#endif

#if defined(_WIN32)	|| defined(_WIN64) 	|| \
  defined(__WIN32__)	|| defined(__TOS_WIN__)	|| \
  defined(__WINDOWS__)
# define OS_WIN
#endif
 
#if defined(OS_GLX)
# define CPU_MAX sysconf(_SC_NPROCESSORS_ONLN) 
#elif defined(OS_WIN)
# define CPU_MAX 4
#endif

#include <unistd.h>
#include <stdbool.h>
#include "app.h"

#define BUFF 255U

extern bool 
is_format(const char* name, const char* newformat);
extern void 
print_debug(const char* where, const char* msg);
extern void
usage(void);

/*  structure edit  */
struct s_au2mp3{
    char* value[BUFF];
    char* newformat;
    char* app;
    int cpu_max;
} au2mp3;

/*   Call after using au2mp3.   */
extern void init_au2mp3(int const argc, char **argv);

/*   Getting structure s_au2mp3.   */
extern const int get_cpu(void);
extern const char* get_format(void);
extern char** get_list(void);
extern const char* get_app(void);
extern const char* get_name(void);
extern const char** get_arg(void);

/*   Setting structure s_au2mp3.   */
extern void set_cpu(int cpu_max);
extern void set_format(char* const newfromat);
extern void set_app(char* const app);
extern void set_name(const char* new_name);
extern void set_list(sapp* app, int const argc, char** const argv);
extern bool redirect_oerror(const char* filename, int handle);
extern const char** set_arg(const char* add_arg);
