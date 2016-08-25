/**
*文件帮助接口
*
*
**/
#ifndef _UTILS_FILE_
#define _UTILS_FILE_

#include <stdlib.h>
#include <stdio.h>



/**
*  从指定路径文件中读取数据 文件不存在时会首先创建该文件
*  成功返回读取到的字节数
*    
**/
int FileRead(const char *filename,const char *mode,char *buf,size_t len);



/**
* 将buf里的内容写入文件
*
**/
int FileWrite(const char *filename,const char *mode,char *buf,size_t len);


/**
* 获取指定文件大小
*失败返回-1 成功返回文件大小
**/
int FileSize(const char *filename);


/**
*指定的文件或者文件夹是否存在
*成功返回1 失败返回0
**/

int IsFileExist(const char *filename);

#endif
