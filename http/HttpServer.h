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

typedef struct HttpOption_S{
	char * key;
	char * value;
} HttpOption;

typedef struct HttpRequest_S	{
	char * method;
	char * uri;
	char * version;
	HttpOption * options;
	int optionsize;
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



/*���������
* ʧ�ܷ��� -1
*/
int StartServer(int port_i);

/**
* ��fd��ȡ����
*/
char * ReadMessage(int fd);

/**
* ��fdд������
*/
void WriteMessage(int fd,char * data,int size);
/**
*����Http����
*/
HttpRequest * ParseHttpRequest(char *data);

/**
*����http��Ӧͷ
*/
HttpResponse * GenerateHttpResponse(HttpRequest  * request);

/**
* ����http����
**/
void HandleHttpRequest(int fd,struct sockaddr_in clientAddr);
/**
*����http��Ӧ
**/
void  SendHttpResponse(int fd,HttpResponse * response);

/**
*����http����
**/
void  SendHttpRequest(int fd,HttpRequest * request);
/**
*������Դ
**/

void DestoryHttpRequest();



#endif
