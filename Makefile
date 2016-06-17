CC := gcc 
RM := rm -rf 
INCLUDE = utils/include
HTTP := http



httpd : main.c $(HTTP)/HttpServer.c
	$(CC) main.c $(HTTP)/HttpServer.c -I $(INCLUDE)/ -L utils/  -lutils  -Wl,-rpath=utils: -lpthread -o httpd  

#HttpServer.o : $(HTTP)/HttpServer.c $(HTTP)/HttpServer.h
#	$(CC) $(HTTP)/HttpServer.c  -I $(INCLUDE)/ -Wl,-Bstatic  -lpthread -Wl,-Bdynamic -L utils/ -lutils
 
clean :
	$(RM) *.o httpd *.so 
