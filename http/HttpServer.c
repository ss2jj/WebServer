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



MimeMap mimeTypes[] = {
	{".css", "text/css"},
	{".gif", "image/gif"},
	{".htm", "text/html"},
	{".html", "text/html"},
	{".jpeg", "image/jpeg"},
	{".jpg", "image/jpeg"},
	{".js", "application/javascript"},
	{".png", "image/png"},
	{".xml", "text/xml"},
	{NULL, NULL}
};

//数字转为字符串
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
//获取mimetype
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


//资源销毁
static void destoryHttp(char * data,HttpRequest * request, HttpResponse * response)	{
	if(data != NULL)	{
		free(data);
	}

	if(request->method != NULL)	{
		free(request->method);
	}
	
	if(request->uri!= NULL)	{
		free(request->uri);
	}

	if(request->version!= NULL)	{
		free(request->version);
	}
	/**
	if(request != NULL)	{

		//free(request);
	}

	if(response->version != NULL)	{
		free(response->version);
	}

	if(response->statusCodeDef!= NULL)	{
		free(response->statusCodeDef);
	}

	if(response->fileName!= NULL)	{
		free(response->fileName);
	}

	if(response->contentType!= NULL)	{
		free(response->contentType);
	}

	if(response!= NULL)	{
		//free(response);
	}**/
	

	
	
}
	 
void  SendHttpResponse(int fd,HttpResponse * response)	{
	char  head[1024] = {0};
	char  num[20];
	char * data;
	
	print_info(TAG,"SendHttpResponse");
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
	
	WriteMessage(fd,head,-1);
	
	data = (char *) malloc(response->contentLen);
	
	
	if(data == NULL)	{
		print_info(TAG,"malloc failed");
		return ;
	}
	
	memset(data,0,response->contentLen);
	FileRead(response->fileName,"rb+",data,response->contentLen); //读取文件到buf 
	
	//print_info(TAG,"response data: %s",data);
	
	WriteMessage(fd,data,response->contentLen);
	
	if(data != NULL)	{
		free(data);
		return ;
	}
}
void  HandleHttpRequest(int fd,struct sockaddr_in clientAddr)	{

	char * data = NULL;
	HttpRequest * request = NULL;
	HttpResponse * response = NULL;
	
	print_info(TAG,"HandleHttpRequest fd %d",fd);
	data = ReadMessage(fd);
	print_info(TAG,"readMessage %s",data);
	request = ParseHttpRequest(data);
	print_info(TAG,"uri:%s  version:%s",request->uri,request->version);
	response = GenerateHttpResponse(request);
	SendHttpResponse(fd,response);

	destoryHttp(data,request,response);
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
	
	//设置端口可重复使用
	int opt = 1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	
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
			
			HandleHttpRequest(clientfd,clientAddr);
			close(clientfd);
		}else {
			close(clientfd);
		}
		
	}
	
}

char * ReadMessage(int fd)	{
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

void WriteMessage(int fd,char * data,int size)	{
	
	if(size == -1)	{
		size = strlen(data);
	}
	
	
	send(fd, data, size, 0);
	print_info(TAG,"writeMessage over");
}
//解析Http请求
HttpRequest * ParseHttpRequest(char *data)	{
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

HttpResponse * GenerateHttpResponse(HttpRequest  * request)	{
	static HttpResponse response;
	char * uri;
	
	
	print_info(TAG,"request->uri %s request->version %s",request->uri,request->version);
	
	memset(&response, 0, sizeof(HttpResponse));
	response.version = request->version;
	uri = request->uri;
	if(!strcmp(uri,"/"))	{ //请求当前目录index页面
		
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
		uri = uri + 1; //跳过'/'
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
	response.contentType = getMimeType(strrchr(response.fileName,'.'));
	print_info(TAG,"generateHttpResponse end");
	
	return &response;
	
	
}


void SendHttpRequest(int fd,HttpRequest * request)	{
 	char  head[1024] = {0};
        int i =0;

	strcat(head,request->method); //请求方法
        strcat(head," "); //空格
        strcat(head,request->uri); //uri
        strcat(head," "); //空格
        strcat(head,request->version); //状态描述符
        strcat(head,"\r\n"); //换行符

	HttpOption * option = request->options;
	if(option != NULL && request->optionsize != 0)	{
	   while(i < request->optionsize)	{
	       strcat(head,option[i].key);
	       strcat(head,": ");
	       strcat(head,option[i].value);
	       strcat(head,"\r\n");
	       i++;
	   }		
	
	}
	
	WriteMessage(fd,head,-1);	

}
