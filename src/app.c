#include "audio2mp3.h"
#include <string.h>
#include <stdio.h>

int __set_app(sapp* app, const char** source){
	memset(app, 0, sizeof(sapp));
	int i = app->size = 0;
	printf("in set_arg\n");
	if(*source != NULL)
	  for(i = 0; source[i] != NULL; i++){
	    strcpy(app->arg[i].opt, source[i]);
	    printf("%s\n", source[i]);
	    app->parg[i] = (char*) app->arg[i].opt;
	  }
	app->parg[i] = (char*) NULL;
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
