#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "Configutils.h"
#include "Log.h"

#define PORT_NUM "port"
#define WORK_DIR "workdir"
#define CONFIG_PATH "config.xml"
#define TAG "MAIN"
#define DEFAULT_PORT "8080"
int main(int argc,char ** argv)	{
	char port_c[50];
	char workDir[50];
	int port_i;
	
        /*1 读取端口配置文件 初始化httpd进程*/
	if(ReadConfig(CONFIG_PATH,PORT_NUM,port_c) == 0)	{
		print_error(TAG,"read port error");
		
		strcpy(port_c,DEFAULT_PORT);
	}
	
	if(ReadConfig(CONFIG_PATH,WORK_DIR,workDir) == 1)	{
		print_info(TAG,"change current dir to  %s",workDir);
		char cmd[100] = "cd ";
		strcat(cmd,workDir);
		print_info(TAG,"cmd  %s",cmd);
		chdir(workDir);   //更改当前工作目录;
		
	}
	
	port_i = atoi(port_c);
	
	/*2 设置服务器应答回调*/
	
	print_info(TAG,"read port is %d",port_i);
       /*3 启动httpd进程*/
	
	StartServer(port_i);
	
	
	
	return 1;

}	
