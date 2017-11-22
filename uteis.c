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
	for (int i=t-1; i >= 0; i--) {
		if (filepath[i] == '/') {
			//variavel para me ajudar a manter o valor de i
			int y = i;
			for (j=0; j < t-1-i; j++) {
				filename_sem_diretorio[j] = filepath[y+1];
				y++;
			}
			filename_sem_diretorio[j+1] = '\0';
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

//Procedimento para escrita do diagnostico de catarata
// void make_diagnostico (double porcentoCatarata, char* diagnostico) {

// 	char *new_diagnostico = calloc(strlen(diagnostico) + 10,sizeof(char));
// 	sprintf(new_diagnostico, "out/%s", diagnostico);
// 	FILE *arquivo = fopen(new_diagnostico, "w");

// 	if (arquivo == NULL) {
// 		fprintf(stderr, "ERR4R: Erro na criacao do arquivo com diagnostico\n");
// 		return 0;
// 	}

// 	//Caso mais de 9% dos pixels do olho estiverem com a doenca, considera-se que o individuo possui catarata
// 	if (porcentoCatarata >= 9) {
// 		fprintf(arquivo, "Indivíduo com Catarata\nPorcentagem da pupila com a doença: %.3lf\n", porcentoCatarata);
// 	}
// 	else {
// 		fprintf(arquivo, "Indivíduo sem Catarata\nPorcentagem da pupila com a doença: %.3lf\n", porcentoCatarata);
// 	}

// 	fclose(arquivo)
// }
