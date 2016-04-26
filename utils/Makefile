CC := gcc 
RM := rm -rf 
INCLUDE = incude/


all:so


test_file : test_fileutils.o 
	$(CC) test_fileutils.o  -o test_file -L ./ -lutils

so : log.o fileutils.o
	g++ -fPIC -shared -o libutils.so log.o fileutils.o

test_fileutils.o : src/test_fileutils.c  include/fileutils.h include/log.h 
	$(CC) -c src/test_fileutils.c -I include/

log.o : src/log.c include/log.h
	$(CC) -c -fPIC src/log.c -I include/

fileutils.o : src/fileutils.c include/fileutils.h
	$(CC) -c -fPIC src/fileutils.c -I include/

 
clean :
	$(RM) *.o test_file *.so
