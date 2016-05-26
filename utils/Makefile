CC := gcc 
RM := rm -rf 
INCLUDE = incude/





so : log.o fileutils.o configutils.o
	g++ -fPIC -shared -o libutils.so log.o fileutils.o configutils.o

log.o : src/Log.c include/Log.h
	$(CC) -c -fPIC src/Log.c -I include/

fileutils.o : src/Fileutils.c include/Fileutils.h
	$(CC) -c -fPIC src/Fileutils.c -I include/

configutils.o : src/Configutils.c include/Configutils.h
	$(CC) -c -fPIC src/Configutils.c -I include/
	
clean :
	$(RM) *.o test_file *.so
