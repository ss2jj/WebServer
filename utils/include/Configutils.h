/**
*�����ļ��ӿ�
*
*
**/
#ifndef _UTILS_CONFIG_
#define _UTILS_CONFIG_

#include <stdlib.h>
#include <stdio.h>



/**
*  ��ָ��·���ļ��ж�ȡĳ������
*  ʧ�ܷ���0  �ɹ�����1
*    
**/
int ReadConfig(const char *filename,const char * name,char *value);



/**
* ��ĳ������д���ļ�
* ��׷���ļ�β�ķ�ʽ���
**/
int WriteConfig(const char *filename,const char * name,char *value);









#endif
