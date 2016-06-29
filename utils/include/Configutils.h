/**
*配置文件接口
*
*
**/
#ifndef _UTILS_CONFIG_
#define _UTILS_CONFIG_

#include <stdlib.h>
#include <stdio.h>



/**
*  从指定路径文件中读取某个配置
*  失败返回0  成功返回1
*    
**/
int ReadConfig(const char *filename,const char * name,char *value);



/**
* 将某个配置写入文件
* 已追加文件尾的方式添加
**/
int WriteConfig(const char *filename,const char * name,char *value);









#endif
