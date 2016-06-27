CC := gcc 
RM := rm -rf 
INCLUDE = utils/include
HTTP := http
UTILS := utils

all:
	cd $(UTILS)/ && make
	make httpd

httpd : main.c $(HTTP)/HttpServer.c
	$(CC) main.c $(HTTP)/HttpServer.c -I $(INCLUDE)/ -L $(UTILS)/  -lutils  -Wl,-rpath=$(UTILS): -lpthread -o httpd  

#HttpServer.o : $(HTTP)/HttpServer.c $(HTTP)/HttpServer.h
#	$(CC) $(HTTP)/HttpServer.c  -I $(INCLUDE)/ -Wl,-Bstatic  -lpthread -Wl,-Bdynamic -L utils/ -lutils
 
clean :
	$(RM) *.o httpd *.so $(UTILS)/*.o $(UTILS)/*.so
