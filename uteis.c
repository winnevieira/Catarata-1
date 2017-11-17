#include "uteis.h"

//AQUI ESTAO FUNCOES QUE SERAO UTEIS NO DECORRER DO CODIGO

//Funcao de criacao de imagens
Imagem *criarImagem(unsigned int altura, unsigned int largura, unsigned int max) {
	Imagem *novaImagem = (Imagem *) calloc(1,sizeof(Imagem));

	novaImagem->altura = altura;
	novaImagem->largura = largura;
	novaImagem->max = max;

	novaImagem->M = alocar_espaco_para_matriz_de_pixels(altura, largura);

	return novaImagem;
}

//Funcao de alocacao de espaco para matriz imagem
Pixel **alocar_espaco_para_matriz_de_pixels(unsigned int altura, unsigned int largura) {
	Pixel **M = calloc(altura,sizeof(Pixel *)); //Alocaçao de criação das linhas
	unsigned int i;
	for (i=0; i<altura; i++) {
		M[i] = calloc(largura,sizeof(Pixel));//Alocação de criação das colunas
	}
	return M;
}

//Funcao para liberar o espaco alocado para imagens
void freeImagem(Imagem *img) {
	unsigned int i;
	for (i=0; i < img->altura; ++i) {
		free(img->M[i]);
	}
	free(img->M);

	free(img);
}

//Funcao de criacao do nome de onde eu quero salvar a imagem construida
char *saidaImagem(char *folder, char *filename, char *formato, char *toAdd) {
	char *outfilename;
	int x = strlen(filename);

	outfilename = (char *) calloc(strlen(folder) + strlen(filename) + strlen(toAdd) + strlen(formato), sizeof(char));//Garantir que haja espaco suficiente em 'outfilename'
	strcpy(outfilename,folder);

	int i = 0;
	int j = strlen(outfilename);
	while (filename[i] != '.') {
		outfilename[j] = filename[i];
		i++;
		j++;
	}

	strcat(outfilename,toAdd);
	outfilename[strlen(outfilename)] = '.';
	strcat(outfilename,formato);
	 
	return outfilename;
}
