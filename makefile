GCC =gcc
CFLAGS= -g -Wall
all = scanner

scanner:  scanner.o main.o 
	$(GCC) $(CFLAGS) -o scanner  scanner.o main.o 

scanner.o: scanner.c
	$(GCC) $(CFLAGS) -c scanner.c

main.o: main.c
	$(GCC) $(CFLAGS) -c main.c
		

clean: 
	rm *.o scanner
