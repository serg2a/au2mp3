#pragma once
#ifndef BUFF
#  define BUFF 255U
#endif

typedef struct {char opt[BUFF];} sapp_arg;
typedef struct {
	sapp_arg arg[BUFF]; 
	char* parg[BUFF];
	const char* name;
	int size;
} sapp;

extern int apps(sapp* app, const char* value, const char* const format);
extern int __set_app(sapp* app, const char** source);
extern int __add_app(sapp* app, const char* source);
