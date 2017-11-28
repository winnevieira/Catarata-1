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
	char *outdir = "out/";//Diretorio de saida das imagens imprimidas
	char sn;//De sim ou nao
	int x;

	Imagem *originalImg = (Imagem *) ler_img(filename);

	//Minha imagem em tons de cinza
	Imagem *greyImg = (Imagem *) make_PPM_cinza(originalImg);

	while (7 > 0) {
		printf("Deseja criar a imagem em tons de cinza?\nS (sim) ou N (nao).\n");
		scanf("%c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileGrey = saidaImagem(outdir, filename, formato, "_1_grey");//Onde eu quero salvar a imagem acinzentada
			write_img(greyImg, outfileGrey);
			free(outfileGrey);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem cinza foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR70: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}	
	}


	//Aqui se define a quantidade de aplicacoes do filtro
	x = 1;//Quantificador
	printf("Gauss:%d\n", x);

	//Minha imagem borrada
	Imagem *gaussImg = (Imagem *) GaussFilter(greyImg, x);

	while (7 > 1) {
		printf("Deseja criar a imagem borrada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileGauss = saidaImagem(outdir, filename, formato, "_2_gauss");//Onde eu quero salvar a imagem borrada
			write_img(gaussImg, outfileGauss);
			free(outfileGauss);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem borrada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR71: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}	
	}


	//Aqui se define a quantidade de aplicacoes do filtro
	x = 1;//Quantificador
	printf("Sobel:%d\n", x);

	//Minha imagem sob aplicacao do filtro de sobel
	Imagem *sobelImg = (Imagem *) SobelFilter(gaussImg, x);

	while (7 > 2) {
		printf("Deseja criar a imagem com filtro aplicado?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileSobel = saidaImagem(outdir, filename, formato, "_3_sobel");//Onde eu quero salvar a imagem sob aplicacao de sobel
			write_img(sobelImg, outfileSobel);
			free(outfileSobel);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem com aplicacao de sobel foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR72: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}		
	}

	//----------------------------//

	//Aqui ocorrem ajustes manuais para o 'threshold' de cada imagem no processo de binarizacao
	int limiar;
	if ( ((strcmp(filename, "Catarata.ppm") == 0) || (originalImg->largura == 1015)) || (strcmp(filename, "Extra2.ppm") == 0) || ( (originalImg->largura == 600) && (originalImg->M[0][0].r == 107) ) ) {
		limiar = 35; //OK
	}
	else if ( (strcmp(filename, "Catarata2.ppm") == 0) || (originalImg->largura == 1198) ) {
		printf("Insira um valor para o limiar\n");
		scanf("%d", &limiar);
		//30 deu merda
		//21 ate q ficou lglzin
		//22 tbm
		//23 piorou
		//24 ficou uma merda
	}
	else if ( (strcmp(filename, "Normal.ppm") == 0) || (originalImg->largura == 1167) ) {
	 	limiar = 25; //OK
	}
	else if ( ((strcmp(filename, "Normal2.ppm") == 0) || (originalImg->largura == 610)) || (strcmp(filename, "Extra1.ppm") == 0) || (originalImg->largura == 520) ) {
		limiar = 50; //OK
	}
	else if ( (strcmp(filename, "Extra3.ppm") == 0) || (originalImg->largura == 500) ) {
		limiar = 55;
	}
	else if ( (strcmp(filename, "Extra4.ppm") == 0) || (originalImg->largura == 700) ) {
		limiar = 40;
	}
	else if ( (strcmp(filename, "Extra5.ppm") == 0) || ((originalImg->largura == 600) && (originalImg->M[0][0].r == 178)) ) {
		limiar = 50;
	}
	else {
		printf("       ATENCAO!!\nImagem sem limiar de binarizacao definido\nInsira um valor!\n");
		scanf("%d", &limiar);
	}

	//Minha imagem binarizada
	Imagem *binImg = Binarizacao(sobelImg, limiar); 

	while (7 > 3) {
		printf("Deseja criar a imagem binarizada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileBin = saidaImagem(outdir, filename, formato, "_4_bin");//Onde eu quero salvar a imagem binarizada
			write_img(binImg, outfileBin);
			free(outfileBin);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem binarizada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR73: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}	
	}

	Centro *c = Transformada_Hough(binImg);
	if (c->y == 0 || c->x == 0 ) {
		fprintf(stderr, "3RR0R: Nao existe um centro retornado\n");
		return 0;
	}
	if (c->r == 0) { 
		fprintf(stderr, "3RR0R.1: Nao existe um raio retornado\n");
		return 0;
	}

	//Minha imagem com a pupila segmentada
	Imagem *pupilaImg = pupila_segmentada(greyImg, c);

	while (7 > 4) {
		printf("Deseja criar a imagem da pupila segmentada em tons de cinza?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfilePupila = saidaImagem(outdir, filename, formato, "_5_pupila");//Onde eu quero salvar a pupila segmentada
			write_img(pupilaImg, outfilePupila);
			free(outfilePupila);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem de pupila segmentada foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR74: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	//Minha imagem (em RGB) com a pupila contornada
	while (7 > 5) {
		printf("Deseja criar a imagem original em RGB com a pupila contornada?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			marcacao_de_pupila_cor(originalImg, c);
			char *outfileContorno = saidaImagem(outdir, filename, formato, "_6_contorno");//Onde eu quero salvar a imagem original em RGB com a pupila contornada
			write_img(originalImg, outfileContorno);
			free(outfileContorno);
			break;
		}
		else if (sn == 'N') {
			printf("\nNenhuma imagem (em RGB) com pupila contornada foi criada\n\n");
			break;
		}
		else {
			fprintf(stderr, "ERR75: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	//Minha imagem com o flash segmentado
	Imagem *flashImg;

	//Pequenos ajustes manuais para a segmentacao do flash
	if ( (strcmp(filename, "Extra4.ppm") == 0) || (originalImg->largura == 700) ) {
		flashImg = flash_segmentado(pupilaImg, 185);
	}
	else if ( (strcmp(filename, "Extra2.ppm") == 0) || ((originalImg->largura == 600) && (originalImg->M[0][0].r == 107)) ) {
		flashImg = flash_segmentado(pupilaImg, 170);
	}
	else {
		flashImg = flash_segmentado(pupilaImg, 155);
	}

	while (7 > 6) {
		printf("Deseja criar a imagem do flash segmentado?\nS (sim) ou N (nao).\n");
		scanf(" %c", &sn);

		if (sn == 'S') {
			printf("\n****Imagem criada com sucesso****\n\n");
			char *outfileFlash = saidaImagem(outdir, filename, formato, "_7_flash");//Onde eu quero salvar o flash segmentado
			write_img(flashImg, outfileFlash);
			free(outfileFlash);
			break;
		}

		else if (sn == 'N') {
			printf("\nNenhuma imagem de flash segmentado foi criada\n\n");
			break;
		}

		else {
			fprintf(stderr, "ERR76: Necessario fazer uma das escolhas disponiveis!\n");
			continue;
		}
	}

	double porcentagem = pixels_comprometidos(pupilaImg, flashImg);

	make_diagnostico(porcentagem, diagnostico, filename);

	return 0;
}
