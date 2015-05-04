#Variables
CC = gcc

CFLAGS = -g -std=gnu99 -Wall -Wextra -Wno-unused-parameter -pthread

OBJECT_FILES = cmpsc473mr.o 

#SUFFIX Rule
.SUFFIXES: .c .o

#Set up a phony target to build everything
#.PHONY: all

#all: project

.c .o:
	$(CC) -c $(CFLAGS) -o $@ $<

project: $(OBJECT_FILES) 
	ar rcs libstatic.a $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES)-L. -lstatic -o $@
	rm *.o
	@echo "\nCompiled Successfully...\nRun using './project'"

cmpsc473mr.o : cmpsc473mr.c cmpsc473mr.h

clean:
	rm project

tarball:
		tar -cvzf ../GARG_Assign3.tar.gz ../CMPSC473_Project3
