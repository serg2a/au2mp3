#include "audio2mp3.h"
#include <string.h>

int __init_app(sapp* app){
	app->size = 0;
	app->name = get_app();
	return 0;
}

int __set_app(sapp* app, const char* source){
	int i = 0;
	if(source != NULL)
	  for(; &source[i] != NULL; i++){
	    strcpy(app->arg[i].opt, &source[i]);
	    app->parg[i] = (char*) app->arg[i].opt;
	  }
	app->size = i;
	return app->size;
}

int __add_app(sapp* app, char* source){
	strcpy(app->arg[app->size].opt, source);
	app->parg[app->size] = (char*) app->arg[app->size].opt;
	char** parg = (char**) app->arg;
	parg[++app->size] = (char*) NULL;
	app->parg[app->size] = (char*) app->arg[app->size].opt;
	return 0;
}
