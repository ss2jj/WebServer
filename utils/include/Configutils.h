/**
*�����ļ��ӿ�
*
*
**/
#ifndef _UTILS_CONFIG_
#define _UTILS_CONFIG_

#include <stdlib.h>
#include <stdio.h>

#define MAX_LENGTH 500
typedef struct S_Map	{
	char key[MAX_LENGTH];
	char value[MAX_LENGTH];
} Map;

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

/**
*���ؼ�ֵ��
*index ��index����ʼ
**/
void  ReadConfigMap(const char * filename,Map * maps,int index);






#endif
