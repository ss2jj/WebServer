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
	pid_t pid;
    /*1 读取端口配置文件 初始化httpd进程*/
	ReadConfig(CONFIG_PATH,PORT_NUM,port);
	
	port_i = atoi(port);
	
	/*2 设置服务器应答回调*/
	SetHttpServerCallBack();
	
	
    /*3 启动httpd进程*/
	pid = fork();
	if(pid < -1)	{
		print_error(TAG,"fork failed");
		exit(1);
	}else if(pid == 0)	{
		print_info(TAG,"start child process");
		// 成为守护进程
		if (setsid() < 0) {
			print_error("error breaking from process group");
		}
		StartServer(port_i);
	}else {
		exit(1);
	}
	
	return 1;

}	
