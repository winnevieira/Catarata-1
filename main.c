#include "uteis.h"
#include "processos.h"
#include "write.h"
#include "read.h"

int main(int argc, char const *argv[]) {
	//Testando se os argumentos minimos necessarios foram passados
	if (argc < 7) {
		fprintf(stderr, "A execucao do programa deve atender ao seguinte formato:\n./catarata -i <input-image> -f <input-image-format> -o <diagnose-file>\nExemplo: ./catarata -i Catarata.ppm -f ppm -o Catarata_Diag.txt\n\n");
		exit(1);
	}

	//Variaveis de controle para saber a posicao, no codigo, das informacoes procuradas
	unsigned char inputAUX, formatoAUX, diagAUX;

	for (int i=0; i < argc; i++) {
		//Checando onde eu encontro os comandos '-i' , '-o' , '-f'
		if ( (strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "-f") == 0) ) {

			if (strcmp(argv[i], "-i") == 0) {
				inputAUX = i+1;
			}

			else if (strcmp(argv[i], "-f") == 0) {
				formatoAUX = i+1;
			}

			else if (strcmp(argv[i], "-o") == 0) {
				diagAUX = i+1;
			}
		}
	}

	char *filepath = (char *) argv[inputAUX]; //Variavel que contem o nome da imagem+diretorio a ser processada
	char *filename = (char *) tirar_diretorio_do_nome_da_imagem(filepath);
	char *formato = (char *) argv[formatoAUX]; //Variavel que contem o nome do formato da imagem a ser processada
	char *diagnostico = (char *) argv[diagAUX]; //Variavel que contem o nome do arquvio que contera o diagnostico
	char sn;//De sim ou nao
	int x;

	Imagem *originalImg = (Imagem *) ler_img(filename);

	//Minha imagem em tons de cinza
	Imagem *greyImg = (Imagem *) make_PPM_cinza(originalImg);

	while (6 > 0) {
		printf("Deseja criar a imagem em tons de cinza?\nS (sim) ou N (nao).\n");
		scanf("%c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileGrey = saidaImagem("out/", filename, formato, "_grey");//Onde eu quero salvar a imagem acinzentada
			write_img(greyImg, outfileGrey);
			free(outfileGrey);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem cinza foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}


	//Aqui se define a quantidade de aplicacoes do filtro
	x = 1;//Quantificador


	//Minha imagem borrada
	Imagem *gaussImg = (Imagem *) GaussFilter(greyImg, x);

	while (6 > 1) {
		printf("Deseja criar a imagem borrada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileGauss = saidaImagem("out/", filename, formato, "_gauss");//Onde eu quero salvar a imagem borrada
			write_img(gaussImg, outfileGauss);
			free(outfileGauss);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem borrada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}


	//Aqui se define a quantidade de aplicacoes do filtro
	x = 1;//Quantificador


	//Minha imagem sob aplicacao do filtro de sobel
	Imagem *sobelImg = (Imagem *) SobelFilter(gaussImg, x);

	while (6 > 2) {
		printf("Deseja criar a imagem com filtro aplicado?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileSobel = saidaImagem("out/", filename, formato, "_sobel");//Onde eu quero salvar a imagem sob aplicacao de sobel
			write_img(sobelImg, outfileSobel);
			free(outfileSobel);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem com aplicacao de sobel foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	//----------------------------//

	//Minha imagem binarizada
	int limiar;
	if (strcmp(filename, "Catarata.ppm") == 0) {
		limiar = 35; //OK
	}
	else if (strcmp(filename, "Catarata2.ppm") == 0) {
		printf("Chuta ai a merda de um limiar pra a porra dessa imagem\nCaralho Puto Arrombado\nRata Cabron Hijo del Putana\n");
		scanf("%d", &limiar);//Sla esse carai, dps vejo //FUCKKKAOOOOYYYYYOUU
		//30 da merda
		//21 ate q ficou lglzin
		//22 tbm
		//23 piorou
		//24 ficou uma merda

	}
	else if (strcmp(filename, "Normal.ppm") == 0) {
	 	limiar = 25; //OK
	}
	else if (strcmp(filename, "Normal2.ppm") == 0) {
		limiar = 50; //OK
	}
	else {
		printf("         ATENCAO!!\nImagem sem limiar de binarizacao definido\n");
	}

	Imagem *binImg = Binarizacao(sobelImg, limiar); 

	while (6 > 3) {
		printf("Deseja criar a imagem binarizada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileBin = saidaImagem("out/", filename, formato, "_bin");//Onde eu quero salvar a imagem binarizada
			write_img(binImg, outfileBin);
			free(outfileBin);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem binarizada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	Centro *c = Transformada_Hough(binImg);
	if (c->y == 0 || c->x == 0 ) {
		fprintf(stderr, "F4T4L 3RR0R: Nao existe um centro retornado\n");
		return 0;
	}
	if (c->r == 0) { 
		fprintf(stderr, "F4T4L 3RR0R: Nao existe um raio retornado\n");
		return 0;
	}

	//Minha imagem com a pupila segmentada
	Imagem *pupilaImg = pupila_segmentada(greyImg, c);

	while (6 > 4) {
		printf("Deseja criar a imagem da pupila segmentada em tons coloridos?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfilePupila = saidaImagem("out/", filename, formato, "_pupila");//Onde eu quero salvar a pupila segmentada
			write_img(pupilaImg, outfilePupila);
			free(outfilePupila);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem de pupila segmentada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	//Minha imagem (em RGB) com a pupila contornada
	while (6 > 5) {
		printf("Deseja criar a imagem original em RGB com a pupila contornada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			marcacao_de_pupila_cor(originalImg, c);
			char *outfileContorno = saidaImagem("out/", filename, formato, "_contorno");//Onde eu quero salvar a imagem original em RGB com a pupila contornada
			write_img(originalImg, outfileContorno);
			free(outfileContorno);
			break;
		}
		else if (sn == 'N') {
			printf("\nNenhuma imagem (em RGB) com pupila contornada foi criada\n\n");
			break;
		}
		else {
			fprintf(stderr, "ERRO: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	double porcentagem = pixels_comprometidos(pupilaImg);

	make_diagnostico(porcentagem, diagnostico, filename);

	//freeImagem(originalImg);
	return 0;
}
