#ifndef S_AU2MP3
#define S_AU2MP3

#define CPU_MAX sysconf(_SC_NPROCESSORS_ONLN) 

struct s_au2mp3{
    char* value[BUFF];
    char* newformat;
    char* app;
    int cpu_max;
} au2mp3;

/*   Call after using au2mo3.   */
extern void init_au2mp3(char **argv);

/*   Getting structure s_au2mp3.   */
extern int get_cpu(void);
extern char* get_format(void);
extern char** get_list(void);
extern char* get_app(void);
extern char* get_name(void);

/*   Setting structure s_au2mp3.   */
extern void set_cpu(int cpu_max);
extern void set_format(char* newfromat);
extern void set_app(char* app);
extern void set_name(char*);
extern void set_list(char** const argv);

#endif
