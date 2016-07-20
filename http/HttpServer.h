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
	char * version;
	int statusCode;
	char * statusCodeDef;
	char * fileName;
	char * contentType;
	int contentLen;
} HttpResponse;


typedef struct {
	char * extension;
	char * mimeType;
} MimeMap;

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

/*启动服务端
* 失败返回 -1
*/
int StartServer(int port_i);

/**
* 从fd读取数据
*/
char * ReadMessage(int fd);

/**
* 往fd写入数据
*/
void WriteMessage(int fd,char * data,int size);
/**
*解析Http请求
*/
HttpRequest * ParseHttpRequest(char *data);

/**
*生成http回应头
*/
HttpResponse * GenerateHttpResponse(HttpRequest  * request);

/**
* 处理http请求
**/
void HandleHttpRequest(int fd,struct sockaddr_in clientAddr);
/**
*处理http回应
**/
void  HandleHttpResponse(int fd,HttpResponse * response);

/**
*销毁资源
**/

void HandleHttpRequest();



#endif
