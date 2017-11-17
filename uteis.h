#ifndef NaoImporta_h
#define NaoImporta_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	unsigned short int r, g, b; //tons vermelho, verde e azul de cada pixel
} Pixel;

typedef struct {
	char header[5];
	unsigned int altura, largura, max;
	char titulo[30];
	Pixel **M;
} Imagem;

Imagem *criarImagem(unsigned int altura, unsigned int largura, unsigned int max);

Pixel **alocar_espaco_para_matriz_de_pixels(unsigned int altura, unsigned int largura);

void freeImagem(Imagem *img);

char *saidaImagem(char *folder, char *filename, char *formato, char *toAdd);

#endif