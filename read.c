#include "read.h"

//Funcao de leitura de arquivo, identificacao da imagem(cabecalho e pixels) e retirada de comentarios
Imagem *ler_img(char *filename) {
	FILE *arquivo;
	char *formato = calloc(4,sizeof(char));//Essa variavel serve somente para guardar o formato de uma imagem, para poder repassar essa informacao depois
	unsigned int i,j,a;
	char *str_check = calloc(73,sizeof(char));//Variavel para checar se ha '#'
	unsigned int altura, largura, max;

	char *real_filename = calloc(strlen(filename) + 5,sizeof(char));//Considerando a pasta com as imagens, devo adiciona-la ao nome da imagem
	sprintf(real_filename, "in/%s", filename);
	Imagem *m;// Criando minha variavel de controle de imagens

	arquivo = fopen(real_filename, "r");
	if (arquivo == NULL) {
		fprintf(stderr, "Erro de abertura de imagem\n");
		exit(1);
	}
	
	//Agora ler os dados contidos no cabecalho
	while (5 < 8) { //Aqui eu checo se existem comentarios antes da informacao do header. Se existirem, eu os pulo ate chegar no header
		fscanf(arquivo, "%s", str_check);
		if (str_check[0] == '#') {
			fgets(str_check, 71, arquivo);
		}
		else {
			strcpy(formato, str_check);
			if (strcmp(str_check, "P3") != 0) {
				fprintf(stderr,"ERRO:Formato de imagem diferente!\n");
				fclose(arquivo);
				exit(1);
			}
			break;
		}
	}

	while(5 < 8) {  //Aqui eu checo se existem comentarios entre a linha que informa header, e a linha que informa largura e altura. Se existirem, eu os pulo ate chegar na linha de largura e altura
		fscanf(arquivo, "%s", str_check);
		if (str_check[0] == '#') {
			fgets(str_check, 71, arquivo);
		}
		else {
			a = strlen(str_check);
			largura = 0; //A largura (em pixels) da imagem
			for (i=0, j=a-1; i<a; i++, j--) { //Como a largura (um unsigned int) foi salva no str_check(uma string de char), preciso converter para obter minha largura
				largura += (unsigned int) (str_check[i] - 48) * pow(10,j);//Convertendo o valor do caracter para um valor decimal (de acordo com a tabela ASCII)
			}
			break;
		}
	}

	fscanf(arquivo, " %u", &altura);//A altura (em pixels) da imagem

	while (5 < 8) { //Aqui eu checo se existem comentarios entre a linha de lagura e altura, e a linha do max. Se existirem, eu os pulo ate chegar na linha que me informa o max
		fscanf(arquivo, "%s", str_check);
		if (str_check[0] == '#') {
			fgets(str_check, 71, arquivo);
		}
		else {
			a = strlen(str_check);
			max = 0; //Valor maximo de um tom de cor
			for (i=0, j=a-1; i<a; i++, j--) { //Como o max (um unsigned int) foi salvo no str_check(uma string de char), preciso converter para obter meu max
				max += (unsigned int) (str_check[i] - 48) * pow(10,j); //Convertendo o valor do caracter para um valor decimal (de acordo com a tabela ASCII)
			}
		break;
		}
	}

	m = criarImagem(altura, largura, max);
	strcpy(m->header, formato);

	unsigned short int temp;

	for (i=0; i < m->altura; i++) {
		for (j=0; j < m->largura; j++) {
			fscanf(arquivo, "%hu", &temp);//Lendo a cor vermelha do pixel
			(m->M[i][j]).r = temp;
			fscanf(arquivo, "%hu", &temp);//Lendo a cor verde do pixel
			(m->M[i][j]).g = temp;
			fscanf(arquivo, "%hu", &temp);//Lendo a cor azul do pixel
			(m->M[i][j]).b = temp;
		}
	}

	free(formato);
	free(str_check);
	fclose(arquivo);
	return m;
}
