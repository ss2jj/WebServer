#include "Fileutils.h"
#include "Log.h"
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#define TAG "FILEOPERATOR"

int FileRead(const char *fileName,const char *mode,char *buf,size_t len) {
    FILE *fp;
    int readSize = 0;
    int totalRead = 0;
    
	

    if(fileName == NULL)    {
       print_error(TAG,"file name is null");
       return -1;
    }

    if(buf == NULL) {
       print_error(TAG,"buf is null");
       return -1;
        
    }

    if((fp = fopen(fileName,mode)) == NULL) {
        print_error(TAG,"file open failed");
        return -1;
    }
    
    while(feof(fp) == 0 &&  totalRead < len)  {
		
       if((readSize = fread(buf+totalRead,1,len-totalRead,fp)) <= 0) {
            print_info(TAG,"read error or complete");
            break;   
        }else {
			print_info(TAG,"read continue %d",readSize);
		}
		
        totalRead += readSize;
        
    }
	print_info(TAG,"read over");
    fclose(fp);
    return totalRead;

}


int FileWrite(const char *fileName,const char *mode,char *buf,size_t len)    {
    FILE *fp;
    int totalWrite = 0;
    int writeSize = 0;    

    if(fileName == NULL)    {
       print_error(TAG,"file name is null");
       return -1;
    }

    if(buf == NULL) {
       print_error(TAG,"buf is null");
       return -1;

    }

    if((fp = fopen(fileName,mode)) == NULL) {
        print_error(TAG,"file open failed");
        return -1;
    }
    
    while(totalWrite < len)    {
        if((writeSize = fwrite(buf+totalWrite,1,len-totalWrite,fp)) <= 0)   {
            print_info(TAG,"write error or complete");
			break;
        }
        fflush(fp);
        totalWrite += writeSize;
    }
    
    fclose(fp);

    return totalWrite;
}


int FileSize(const char *fileName)  {
    FILE *fp;
    int fileLen = -1;
    if(fileName == NULL)    {                                                                                                                                   
       print_error(TAG,"file name is null");                                                                                                                    
       return -1;                                                                                                                                               
    }
          
    if((fp = fopen(fileName,"r+")) == NULL) {
        print_error(TAG,"file open failed");                                                                                                                    
        return -1;
    }

    fseek(fp,0,SEEK_END);
    
    fileLen = ftell(fp);

    fclose(fp);

    return fileLen;

}

int IsFileExist(const char *filename)	{
	
	FILE *fp;
	struct stat buf;
	
	if(filename == NULL)    {                                                                                                                                   
       print_error(TAG,"file name is null");                                                                                                                    
       return 0;                                                                                                                                               
    }
          
    /**if((fp = fopen(filename,"r")) == NULL) {
        print_error(TAG,"file open failed");                                                                                                                    
        return 0;
    }**/
	
	int result = stat(filename,&buf);
	if(result != 0)	{
		print_info(TAG,"error %d",errno);    
	}
	//print_info(TAG,"result %d",result);    
	return result==0?1:0;
}
