#Pastas
srcdir = ./src
objdir = ./obj
indir = ./in
outdir = ./out

#Variaveis
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99 -lm

.PHONY: clean cleanin cleanobj cleanout

main: $(objdir)/uteis.o $(objdir)/read.o $(objdir)/write.o $(objdir)/processos.o
	$(CC) $(CFLAGS) $(srcdir)/main.c $(srcdir)/uteis.c $(srcdir)/read.c $(srcdir)/write.c $(srcdir)/processos.c -o catarata $(CFLAGS)

$(objdir)/uteis.o: $(srcdir)/uteis.h
	mkdir -p obj
	gcc -c $(srcdir)/uteis.c -o $(objdir)/uteis.o $(CFLAGS)

$(objdir)/write.o: $(srcdir)/write.h
	mkdir -p obj
	gcc -c $(srcdir)/write.c -o $(objdir)/write.o $(CFLAGS)

$(objdir)/read.o: $(srcdir)/read.h
	mkdir -p obj
	gcc -c $(srcdir)/read.c -o $(objdir)/read.o $(CFLAGS)

$(objdir)/processos.o: $(srcdir)/processos.h
	mkdir -p obj
	gcc -c $(srcdir)/processos.c -o $(objdir)/processos.o $(CFLAGS)

# Limpa tudo
clean: cleanin cleanout cleanobj
	rm main ./catarata -f

#Limpa o diretorio de entradas
cleanin:
	rm -rf $(indir)
	echo "Arquivo in (com imagens de entrada) foi excluido"

#Limpa o diretorio dos objetos
cleanobj:
	rm -rf $(objdir)
	echo "Arquivo obj (com os objetos) foi excluido"

#Limpa o diretorio das saidas
cleanout:
	rm -rf $(outdir)
	echo "Arquivo out (com os arquivos saida) foi excluido"
