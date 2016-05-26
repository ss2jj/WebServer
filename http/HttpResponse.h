/**
*http服务端应答接口
*
*
**/
#ifndef _HTTP_RESPONSE_
#define _HTTP_RESPONSE_
typedef struct S_RESPONSE	{
	int responseCode;
	char * head;
	char * data;
} Response;

//设置服务器应答回调
SetHttpServerCallBack();


#endif