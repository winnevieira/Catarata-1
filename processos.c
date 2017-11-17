#include "processos.h"

//FUNCAO DE CONVERSAO DA IMAGEM EM TONS DE CINZA
Imagem *make_PPM_cinza (Imagem *m) {
	unsigned int i,j;
	int temp;

	Imagem *GreyImage = criarImagem(m->altura, m->largura, m->max);
	strcpy(GreyImage->header, m->header);

	//Colocando no tom cinza, atraves de mudanças nos valores vermelho, verde e azul de cada pixel
	for (i=0; i < m->altura; i++) {
		for (j=0; j < m->largura; j++) {
			temp = 0;
			temp += (unsigned short int) ((m->M[i][j]).r) * 0.3;
			temp += (unsigned short int) ((m->M[i][j]).g) * 0.59;
			temp += (unsigned short int) ((m->M[i][j]).b) * 0.11;

			(GreyImage->M[i][j]).r = temp;
			(GreyImage->M[i][j]).g = temp;
			(GreyImage->M[i][j]).b = temp;
		}
	}
	freeImagem(m);
	return GreyImage;
}


//FUNCAO DE APLICACAO DO FILTRO GAUSSIANO NA IMAGEM
//COMO EXTRA EU POSSO CONTROLAR A QUANTIDADE DE APLICACOES
Imagem *GaussFilter (Imagem *m, int blurtimes) {
	if (blurtimes < 0) {
		fprintf(stderr, "ERRO: Nao pode borrar a imagem %d vezes!\n", blurtimes);
	}
	else if (blurtimes == 0) {
		printf("A imagem nao foi borrada!\n");
		return m;
	}

	int filter[5][5] = {{2,4,5,4,2}, {4,9,12,9,4}, {5,12,15,12,5}, {4,9,12,9,4}, {2,4,5,4,2}};//Filtro Gaussiano
	int i,j,k,l;
	double aux=0;//Variaveis de auxilio para o calculo
	static int count = 0;

	Imagem *GaussImage = criarImagem(m->altura, m->largura, m->max);
	strcpy(GaussImage->header, m->header);

	for (i=0; (unsigned int)i < m->altura; i++) {
		for (j=0; (unsigned int)j < m->largura; j++) {
			aux = 0;
			for (k=0; k < 5; k++) {
				for (l=0; l < 5; l++) {
					if ( (i+k-2 < 0) || (j+l-2 < 0) || ((unsigned int)i+k-2 >= m->altura) || ((unsigned int)j-2+l >= m->largura) ) {
						continue;
					} 

					aux += (double) (m->M[i+k-2][j+l-2].r * filter[k][l])/159;
				}
			}
			GaussImage->M[i][j].r = aux;
			GaussImage->M[i][j].g = aux;
			GaussImage->M[i][j].b = aux;

		}
	}
	if (count == 0) {
		printf("A imagem foi borrada com sucesso %d vez.\n", count + 1);
		++count;
	} 

	else {
		printf("A imagem foi borrada com sucesso %d vezes.\n", count + 1);
		++count;
	}
	if (blurtimes > 1) {
		GaussImage = GaussFilter(GaussImage, blurtimes -1);
	}
	freeImagem(m);
	return GaussImage;
}


//FUNCAO DE APLICACAO DO FILTRO DE SOBEL NA IMAGEM
//COMO EXTRA EU POSSO CONTROLAR A QUANTIDADE DE APLICACOES
Imagem *SobelFilter (Imagem *m, int limite) {
	if (limite < 0) {
		fprintf(stderr, "ERRO: Nao foi possivel aplicar o filtro de sobel vezes!\n");
	}
	else if (limite == 0) {
		printf("O filtro de sobel nao foi aplicado!\n");
		return m;
	}
	int sobel_x[3][3] = {{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};//Filtro para as mudanças horizontais
	int sobel_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};//Filtro para as mudanças verticais
	int i,j,k,l;
	double aux_x=0, aux_y=0;//Variaveis de auxilio para o calculo
	static int count = 0;

	Imagem *SobelImage = criarImagem(m->altura, m->largura, m->max);
	strcpy(SobelImage->header, m->header);

	for (i=0; (unsigned int)i < m->altura; i++) {
		for (j=0; (unsigned int)j < m->largura; j++) {
				//Aqui serao analisados cada pixel da imagem 'entrada'
			aux_x = 0;
			aux_y = 0;
			for (k=0; k < 3; k++) {
				for (l=0; l < 3; l++) {
					if ( (i+k-1 < 0) || (j+l-1 < 0) || ((unsigned int)i-1+k >= m->altura) || ((unsigned int)j-1+l >= m->largura) ) {
						continue;
					} 

					aux_x += (double) m->M[i+k-1][j+l-1].r * sobel_x[k][l];
					aux_y += (double) m->M[i+k-1][j+l-1].r * sobel_y[k][l];
				}
			}
			if (sqrt((aux_x * aux_x) + (aux_y * aux_y)) > m->max) { //Caso ocorra desse valor ultrapassar o tom maximo de RGB, os pixels devem ficar com o valor maximo
				SobelImage->M[i][j].r = m->max;
				SobelImage->M[i][j].g = m->max;
				SobelImage->M[i][j].b = m->max;
			}
			else {
				SobelImage->M[i][j].r = sqrt((aux_x * aux_x) + (aux_y * aux_y));
				SobelImage->M[i][j].g = sqrt((aux_x * aux_x) + (aux_y * aux_y));
				SobelImage->M[i][j].b = sqrt((aux_x * aux_x) + (aux_y * aux_y));
			}
		}
	}
	if (count == 0) {
		printf("O filtro foi aplicado com sucesso %d vez.\n", count + 1);
		++count;
	} 

	else {
		printf("O filtro foi aplicado com sucesso %d vezes.\n", count + 1);
		++count;
	}

	if (limite > 1) {
		SobelImage = SobelFilter(SobelImage, limite-1);
	}
	freeImagem(m);
	return SobelImage;
}