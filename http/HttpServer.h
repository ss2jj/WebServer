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
	int statusCode;
	char * statusCodeDef;
	char * fileName;
	char * contentType;
	int contentLen;
} HttpResponse;

/*���������
* ʧ�ܷ��� -1
*/
int StartServer(int port_i);

/**
* ��fd��ȡ����
*/
char * readMessage(int fd);

/**
*����Http����
*/
HttpRequest parseHttpRequest(char *data);
#endif