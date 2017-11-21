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
	for (i=0; i < altura; i++) {
		M[i] = calloc(largura,sizeof(Pixel));//Alocação de criação das colunas
	}
	return M;
}

//Remove o caminho de diretorio da string
char *tirar_diretorio_do_nome_da_imagem(char *filepath) {

	//Se a o argumento for o proprio arquivo, retorna ele mesmo
	if (!strstr(filepath, "/")) {
		return filepath;
	}

	char *filename_sem_diretorio = (char *) calloc(strlen(filepath),sizeof(char));

	//tira a pasta folder do nome
	int t = strlen(filepath);
	int j;
	for (int i=0; i < t; i++) {
		if (filepath[i] == '/') {
			//variavel para me ajudar a manter o valor de i
			int y = i;
			for (j=0; j < t-i; j++) {
				filename_sem_diretorio[j] = filepath[y+1];
				y++;
			}
			filename_sem_diretorio[j] = '\0';
		}
	}
	return filename_sem_diretorio;
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

int ***alocar_espaco_para_circulos(unsigned int altura, unsigned int largura, int raio) {
	int ***circulos = calloc(altura,sizeof(int **));
	unsigned int i;
	for (i=0; i < altura; i++) {
		circulos[i] = calloc(largura,sizeof(int *));
		for (unsigned int j=0; j < largura; j++) {
			circulos[i][j] = calloc(raio,sizeof(int));
		}
	}
	return circulos;
}

Circulo *criarCirculo(unsigned int altura, unsigned int largura, int raio) {
	Circulo *novoCirculo = (Circulo *) calloc(1,sizeof(Circulo));
	novoCirculo->count = 0;
	novoCirculo->accumulator = alocar_espaco_para_circulos(altura, largura, raio);
	return novoCirculo;
}



