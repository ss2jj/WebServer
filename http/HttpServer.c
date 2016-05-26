#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "HttpServer.h"
#include "Log.h"

#define TAG "HttpServer"
/*启动服务端
* 失败返回 -1
*/
int StartServer(port_i)	{
	int listenfd;
	struct sockaddr_in serverAddr;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(listenfd == -1)	{
		print_error(TAG,"socket create failed");
		return -1
	}
	
	bzero(&serverAddr,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port_i);
	
	if(bind(listenfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) == -1)	{
		print_error(TAG,"socket bind failed");
		return -1
	}
	
	if(listen(listenfd, 20) == -1)	{
		print_error(TAG,"socket listen failed");
		return -1
	}
	
	while(1)	{
		
	}
	
}

