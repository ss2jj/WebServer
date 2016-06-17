#include "Log.h"
#include "Fileutils.h"
#include "Configutils.h"
#include <string.h>

#define FILE_NAME "test.txt"
#define TAG "test_fileutil"



static void test_file();
static void test_config();

int main(void)  {
    test_file();
    test_config();

}

static void test_file()	{
	char * writeBUF = "a=1\r\nb=2\r\nc=3";
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

static void test_config()	{
	 char value[50];
	 print_info(TAG,"test file config write");
	 WriteConfig(FILE_NAME,"testkey","testvalue");
	 WriteConfig(FILE_NAME,"testkey1","testvalue1");
	 WriteConfig(FILE_NAME,"testkey","testvalue");
	 print_info(TAG,"test file config read");
	 ReadConfig(FILE_NAME,"testkey1",value);
	 print_info(TAG,"value is %s \n",value);
}
