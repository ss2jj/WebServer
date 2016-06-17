/**
*http服务端逻辑处理
*
*
**/
#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_
#include <sys/types.h>
#include <unistd.h>

typedef struct Param_S 	{
	int fd;
	struct sockaddr_in clientAddr;
} Param;

typedef struct HttpRequest_S	{
	char * method;
	char * uri;
	char * version;
} HttpRequest;

typedef struct HttpResponse_S	{
	int statusCode;
	char * statusCodeDef;
	char * fileName;
	char * contentType;
	int contentLen;
} HttpResponse;

/*启动服务端
* 失败返回 -1
*/
int StartServer(int port_i);

/**
* 从fd读取数据
*/
char * readMessage(int fd);

/**
*解析Http请求
*/
HttpRequest parseHttpRequest(char *data);
#endif