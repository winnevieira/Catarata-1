#include "uteis.h"
int main(int argc, char const *argv[]) {
	//Testando se os argumentos minimos necessarios foram passados
	if (argc < 7) {
		fprintf(stderr, "A execucao do programa deve atender ao seguinte formato:\n./catarata -i <input-image> -f <input-image-format> -o <diagnose-file>\nExemplo: ./catarata -i Catarata.ppm -f ppm -o Catarata_Diag.ppm\n\n");
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
	printf("Deseja criar a imagem em tons de cinza? Digite S para sim ou N para nao.\n");
	scanf("%c", &sn);

	if (sn == 'S') {
		char *outfileGrey = saidaImagem("out/", filename, formato, "_grey");//Onde eu quero salvar a imagem acinzentada
		write_img(greyImg, outfileGrey);
		free(outfileGrey);

	}
	else if (sn == 'N') {
		printf("Nenhuma imagem cinza foi criada\n");
	}
	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}

	//freeImagem(originalImg);

	printf("Quantas vezes deseja borrar?\n");
	scanf(" %d", &x);

	//Minha imagem borrada
	Imagem *gaussImg = (Imagem *) GaussFilter(greyImg, x);
	printf("A imagem foi borrada um total de %d vezes!\n", x);

	printf("Deseja criar a imagem borrada? Digite S para sim ou N para nao.\n");
	scanf(" %c", &sn);

	if (sn == 'S') {
		if (x == 0) {
			char *outfileGauss = saidaImagem("out/", filename, formato, "_grey_NOgauss");
			write_img(gaussImg, outfileGauss);
			free(outfileGauss);
		}
		else {
			char *outfileGauss = saidaImagem("out/", filename, formato, "_grey_gauss");//Onde eu quero salvar a imagem borrada
			write_img(gaussImg, outfileGauss);
			free(outfileGauss);		
		}
	}
	else if (sn == 'N') {
		printf("Nenhuma imagem borrada foi criada\n");
	}
	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}

	//freeImagem(greyImg);

	printf("Quantas vezes deseja aplicar o filtro de sobel?\n");
	scanf("%d", &x);

	//Minha imagem sob aplicacao do filtro de sobel
	Imagem *sobelImg = (Imagem *) SobelFilter(gaussImg, x);
	printf("O filtro de sobel foi aplicado %d vezes.\n", x);

	printf("Deseja criar a imagem com filtro aplicado? Digite S para sim ou N para nao.\n");
	scanf(" %c", &sn);

	if (sn == 'S') {
		if (x == 0) {
			char *outfileSobel = saidaImagem("out/", filename, formato, "_grey_gauss_NOsobel");
			write_img(sobelImg, outfileSobel);
			free(outfileSobel);
		}
		else {
			char *outfileSobel = saidaImagem("out/", filename, formato, "_grey_gauss_sobel");//Onde eu quero salvar a imagem borrada
			write_img(sobelImg, outfileSobel);
			free(outfileSobel);	
		}
	}
	else if (sn == 'N') {
		printf("Nenhuma imagem com aplicacao de sobel foi criada\n");
	}
	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}

	return 0;
}
