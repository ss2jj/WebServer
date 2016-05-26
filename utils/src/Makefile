CC := gcc 
RM := rm -rf 
INCLUDE = ../include




test_file : test_fileutils.o log.o fileutils.o configutils.o
	$(CC) test_fileutils.o log.o fileutils.o configutils.o -o test_file 



test_fileutils.o : test_fileutils.c  $(INCLUDE)/Fileutils.h $(INCLUDE)/Fog.h $(INCLUDE)/Configutils.h 
	$(CC) -c  test_fileutils.c -I $(INCLUDE)/

log.o : Log.c $(INCLUDE)/Log.h
	$(CC) -c  Log.c -I $(INCLUDE)/

fileutils.o : Fileutils.c $(INCLUDE)/Fileutils.h
	$(CC) -c Fileutils.c -I $(INCLUDE)/

configutils.o : Configutils.c $(INCLUDE)/Configutils.h
	$(CC) -c Configutils.c -I $(INCLUDE)/
 
clean :
	$(RM) *.o test_file *.so *.txt
