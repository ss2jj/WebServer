#include "log.h"



void log_print(int type,char *tag,char *msg)    {
    if(type >  LOG_LERVER)   {
        return ;
    }
    
    if(tag!= NULL && msg != NULL)   {
        printf("[%s] %s",tag,msg);
    } else {
        printf("msg is null");
    }
    

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


}
