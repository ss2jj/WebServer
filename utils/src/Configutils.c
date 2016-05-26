#include "Fileutils.h"
#include "Log.h"
#include "Configutils.h"
#include <string.h>

#define TAG "CONFIGOPERATOR"
#define BUFFER_SIZE  1024
#define MAX_LENGTH 50
#define PARSE_TAG '=' 

typedef struct S_Map	{
	char key[MAX_LENGTH];
	char value[MAX_LENGTH];
} Map;

static int parseString(char * sources,Map * maps)	{
	char * temp1;
	char * temp2;
	char * temp3;
	int len = 0;
	int index = 0;
	
	if(sources == NULL || strlen(sources) == 0 )	{
		print_error(TAG,"sources is null");
		return -1;
	}
	
	print_info(TAG,"sources %s ",sources);
	
	temp2 =  (char *)malloc(2*MAX_LENGTH);
	memset(temp2,0,2*MAX_LENGTH);
	if(temp2 == NULL)	{
		print_error(TAG,"malloc buffer error");
		return -1;
	}
	
	while(sources!=NULL && strlen(sources) > 2 && (temp1 = strstr(sources,"\n")) != 0)	{
		
		len = temp1 - sources; //将整个字串以\r\n分开后前半字串的长度
		print_warn(TAG,"temp1 is %s len %d",temp1,len);
	
		temp2 = strncpy(temp2,sources,len);	//截取后的前半部
		temp2[len+1] = '0';
		
		temp3 = strchr(temp2,PARSE_TAG); //继续将截取前半部以PARSE_TAG分开
		len = temp3 - temp2;
		strncpy(maps[index].key,temp2,len);
		strncpy(maps[index].value,temp3+1,strlen(temp3)-1);
		print_info(TAG,"key is %s value is %s",maps[index].key,maps[index].value);
		memset(temp2,0,2*MAX_LENGTH);
		memset(temp3,0,strlen(temp3));
		index++;
			
		if(strlen(temp1) > 2)	{
			sources = temp1+1; //后半部去掉\r\n继续截取
		}else {
			sources = temp1;
		}
		
		
		print_warn(TAG,"sources %s",sources);			
	}
	//分析最后一对键值对 或者只存储了一对键值对
	if(strlen(sources) > 2)	{
		temp3 = strchr(sources,PARSE_TAG); //继续截取键值对
		len = temp3 - sources;
		strncpy(maps[index].key,sources,len);
		strncpy(maps[index].value,temp3+1,strlen(temp3)-1);
		print_info(TAG,"key is %s value is %s",maps[index].key,maps[index].value);	
		index++;
	}
	
	
	if(temp2 != NULL)	{
		free(temp2);
	}
	
	return index;
}

int ReadConfig(const char *filename,const char * name,char *value)	{
	char * readBUF = NULL;
	Map maps[BUFFER_SIZE];
	int index = 0;
	int i =0;
	if(name == NULL)	{
		print_error(TAG,"file name is null");
		return 0;
	}
	if(value == NULL)	{
		print_error(TAG,"file name is null");
		return 0;
	}
	
	readBUF =  (char *)malloc(BUFFER_SIZE);
	if(readBUF == NULL)	{
		print_error(TAG,"malloc buffer error");
		return 0;
	}
	memset(readBUF,0,BUFFER_SIZE);
	FileRead(filename,"r",readBUF,BUFFER_SIZE); //读取文件到buf buf最大支持1024
	memset(maps,0,BUFFER_SIZE*sizeof(Map));
	index = parseString(readBUF,maps);   //解析键值对
	
	while(i < index && index < BUFFER_SIZE)	{
		
		if(strcmp(name,maps[i].key) == 0)	{
			strncpy(value,maps[i].value,strlen(maps[i].value)+1);
			break; 	
		}
		i++;
		
	}
	
	if(readBUF != NULL)	{
		free(readBUF);
	}
	
	return index;	
}


/**
* 将某个配置写入文件
* 已追加文件尾的方式添加
**/
int WriteConfig(const char *filename,const char * name,char *value)	{
	char * writeBUF;
	
	if(name == NULL)	{
		print_error(TAG,"file name is null");
		return 0;
	}
	if(value == NULL)	{
		print_error(TAG,"file name is null");
		return 0;
	}
	int len = strlen(name)+strlen(value)+2;
	writeBUF = (char *)malloc(len);
	if(writeBUF == NULL)	{
		print_error(TAG,"malloc buffer error");
		return 0;
	}
	memset(writeBUF,0,len);
	sprintf(writeBUF,"%s=%s\n",name,value);
	print_warn(TAG,"wrirte str is  %s",writeBUF);			
	//writeBUF[strlen(name)+strlen(value)+2] = '0';
	FileWrite(filename,"ab+",writeBUF,len);
	if(writeBUF != NULL)	{
		free(writeBUF);
	}
		
		
}

