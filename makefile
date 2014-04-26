
#other rules
.PHONY: clean
.PHONY: delete


myshell: LineParser.o myshell.o
	gcc -g -m32 -Wall -o myshell LineParser.o myshell.o

LineParser.o: LineParser.c LineParser.h
	gcc -m32 -g -Wall -ansi -c LineParser.c

myshell.o :myshell.c LineParser.h
	gcc -m32 -g -Wall -ansi -c myshell.c

clean:
	rm -f *.o