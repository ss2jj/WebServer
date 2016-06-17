CC := gcc 
RM := rm -rf 
INCLUDE = incude/





so : Log.o Fileutils.o Configutils.o
	g++ -fPIC -shared -o libutils.so Log.o Fileutils.o Configutils.o

Log.o : src/Log.c include/Log.h
	$(CC) -c -fPIC src/Log.c -I include/

Fileutils.o : src/Fileutils.c include/Fileutils.h
	$(CC) -c -fPIC src/Fileutils.c -I include/

Configutils.o : src/Configutils.c include/Configutils.h
	$(CC) -c -fPIC src/Configutils.c -I include/
	
clean :
	$(RM) *.o test_file *.so
