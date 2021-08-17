#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio2mp3.h"
#include "s_audio2mp3.h"

extern void debugs(void);

void 
set_list(char** const argv){
    /*   Key:
     *   -j max call programm 
     *   -f new format file name
     *   -p call programm name
     *   -v enable debug priunt    */

    char** name = au2mp3.value; 
    char** _argv = argv;

    while(*++_argv){
        if(**_argv == '-'){

            ++*_argv;
	    switch(**_argv){
		case 'j': 
                    print_debug("cpu_max", "on");

		    if (atoi(++*_argv)) 
			set_cpu(atoi(*_argv));
		    else if (*++_argv)
		        set_cpu(atoi(*_argv));
		    else{
			set_cpu(CPU_MAX);
		        _argv--;
		    }
		    break;

                case 'p':
		    print_debug("app", "on");

		    (strlen(*_argv) > 1) ? set_app(++*_argv):
					   set_app(*++_argv);
		    if (!*_argv) --_argv;
		    break;

		case 'f':
		    print_debug("format", "on");

		    (strlen(*_argv) > 1) ? set_format(++*_argv):
					   set_format(*++_argv);

		    if (!*_argv) --_argv;
		    break;

		case 'v':
		    printf("Debug: on");
            debugs();
		    break;

		case 'h':
		    usage();
            }

        } else {/*   Value   */ 
            *name = *_argv;
            name++;
        }
     } /*   End while.   */
}
