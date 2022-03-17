#include <string.h>
#include <stdio.h>
#include "app.h"
#include "audio2mp3.h"

int apps(sapp* app, const char* value, const char* const format){

  extern char* const APP;
  char sarg[BUFF];
  if(!strcmp(get_app(), APP)){
  extern char* const ARG;
  extern char* const ARG2;
  char new_value[100] = {0}; 
  sprintf(new_value, "%s.%s", value, format);
    sprintf(sarg,"%s %s %s %s", ARG, value, ARG2, new_value);
    __set_app(app, set_arg(sarg));  
  } else {
    sprintf(sarg,"%s %s", app->larg, value);
    __set_app(app, set_arg(sarg));  
  }
  //__add_app(app, value);
  //__add_app(app, new_value);

  print_debug("call app", value); 
  if(execvp(get_app(), app->parg) == -1)
        perror("execvp");
  return 127;
}

int __set_app(sapp* app, const char** source){
/*
*  Create array arguments for execvp().
*  Return size array.
*/
	memset(app, 0, sizeof(sapp));
	if(*source != NULL){
	  for(int* i = &app->size; source[*i] != NULL; ++*i){
	    if(strlen(source[*i]) < BUFF){
	      strcpy(app->arg[*i].opt, source[*i]);
	      app->parg[*i] = (char*) app->arg[*i].opt;
	    } else fprintf(stderr, "it's long arguments: %s\n", source[*i]);
	  }
	  app->parg[app->size] = (char*) NULL;
	}
	return app->size;
}

int __add_app(sapp* app, const char* source){
/*
*  Add string array arguments for execvp().
*  Return 0 is ok.
*/
	if(strlen(source) < BUFF){
	  int i = app->size;
	  strcpy(app->arg[i].opt, source);
	  app->parg[i] = (char*) app->arg[i].opt;
	  char** parg = (char**) app->arg;
	  parg[++i] = (char*) NULL;
	  app->parg[i] = (char*) app->arg[i].opt;
	} else return -1;
	app->size++;
	return 0;
}
