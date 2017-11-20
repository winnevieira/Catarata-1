#include "uteis.h"
#include "processos.h"
#include "write_img.h"
#include "talvezread.h"
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


	x = 1;//Quantificador


	//Minha imagem borrada
	Imagem *gaussImg = (Imagem *) GaussFilter(greyImg, x);

	printf("Deseja criar a imagem borrada? Digite S para sim ou N para nao.\n");
	scanf(" %c", &sn);

	if (sn == 'S') {
		char *outfileGauss = saidaImagem("out/", filename, formato, "_gauss");//Onde eu quero salvar a imagem borrada
		write_img(gaussImg, outfileGauss);
		free(outfileGauss);		
	}

	else if (sn == 'N') {
		printf("Nenhuma imagem borrada foi criada\n");
	}

	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}


	x = 1;//Quantificador


	//Minha imagem sob aplicacao do filtro de sobel
	Imagem *sobelImg = (Imagem *) SobelFilter(gaussImg, x);

	printf("Deseja criar a imagem com filtro aplicado? Digite S para sim ou N para nao.\n");
	scanf(" %c", &sn);

	if (sn == 'S') {
		char *outfileSobel = saidaImagem("out/", filename, formato, "_sobel");//Onde eu quero salvar a imagem sob aplicacao de sobel
		write_img(sobelImg, outfileSobel);
		free(outfileSobel);	
	}

	else if (sn == 'N') {
		printf("Nenhuma imagem com aplicacao de sobel foi criada\n");
	}

	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}

	//----------------------------//

	//Minha imagem binarizada
	int limiar;
	if (strcmp(filename, "c1.ppm") == 0) {
		limiar = 29;
	}

	else if (strcmp(filename, "c2.ppm") == 0) {
		limiar = 40;//Sla esse carai, dps vejo
	}
// E ETC

	Imagem *binImg = Binarizacao(sobelImg, 55); 

	printf("Deseja criar a imagem binarizada? Digite S para sim ou N para nao.\n");
	scanf(" %c", &sn);

	if (sn == 'S') {
		char *outfileBin = saidaImagem("out/", filename, formato, "_sobel_bin");//Onde eu quero salvar a imagem binarizada
		write_img(binImg, outfileBin);
		free(outfileBin);	
	}

	else if (sn == 'N') {
		printf("Nenhuma imagem binarizada foi criada\n");
	}

	else {
		fprintf(stderr, "ERRO:Necessario fazer uma escolha!\n");
		return 0;
	}


	return 0;
}
