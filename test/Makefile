CC := gcc 
RM := rm -rf 
INCLUDE = ../utils/include




test_http : test_http.c ../http/HttpServer.c
	$(CC) test_http.c ../http/HttpServer.c -I ../http -I $(INCLUDE)/ -L ../utils  -lutils  -Wl,-rpath=../utils: -o test_http


 
clean :
	$(RM) *.o test_http *.so *.txt
