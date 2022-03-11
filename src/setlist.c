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
#include <unistd.h>

#include "audio2mp3.h"


extern void debugs(void);



void 
set_list(sapp* app, int const argc, char** const argv)
{
    /*   Key:
     *   -j max call programm 
     *   -f new format file name
     *   -p call programm name
     *   -v enable debug priunt    
     *	 -a arguments for call progarm -p <app>
     */

    int opt;

    while((opt = getopt(argc, argv, "j:f:p:a:v")) != -1)
      switch (opt){
        case 'j':
	  print_debug("cpu_max", "on");
          set_cpu(atoi(optarg));
          break;

        case 'p':
          print_debug("app", "on");
          set_app(optarg);
          break;

        case 'f':
          print_debug("format", "on");
          set_format(optarg);
          break;

        case 'v':
          printf("Debug: on");
          debugs();
          break;

	case 'a':
	  print_debug("add arguments", "on");
	  __set_app(app, set_arg(optarg));
	  break;

        default:
          usage();
      }/*  end switch */

    if(optind >= argc){
      fprintf(stderr, "Expected argument after options\n");
      exit(EXIT_FAILURE);
    };
    
    for(int i = optind; i <argc; i++) {
      au2mp3.value[i-optind] = argv[i];
    }
    au2mp3.value[argc] = NULL;
}
