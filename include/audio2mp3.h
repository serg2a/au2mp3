#ifndef AU2MP3
#define AU2MP3

#include <stdbool.h>
#include <unistd.h>

enum { BUFF = 1024 };

extern bool 
is_format(char* const  name, char* const newformat);

extern void 
print_debug(char* const where, char* const msg);

extern void
usage(void);

#endif
