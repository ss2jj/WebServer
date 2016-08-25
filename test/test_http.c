#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Log.h"
#include "HttpServer.h"
#include "Configutils.h"
#include "Fileutils.h"
#define TAG "TEST_HTTP"

int main(int argc, char **argv)	{
    char * optstring = "i:p:f:";
    int ch;
    char * ip = "127.0.0.1";
    char * path = "option.prop";
    int  port = 8000;
	int i =0;
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
       print_info(TAG,"usage: test_http -i ip -p port -f file path");
      // exit(1);
    
    }   
    
    while((ch = getopt(argc,argv,optstring)) != -1)	{
       switch(ch)	{
       	case 'i':  
		ip = optarg;
		break;
	
	case 'p':
		port = atoi(optarg);
		break;
	case 'f':
		path = optarg;
		break;
	
	default:

                print_info(TAG,"Invalid option!!");
                print_info(TAG,"usage: test_http -i ip -p port -f filepath");
		break;
       
       }
    
    }

    print_info(TAG,"ip : %s port : %d filepath : %s",ip,port,path);
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&serveraddr.sin_addr);
    serveraddr.sin_port = htons(port);
     

    if(IsFileExist(path) == 1)	{
       char value [500];
       if(ReadConfig(path,"method",value)==1)	{
         request.method =  strdup(value);
		 memset(value,0,500);
       }
       
       if(ReadConfig(path,"uri",value)==1)	{
         request.uri =  strdup(value);
		 memset(value,0,500);
       }
       if(ReadConfig(path,"version",value)==1)	{
         request.version =  strdup(value);
		 memset(value,0,500);
       }
       if(ReadConfig(path,"optionsize",value)==1)	{
         request.optionsize =  atoi(strdup(value));
		 memset(value,0,500);
		 
       }
       int length = request.optionsize;
	   print_info(TAG,"length %d",length);
	   if(length > 0 )	{
		   Map maps[length];
		   memset(maps,0,length*sizeof(Map));
		   memset(options,0,5*sizeof(HttpOption));
		   ReadConfigMap(path,maps,4);
		   for(i=0;i<length;i++)	{
			 options[i].key = strdup(maps[i].key);
			 options[i].value = strdup(maps[i].value);	 
		   }
		   request.options = options;
	   }
		
		
    }else {
    
    request.method = "GET";
    request.uri = "/test/pic/bottom061.png";
    request.version = "HTTP/1.1";
    request.optionsize = 5;
   
    request.options = options;
	    
    }
	
		if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == 0)	{
    	print_info(TAG,"connect success");
	
		while(1)	{
		sleep(1);
		SendHttpRequest(sockfd,&request);
		}	
    }


    return 1;

  

}
