

#ifndef _LOH_H_
#define _LOG_H_ 

#include <stdio.h>
#include <stdarg.h>
#define LOG_LERVER 1



//void log_print(int type,char *fun,int line,char *tag,char *msg);

void print_info(char *tag,char *msg, ...);

//void print_info(char *fun,int line,char *tag,char *msg);

//void print_warn(char *fun,int line,char *tag,char *msg);

void print_warn(char *tag,char *msg, ...);

//void print_error(char *fun,int line,char *tag,char *msg);

void print_error(char *tag,char *msg, ...);




#endif
