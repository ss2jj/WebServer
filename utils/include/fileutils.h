/**
*�ļ������ӿ�
*
*
**/
#ifndef _UTILS_FILE_
#define _UTILS_FILE_

#include <stdlib.h>
#include <stdio.h>



/**
*  ��ָ��·���ļ��ж�ȡ���� �ļ�������ʱ�����ȴ������ļ�
*  �ɹ����ض�ȡ�����ֽ���
*    
**/
int FileRead(const char *filename,const char *mode,char *buf,size_t len);



/**
* ��buf�������д���ļ�
*
**/
int FileWrite(const char *filename,const char *mode,char *buf,size_t len);


/**
* ��ȡָ���ļ���С
*
**/
int FileSize(const char *filename);






#endif
