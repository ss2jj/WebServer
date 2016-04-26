#include "log.h"
#include "fileutils.h"
#include <string.h>

#define FILE_NAME "test.txt"
#define TAG "test_fileutil"
int main(void)  {
    char * writeBUF = "yes i am test file";
    char * readBUF = NULL;
    
    print_info(TAG,"test file write");
    
    int writeSize = FileWrite(FILE_NAME,"w+",writeBUF,strlen(writeBUF));
	
	if(writeSize == -1)	{
		print_info(TAG,"test file write fail");
	}else {
		print_info(TAG,"write succed and size is %d \n",writeSize);
	}

	print_info(TAG,"test file size");
	
	int fileSize = FileSize(FILE_NAME);
	
	print_info(TAG,"filesize is %d \n",fileSize);
    
	print_info(TAG,"test file read");

    readBUF = (char *)malloc(strlen(writeBUF)+1);
    
    int readSize = FileRead(FILE_NAME,"r+",readBUF,strlen(writeBUF));
	
	print_info(TAG,"readSize is %d",readSize);
    
    print_info(TAG,"%s \n",readBUF);
    
	if(readBUF != NULL)	{
		free(readBUF);
		readBUF = NULL;
	}
     

}


