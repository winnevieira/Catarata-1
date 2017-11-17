CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99

main: uteis.o talvezread.o write_img.o processos.o
	$(CC) $(CFLAGS) maindotalvezread.c uteis.c talvezread.c write_img.c processos.c -o talvez.exec -lm

uteis.o: uteis.h

write_img.o: write_img.h

talvezread.o: talvezread.h

processos.o: processos.h

clean:
	rm main uteis.o talvezread.o write_img.o processos.o