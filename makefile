ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif
all: main.o
	$(CC) -o program main.o
main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o
	rm *.exe
	rm *~

run: all
		$(info Please enter a Path to Scan:)./program $(info Please enter a Path to Scan:)
