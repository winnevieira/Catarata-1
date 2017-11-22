CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99

main: uteis.o read.o write.o processos.o
	$(CC) $(CFLAGS) main.c uteis.c read.c write.c processos.c -o talvez.exec -lm

uteis.o: uteis.h

write.o: write.h

read.o: read.h

processos.o: processos.h

clean:
	rm main uteis.o read.o write.o processos.o
