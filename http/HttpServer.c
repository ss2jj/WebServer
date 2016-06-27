#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "HttpServer.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include "Log.h"
#include "Fileutils.h"
#define TAG "HttpServer"
#define MAX_CONNECTION 20
#define MAXLENGTH 1024*8
#define LINE_MAX 100
#define BOOL int
#define TRUE 1
#define FALSE 0

static void itoa(int i,char*string)	{
      int power,j;
      j=i;
      for(power=1;j>=10;j/=10)
      power*=10;
      for(;power>0;power/=10)
       {
           *string++='0'+i/power;
           i%=power;
       }
      *string='\0';
}
	 
static void * handleHttpResponse(int fd,HttpResponse * response)	{
	char  head[1024] = {0};
	char  num[20];
	char * data;
	
	print_info(TAG,"handleHttpResponse");
	 strcat(head,response->version); //添加协议名
	 print_info(TAG,"response head: %s version: %s",head,response->version);
	 strcat(head," "); //空格
	 itoa(response->statusCode,num);
	 strcat(head,num); //状态码
	 strcat(head," "); //空格
	 strcat(head,response->statusCodeDef); //状态描述符
	 strcat(head,"\r\n"); //换行符
	  itoa(response->contentLen,num);
	 strcat(head,"Content-Length:");
	 strcat(head,num);
	 strcat(head,"\r\n"); //换行符
	 strcat(head,"Content-Type:");
	 strcat(head,response->contentType);
	 strcat(head,"\r\n"); //换行符
	 strcat(head,"\r\n"); //换行符
	
	print_info(TAG,"response head: %s",head);
	
	writeMessage(fd,head);
	
	data = (char *) malloc(response->contentLen);
	
	
	if(data == NULL)	{
		print_info(TAG,"malloc failed");
		return ;
	}
	
	FileRead(response->fileName,"r",data,response->contentLen); //读取文件到buf buf最大支持1024
	
	print_info(TAG,"response data: %s",data);
	
	writeMessage(fd,data);
	
	if(data == NULL)	{
		free(data);
		return ;
	}
}
static void * handleHttpRequest(int fd,struct sockaddr_in clientAddr)	{

	char * data = NULL;
	HttpRequest * request;
	HttpResponse * response ;
	
	print_info(TAG,"HandleHttpRequest fd %d",fd);
	data = readMessage(fd);
	print_info(TAG,"readMessage %s",data);
	request = parseHttpRequest(data);
	print_info(TAG,"uri:%s  version:%s",request->uri,request->version);
	printf("uri2:%s  version2:%s",request->uri,request->version);
	response = generateHttpResponse(request);
	handleHttpResponse(fd,response);
}

static char * getMimeType(char * dot)	{
	int i =0;
	char * defaultType = "text/html";
	MimeMap * type = mimeTypes;
	while(type->extension != NULL)	{
		if (strcmp(type->extension, dot) == 0) {
				return type->mimeType;
		}
		type++;
	}
	return defaultType;
	
}
/*启动服务端
* 失败返回 -1
*/
int StartServer(int port_i)	{
	int listenfd,clientfd;
	socklen_t clientaddr_len;
	struct sockaddr_in serverAddr,clientAddr;
	
	pid_t pid;
	
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
	clientaddr_len = sizeof(clientAddr);
	bzero(&clientAddr,clientaddr_len);	
	
	while(1)	{
		
		print_info(TAG,"accept port on %d",port_i);
		clientfd =  accept(listenfd,(struct sockaddr *)&clientAddr,(int *)&clientaddr_len);
	
	
		pid = fork();
		if(pid < -1)	{
			print_error(TAG,"fork failed");
			exit(1);
		}else if(pid == 0)	{
			//close(listenfd);
			handleHttpRequest(clientfd,clientAddr);
			close(clientfd);
		}else {
			close(clientfd);
		}
		
		//close(clientfd);
		
		//print_info(TAG,"receive request from %s",inet_ntoa(clientAddr.sin_addr));
		//int err = pthread_create(&ntid,NULL,HandleHttpRequest,(void *)&p);
		
	}
	
}

char * readMessage(int fd)	{
	 char  data[MAXLENGTH];
	int readSize  = 0;
	
	memset(data,0,MAXLENGTH); //data 清零
	//BOOL bNoDelay = TRUE;
	//setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&bNoDelay, sizeof(BOOL));
	/**	while((readSize = recv(fd, data, MAXLENGTH, 0)) > 0)
	{
		data[readSize-1] = '\0';
		
		print_info(TAG,"read data %s %d",data,readSize);
		memset(data,0,MAXLENGTH); //data 清零
	}**/
	readSize = recv(fd, data, MAXLENGTH, 0);
	

	return strdup(data);
}

void writeMessage(int fd,char * data)	{
	int size = strlen(data);

	send(fd, data, size, 0);
}
//解析Http请求
HttpRequest * parseHttpRequest(char *data)	{
	static HttpRequest request;
	
	char method[LINE_MAX] = {0};
	char uri[LINE_MAX] = {0};
	char version[LINE_MAX] = {0};
		
	memset(&request, 0, sizeof(HttpRequest));
	
	sscanf(data, "%s %s %s", method, uri, version);
	
	print_info(TAG,"method:%s  uri:%s  version:%s",method, uri, version);
	request.method = strdup(method);
	request.uri = strdup(uri);
	request.version = strdup(version);
	print_info(TAG,"uri:%d version:%d",strlen(request.uri),strlen(request.version));
	
	return &request;
}

HttpResponse * generateHttpResponse(HttpRequest  * request)	{
	static HttpResponse response;
	char * uri;
	
	
	print_info(TAG,"request->uri %s request->version %s",request->uri,request->version);
	response.version = request->version;
	uri = request->uri;
	
	print_info(TAG,"uri %s response.version %s",uri,response.version);
	if(!strcmp(uri,"/"))	{
		print_info(TAG,"index is exist %d",IsFileExist("index.html"));
		if(IsFileExist("index.html") || IsFileExist("index.htm"))	{
			response.statusCode = 200;
			response.statusCodeDef ="OK";
			response.fileName = "index.html";
			
		}else {
			print_info(TAG,"file is not exist");
			response.statusCode = 404;
			response.statusCodeDef = "NOT FOUND";
			response.fileName = "404.html";
		}
	}else	{
		uri = uri + 1;
		if(IsFileExist(uri))	{
			response.statusCode = 200;
			response.statusCodeDef = "OK";
			response.fileName = uri ;
		}else {
			response.statusCode = 404;
			response.statusCodeDef = "NOT FOUND";
			response.fileName = "404.html";
		}
		
	}
		
	
	response.contentLen = FileSize(response.fileName);
	response.contentType = getMimeType(strchr(response.fileName,'.'));
	print_info(TAG,"generateHttpResponse end");
	
	return &response;
	
	
}