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
//Na execucao do programa, eu posso colocar qualquer diretorio antes da imagem entra
//que nao havera problema
//Exemplo: ./catarata -i pasta/aleatoria/qualquer/Normal2.ppm -f ppm -o diag.txt
//Minha imagem ainda sera Normal2.ppm
char *tirar_diretorio_do_nome_da_imagem(char *filepath) {

	//Se a o argumento for o proprio arquivo, retorna ele mesmo
	if (!strstr(filepath, "/")) {
		return filepath;
	}

	char *filename_sem_diretorio = (char *) calloc(strlen(filepath),sizeof(char));

	//Tira a pasta folder do nome
	int t = strlen(filepath);
	int j;
	for (int i=t-1; i >= 0; i--) {
		if (filepath[i] == '/') {
			//Variavel para me ajudar a manter o valor de i
			int y = i;
			for (j=0; j < t-1-i; j++) {
				filename_sem_diretorio[j] = filepath[y+1];
				y++;
				printf("%c\n", filename_sem_diretorio[j]);
			}
			break;
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
	system("mkdir -p out");

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

//Procedimento para escrita do diagnostico sobre a existencia ou nao de catarata no olho
void make_diagnostico(double percentCatarata, char* diagnostico, char* filename) {
	system("mkdir -p out");//Para o caso de eu nao imprimir nenhuma imagem anteriormente
	char *temp = calloc(strlen(filename),sizeof(char));
	char *new_diagnostico = calloc(strlen(diagnostico) + strlen(filename) + 6,sizeof(char));//Alocando espaço suficiente para o nome do arquivo acrescido da imagem e diretorio

	for (int i=0; i < strlen(filename); i++) {
		if (filename[i] == '.') {
			//Pegando somente o nome da imagem, esquecendo o tipo de imagem
			strncat(temp, filename, i);
		}
	}

	sprintf(new_diagnostico, "out/%s_%s", temp, diagnostico);
	FILE *arquivo = fopen(new_diagnostico, "w");

	if (arquivo == NULL) {
		fprintf(stderr, "ERR4R: Erro na criacao do arquivo com diagnostico\n");
		exit(1);
	}

	//Caso mais de 9% dos pixels do olho estiverem comprometidos, considera-se que o individuo possui catarata
	if (percentCatarata >= 9) {
		fprintf(arquivo, "Imagem Analisada: %s\n\nSituação do indivíduo: Com Catarata\nPorcentagem de comprometimento da pupila: %.2lf%%\nFim do diagnóstico.",filename, percentCatarata);
	}
	else {
		fprintf(arquivo, "Imagem Analisada: %s\n\nSituação do indivíduo: Sem Catarata\nPorcentagem de comprometimento da pupila: %.2lf%%\nFim do diagnóstico.",filename, percentCatarata);
	}

	free(temp);
	fclose(arquivo);
}
