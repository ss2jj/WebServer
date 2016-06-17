#include "Socketutils.h"
#include <string.h>

#define TAG "SocketUtils"

int Socket(int family, int type, int protocol)	{
	int fd;
	
	fd = socket(family,type,protocol);
	
	if(fd == -1)	{
		print_error(TAG,"socket create failed");
		exit(1);
	}
	
	return fd;
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)	{
	
	if(bind(fd,sa,salen) == -1)	{
		print_error(TAG,"socket bind failed: %s",strerror(errno));
		exit(1);
	}
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)	{
	
	if(connect(fd,sa,salen) == -1)	{
		print_error(TAG,"socket connect failed: %s",strerror(errno));
		exit(1);
	}
}