#include "audio2mp3.h"
#include <string.h>
#include <stdio.h>

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

int __add_app(sapp* app, char* source){
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
