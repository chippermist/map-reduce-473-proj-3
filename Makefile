#Variables
CC = gcc

CFLAGS = -g -std=gnu99 -Wall -Wextra -Wno-unused-parameter -pthread

OBJECT_FILES = project3.o 

#SUFFIX Rule
.SUFFIXES: .c .o

#Set up a phony target to build everything
#.PHONY: all

#all: project3

.c .o:
	$(CC) -c $(CFLAGS) -o $@ $<

project3: $(OBJECT_FILES) 
	ar rcs libstatic.a $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES)-L. -lstatic -o $@
	rm *.o
	@echo "\nCompiled Successfully...\nRun using './project3'"

project3.o : project3.c project3.h


default: 
	gcc -o project3 -Wall -Wunused -g -std=gnu99 small_symmetric_best.c project3.c project3.h

clean:
	rm project3

tarball:
		tar -cvzf ../GARG_Assign3.tar.gz ../CMPSC473_Project3
