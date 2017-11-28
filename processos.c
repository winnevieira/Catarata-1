#include "processos.h"

////Funcao de criacao da minha imagem entrada em tons de cinza
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
	//freeImagem(m);
	//Nao dou free aqui para guardar a imagem original para uso posterior
	return GreyImage;
}


//Funcao de aplicacao do filtro de gauss na minha imagem passada por parametro
//Como extra eu posso controlar a quantidade de aplicacoes
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
			//Cada pixel
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

	if (!GaussImage) {
		fprintf(stderr, "ERRO: Filtro Gaussiano nao pode ser aplicada com sucesso! Imagem resultante foi Nula\n");
		freeImagem(GaussImage);
		freeImagem(m);
		return 0;
	}

	//Aqui comeca a recurcao para situacoes em que se usa mais de 1 vez o filtro
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

	//freeImagem(m);
	//Nao dou free aqui, para guardar a imagem cinza para uso posterior
	return GaussImage;
}


//Funcao de aplicacao do filtro de sobel na imagem
//Como extra eu posso controlar a quantidade de aplicacoes
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
	if (!SobelImage) {
		fprintf(stderr, "ERRO: Filtro de sobel nao pode ser aplicada com sucesso! Imagem resultante foi Nula\n");
		freeImagem(SobelImage);
		freeImagem(m);
		return 0;
	}

	//Aqui comeca a recurcao para situacoes em que se usa mais de 1 vez o filtro
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

//Funcao de aplicacao da binarizacao na minha imagem passada por parametro
Imagem *Binarizacao (Imagem *m, int limiar) {
	int i,j;

	Imagem *BinImage = criarImagem(m->altura, m->largura, m->max);
	strcpy(BinImage->header, m->header);

	for (i=0; i < m->altura; i++) {
		for (j=0; j < m->largura; j++) {
			//Para cada pixel, checaremos se ele e maior que o limiar, se sim, igualaremos ao max
			//Se nao, igualaremos a 0
			if (m->M[i][j].r > limiar) {
				BinImage->M[i][j].r = m->max;
				BinImage->M[i][j].g = m->max;
				BinImage->M[i][j].b = m->max;
			}
			else {
				BinImage->M[i][j].r = 0;
				BinImage->M[i][j].g = 0;
				BinImage->M[i][j].b = 0;
			}
		}
	}

	if (!BinImage) {
		fprintf(stderr, "ERRO: Binarizacao nao pode ser aplicada com sucesso! Imagem resultante foi Nula\n");
		freeImagem(BinImage);
		freeImagem(m);
		return 0;
	}

	freeImagem(m);
	return BinImage;
}

//Funcao de aplicacao da Transformada de Hough para a obtencao de centros e raios de possiveis circulos
Centro *Transformada_Hough (Imagem *m) {
    int altura = (int) m->altura;
    int largura = (int) m->largura;
    int r;

    int rmin = fmin(altura,largura)/20;
    int rmin_iris = fmin(altura,largura)/10;
    int rmax = fmin(altura,largura)/4;
 
    int *A = calloc(altura*largura*(rmax-rmin+1),sizeof(int));
    if (A == NULL) {
        fprintf(stderr, "ERR15: Falha em alocacao de matriz tridimencional\n");
        return NULL;
    }
 
    int i,j,x,y;
    int dim = altura*largura;
    int theta;
    for (i=rmax; i < altura-rmax; i++) {
        for (j=rmax; j < largura-rmax; j++) {
            if (m->M[i][j].r == 255) {
                for (r=rmin; r <= rmax; r++) {
                    for (theta=0; theta < 360; theta++) {
                        y = i - r * sin(theta*PI/180.0);
                        x = j + r * cos(theta*PI/180.0);
                        A[(r-rmin)*dim+(y*largura)+x]++;//espaço de Hough
                    }
                }
            }
        }
    }
 
    //Algortimo que identifica valor maximo na matriz de Hough com mais pontos
    unsigned int imax, jmax;
    double max = 0;
    long int icount = 0, jcount = 0, count = 0;
    for (i=rmax; i < altura-rmax; i++) {
        for (j=rmax; j < largura-rmax;j++) {
            for(r=rmin_iris; r <= rmax; r++) {
                max = fmax(A[dim*(r-rmin)+(i*largura)+j], max);
            }
        }
    }
    //Algoritmo para achar centro
    for (i=rmin; i < altura-rmax; i++) {
        for (j=rmin; j < largura-rmax; j++) {
            for (r=rmin_iris; r <= rmax; r++) {
                //As coordenadas serao calculadas a partir de uma media entre elas
                //Devendo ser maior ou igual a 87.5% do valor maximo da matriz (255)
                if (A[dim*(r-rmin)+(i*largura)+j] >= 0.875*max) {
                    count++;
                    icount += i;
                    jcount += j;
                }
            }
        }
    }
    //Calculo da media
    imax = (unsigned int) icount/count;
    jmax = (unsigned int) jcount/count;
 
    Centro *c = malloc(sizeof(Centro));
    if (c == NULL) {
        fprintf(stderr, "ERRO: CENTRO DE PUPILA NAO ALOCADO CORRETAMENTE\n");
    }
 
    //Definindo as coordenadas
    c->x = (int) jmax;
    c->y = (int) imax;
    c->r = 0;
 
    //Algoritmo para achar o raio da pupila
    max = 0;
    int raios[rmax-rmin+1];
    int r_max_diferente;
    int count_raios = 0;
    for (r=rmin; r <= rmax+1; r++) {
        if ((A[dim*(r-rmin)+(imax*largura)+jmax] == 0 && max != 0) || (r == rmax+1)) {
            max = 0;
            raios[count_raios++] = r_max_diferente;
            continue;
        }
        if (A[dim*(r-rmin)+(imax*largura)+jmax] > max) {
            max = A[dim*(r-rmin)+(imax*largura)+jmax];
            r_max_diferente = r;
        }
    }
 
    //Atraves dos raios maximos encontrados, achamos qual raio deve pertencer a pupila
    for (i=0; i < count_raios; i++) {
        if (i == count_raios-1) {
            c->r = raios[i];
        }
        else if (raios[i] > (double) (raios[i+1])/3) {
            c->r = raios[i];
            if (i+1 == count_raios-1) {
                break;
            }
        }
    }

    printf("Coordenada = (%d,%d)\nRaio = %d\n", c->x, c->y, c->r);
    free(A);
    return c;
}
 
//Funcao para segmentacao da pupila do restante da imagem
Imagem *pupila_segmentada (Imagem *m, Centro *c) {
    Imagem *PupImage = criarImagem(m->altura, m->largura, m->max);
    strcpy(PupImage->header, m->header);
 
	//Algoritmo para pegar o circulo com centro no centro da pupila
	int i,j;
	for(i=0; i < m->altura; i++) {
		for(j=0; j < m->largura; j++) {
    		//Caso o pixel pertenca a um circulo de mesmo centro que a pupila
    		//E mesmo raio (tirar 5 pixels para evitar bordas da iris)
    		if (sqrt((i-c->y)*(i-c->y)+(j-c->x)*(j-c->x)) < c->r-5) {
        		PupImage->M[i][j].r = m->M[i][j].r;
        		PupImage->M[i][j].g = m->M[i][j].g;
        		PupImage->M[i][j].b = m->M[i][j].b;
    		}
    		else {
        	PupImage->M[i][j].r = 0;
        	PupImage->M[i][j].g = 0;
        	PupImage->M[i][j].b = 0;
    		}
		}
	}
	if (!PupImage) {
  		fprintf(stderr, "ERROR: Imagem da pupila segmentada saiu Nula\n");
  		freeImagem(PupImage);
  		freeImagem(m);
	}
	
	freeImagem(m);
	return PupImage;
}

//Procedimento para o contorno da pupila em RGB
void marcacao_de_pupila_cor (Imagem *m, Centro *c) {
	unsigned int t;
	int xpos, ypos;
	
	//Percorre a circunferencia de centro igual ao passado por parametro
	for (t = 0; t < 360; t++) {
		//Calcula as coordenadas atraves do raio (incluso na passagem por parametro do Centro)
		ypos = c->r*sin(t*(PI/180.0));
		xpos = c->r*cos(t*(PI/180.0));

		//Marca em magenta as coordenadas no raio
		m->M[c->y+ypos][c->x+xpos].r = 255;
		m->M[c->y+ypos][c->x+xpos].g = 0;
		m->M[c->y+ypos][c->x+xpos].b = 255;
	}
}

//Funcao para obtencao da porcentagem de pixels com catarata
double pixels_comprometidos (Imagem *m, Imagem *img) {
	//A imagem 'm', refere-se a imagem da pupila segmentada
	int i,j;
	int limiar = 150;//Valor obtido empiricamente
	double count_total = 0,count = 0;

	for (i=0; i < m->altura; i++) {
		for (j=(int) (m->largura)/4; j < m->largura; j++) {
			//Para cada pixel, checar se o pixel pertence a pupila, e se sim, se ele esta comprometido ou nao
			//Se o pixel pertencer a pupila, ou seja, 'm' possuir valor diferente de 0
			//Se o pixel nao pertencer ao flash, ou seja, 'img' possuir valor igual a 0
			if ((m->M[i][j].r != 0) && (img->M[i][j].r == 0)) {
				//A imagem 'm', refere-se a imagem da pupila segmentada, logo, um pixel dessa imagem precisa ter valor
				//A imagem 'img', refere-se a imagem do flash segmentado, logo, um pixel dessa imagem nao pode ter valor
				count_total++;//Cada pixel existente na pupila e que tambem não faz parte do flash, ou seja, o total a analisar

				if (m->M[i][j].r > 6*limiar/10) {
					count++;//Cada pixel que corresponde a pixel de catarata
				}
			}
		}
	}
	double porcento = (double) (count*100)/count_total;

	freeImagem(m);
	freeImagem(img);
	return porcento;
}

//Funcao para segmentacao do flash do restante da imagem
Imagem *flash_segmentado (Imagem *m, unsigned short int limiar) {
	Imagem *FlashImage = criarImagem(m->altura, m->largura, m->max);
	strcpy(FlashImage->header, m->header);

	for (unsigned int i=0; i < m->altura; i++) {
		for (unsigned int j=0; j < m->largura; j++) {
			//Analise de cada pixel
			//Caso o pixel possuir valor maior ou igual a um limiar, considera-o como pixel de flash
			//Valor de limiar passado como parametro, e encontrado empiricamente
			if (m->M[i][j].r >= limiar) {
				FlashImage->M[i][j].r = m->M[i][j].r;
				FlashImage->M[i][j].g = m->M[i][j].g;
				FlashImage->M[i][j].b = m->M[i][j].b;
			}
			else {
				FlashImage->M[i][j].r = 0;
				FlashImage->M[i][j].g = 0;
				FlashImage->M[i][j].b = 0;
			}
		}
	}

	return FlashImage;
}
