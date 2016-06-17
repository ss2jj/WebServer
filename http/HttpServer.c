#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "HttpServer.h"
#include <pthread.h>
#include "Log.h"

#define TAG "HttpServer"
#define MAX_CONNECTION 20
#define MAXLENGTH 8*1024
#define LINE_MAX 50

static void * HandleHttpRequest(void * arg)	{
	int fd = ((Param *)arg)->fd;
	struct sockaddr_in clientAddr = ((Param *)arg)->clientAddr;
	char * data = NULL;
	HttpRequest request;
	HttpResponse response ;
	
	data = readMessage(fd);
	
	request = parseHttpRequest(data);
	

}
/*启动服务端
* 失败返回 -1
*/
int StartServer(int port_i)	{
	int listenfd,clientfd;
	socklen_t clientaddr_len;
	struct sockaddr_in serverAddr,clientAddr;
	pthread_t ntid;
	Param  p;
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	
	if(listenfd == -1)	{
		print_error(TAG,"socket create failed");
		return -1;
	}
	
	bzero(&serverAddr,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port_i);
	
	if(bind(listenfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr)) == -1)	{
		print_error(TAG,"socket bind failed");
		return -1;
	}
	
	if(listen(listenfd, MAX_CONNECTION) == -1)	{
		print_error(TAG,"socket listen failed");
		return -1;
	}
	print_info(TAG,"linsten port on %d",port_i);
	while(1)	{
		clientaddr_len = sizeof(clientAddr);
		bzero(&clientAddr,clientaddr_len);	
		memset(&p,0,sizeof(Param));
		
		clientfd =  accept(listenfd,(struct sockaddr *)&clientAddr,&clientaddr_len);
		p.fd = clientfd;
		p.clientAddr = clientAddr;
		print_info(TAG,"receive request from %s",inet_ntoa(clientAddr.sin_addr));
		int err = pthread_create(&ntid,NULL,HandleHttpRequest,&p);
		
	}
	
}

char * readMessage(int fd)	{
	char  data[MAXLENGTH];
	int readSize  = 0;
	int totalSize = 0;
	memset(data,0,MAXLENGTH); //data 清零
	
	while(totalSize < MAXLENGTH && (readSize = read(fd,data+readSize,MAXLENGTH)) > 0)	{
		totalSize += readSize;
	}
	
	return data;
}
//解析Http请求
HttpRequest parseHttpRequest(char *data)	{
	HttpRequest request;
	
	char method[LINE_MAX];
	char uri[LINE_MAX];
	char version[LINE_MAX];

	print_info("reque : %s",data);
	sscanf(data, "%s %s %s", method, uri, version);
	
	request.method = method;
	request.uri = uri;
	request.version = version;
	
	return request;
}
