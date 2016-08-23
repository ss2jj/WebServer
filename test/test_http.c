#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Log.h"
#include "HttpServer.h"

#define TAG "TEST_HTTP"

int main(int argc, char **argv)	{
    char * optstring = "i:p:";
    int ch;
    char * ip;
    int  port;
    HttpOption options[5] = {
	    		     {"Accept","image/png, image/svg+xml, image/*;q=0.8, */*;q=0.5"},
    			     {"Accept-Language","zh-CN"},
			     {"User-Agent","Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko"},
			     {"Accept-Encoding","gzip, deflate"},
			     {"Connection","Keep-Alive"}
			     
			     	    };
    static HttpRequest request; 
    int sockfd;	
    struct sockaddr_in serveraddr;

    if(argc < 2)	{
       print_info(TAG,"usage: test_http -i ip -p port");
       exit(1);
    
    }   
    
    while((ch = getopt(argc,argv,optstring)) != -1)	{
       switch(ch)	{
       	case 'i':  
		ip = optarg;
		break;
	
	case 'p':
		port = atoi(optarg);
		break;
	
	default:

                print_info(TAG,"Invalid option!!");
                print_info(TAG,"usage: test_http -i ip -p port");
		break;
       
       }
    
    }

    print_info(TAG,"ip : %s port : %d",ip,port);
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);
     

    request.method = "GET";
    request.uri = "/test/pic/bottom061.png";
    request.version = "HTTP/1.1";
    request.optionsize = 5;
   
    request.options = options;

    if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == 0)	{
    	print_info(TAG,"connect success");
	SendHttpRequest(sockfd,&request);
    	
    }


    return 1;

  

}
