#ifndef AU2MP3
#define AU2MP3
#define CPU_MAX sysconf(_SC_NPROCESSORS_ONLN) 

#include <unistd.h>
#include <stdbool.h>

enum { BUFF = 1024 };
extern bool 
is_format(char* const  name, char* const newformat);
extern void 
print_debug(char* const where, char* const msg);
extern void
usage(void);


/*  structure edit  */
struct s_au2mp3{
    char* value[BUFF];
    char* newformat;
    char* app;
    int cpu_max;
} au2mp3;

/*   Call after using au2mo3.   */
extern void init_au2mp3(char **argv);

/*   Getting structure s_au2mp3.   */
extern const int get_cpu(void);
extern const char* get_format(void);
extern char** get_list(void);
extern const char* get_app(void);
extern const char* get_name(void);

/*   Setting structure s_au2mp3.   */
extern void set_cpu(int cpu_max);
extern void set_format(char* newfromat);
extern void set_app(char* app);
extern void set_name(char*);
extern void set_list(char** const argv);

#endif
