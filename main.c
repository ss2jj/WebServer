#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "Configutils.h"
#include "Log.h"

#define PORT_NUM "port"
#define CONFIG_PATH "config.xml"
#define TAG "MAIN"
int main(int argc,char ** argv)	{
	char port_c[50];
	int port_i;
	
    /*1 读取端口配置文件 初始化httpd进程*/
	ReadConfig(CONFIG_PATH,PORT_NUM,port_c);
	
	port_i = atoi(port_c);
	
	/*2 设置服务器应答回调*/
	//SetHttpServerCallBack();
	
	print_info(TAG,"read port is %d",port_i);
    /*3 启动httpd进程*/
	
	StartServer(port_i);
	
	
	
	return 1;

}	
