/**
*http�����Ӧ��ӿ�
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

//���÷�����Ӧ��ص�
SetHttpServerCallBack();


#endif