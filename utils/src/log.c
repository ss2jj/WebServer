#include "log.h"



/**void log_print(int type,char *tag,char *msg, ...)    {
	va_list argp;
	va_start(argp,msg);
    if(type >  LOG_LERVER)   {
        return ;
    }
    
    if(tag!= NULL && msg != NULL)   {
		printf("[%s]",tag);
        vfprintf(stdout,msg,argp);	
    } else {
        printf("msg is null");
    }
    va_end(argp);

}

void log_print(int type,char *fun,int line,char *tag,char *msg) {
    if(type >  LOG_LERVER)   {
        return ;
    }

    if(tag!= NULL && msg != NULL)   {
        printf("[%s,%d %s] %s",fun,line,tag,msg);
    } else {
        printf("msg is null");
    }


}**/

void print_info(char *tag,char *msg, ...)   {
    va_list argp;
	va_start(argp,msg);
	int type = 0;
    if(type >  LOG_LERVER)   {
        return ;
    }
    
    if(tag!= NULL && msg != NULL)   {
		printf("[%s]",tag);
        vfprintf(stdout,msg,argp);	
		printf("\n");
    } else {
        printf("msg is null");
    }
    va_end(argp);

}

/*void print_info(char *fun,int line,char *tag,char *msg)   {
     log_print(0,fun,line,tag,msg);

}

void print_warn(char *fun,int line,char *tag,char *msg)    {
    log_print(2,fun,line,tag,msg);
}*/

void print_warn(char *tag,char *msg, ...)    {
     va_list argp;
	va_start(argp,msg);
	int type = 2;
    if(type >  LOG_LERVER)   {
        return ;
    }
    
    if(tag!= NULL && msg != NULL)   {
		printf("[%s]",tag);
        vfprintf(stdout,msg,argp);	
    } else {
        printf("msg is null");
    }
    va_end(argp);
}

/*void print_error(char *fun,int line,char *tag,char *msg)   {
    log_print(4,fun,line,tag,msg);
}*/

void print_error(char *tag,char *msg, ...)   {
      va_list argp;
	va_start(argp,msg);
	int type = 4;
    if(type >  LOG_LERVER)   {
        return ;
    }
    
    if(tag!= NULL && msg != NULL)   {
		printf("[%s]",tag);
        vfprintf(stdout,msg,argp);	
    } else {
        printf("msg is null");
    }
    va_end(argp);
}
