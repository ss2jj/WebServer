/**
*http������߼�����
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

/*���������
* ʧ�ܷ��� -1
*/
int StartServer(int port_i);

/**
* ��fd��ȡ����
*/
char * readMessage(int fd);

/**
* ��fdд������
*/
void writeMessage(int fd,char * data);
/**
*����Http����
*/
HttpRequest parseHttpRequest(char *data);

/**
*����http��Ӧͷ
*/
HttpResponse generateHttpResponse(HttpRequest  request);
#endif