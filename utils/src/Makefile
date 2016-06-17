CC := gcc 
RM := rm -rf 
INCLUDE = ../include




test_file : test_fileutils.c
	$(CC) test_fileutils.c -I $(INCLUDE)/ -L ../  -lutils  -Wl,-rpath=.:..:lib: -o test_file 


 
clean :
	$(RM) *.o test_file *.so *.txt
