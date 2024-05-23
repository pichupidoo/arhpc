CC = gcc
CFLAGS = -g3 -gdwarf
#LFLAGS = -L./lib/

.PHONY: clean

all: mySimpleComputer.a myTerm.a myBigChars.a myReadkey.a SimpleComputer

genfont: myBigChars.a
	$(CC) -Iinclude ./font.c ./myBigChars/myBigChars.a -o genfont

myReadkey.a: myTerm.a mySimpleComputer.a
	cd myReadkey && make all

mySimpleComputer.a:
	cd mySimpleComputer && make all

myTerm.a:
	cd myTerm && make all
	
myBigChars.a:
	cd myBigChars && make all
	

	
#tests:
#cd tests && make all
	
SimpleComputer:
	cd console && make all

clean:
	rm -f ./sc ./genfont
	cd mySimpleComputer && make clean
	cd myTerm && make clean
	cd myBigChars && make clean
	cd myReadkey && make clean
#cd tests && make clean
	cd console && make clean
	