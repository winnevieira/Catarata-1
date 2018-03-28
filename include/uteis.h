#ifndef NaoImporta_h
#define NaoImporta_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Struct para definicao de tipo que ira representar cada pixel
typedef struct {
	unsigned short int r, g, b; //tons vermelho, verde e azul de cada pixel
} Pixel;

//Struct para definicao de tipo que ira representar uma imagem
typedef struct {
	char header[5];//Formato encontrado no cabecalho. Ira me dizer a forma da imagem
	unsigned int altura, largura;//Dimensoes da imagem
	unsigned int max;//Valor maximo para um tom de cor
	char titulo[30];
	Pixel **M;
} Imagem;

//Struct para definicao de tipo que ira representar meus circulos
//Especifico para a Transformada de Hough
typedef struct {
	int x,y;//Representacoes da posicao 'x' e 'y'
	int r;//Representacao do raio
} Centro;

//Funcao para a criacao de imagens baseadas num mesmo cabecalho
Imagem *criarImagem(unsigned int altura, unsigned int largura, unsigned int max);

//Funcao para alocar o espaco necessario para a existencia da minha matriz de pixels
Pixel **alocar_espaco_para_matriz_de_pixels(unsigned int altura, unsigned int largura);

//Procedimento para libertar o espaco alocado para imagens
void freeImagem(Imagem *img);

//Funcao de criacao do nome da minha imagem de saida
char *saidaImagem(char *folder, char *filename, char *formato, char *toAdd);

//Funcao para tirar o diretorio do nome da minha imagem
//Na execucao do programa, eu posso colocar qualquer diretorio antes da imagem entra
//que nao havera problema
//Exemplo: ./catarata -i pasta/aleatoria/qualquer/Normal2.ppm -f ppm -o diag.txt
//Minha imagem ainda sera Normal2.ppm
char *tirar_diretorio_do_nome_da_imagem(char *filepath);

//Procedimento para a criacao do meu arquivo texto com o diagnostico sobre Catarata
void make_diagnostico(double porcentoCatarata, char* diagnostico, char* filename);

#endif
