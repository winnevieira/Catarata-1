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
	//freeImagem(m);
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
	if (!SobelImage) {
		fprintf(stderr, "ERRO: Filtro de sobel nao pode ser aplicada com sucesso! Imagem resultante foi Nula\n");
		freeImagem(SobelImage);
		freeImagem(m);
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
	}

	freeImagem(m);
	return BinImage;
}

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
                //As coordenadas serao uma media das coordenadas, dos pontos na matriz, maiores
                //que ou iguais a 87,5% do valor maximo na matriz
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
 
    //Atraves dos raios maximos encontrados, achamos qual raio pertence a pupila
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
    return c;
}
 
Imagem *pupila_segmentada (Imagem *m, Centro *c) {
    Imagem *PupImage = criarImagem(m->altura, m->largura, m->max);
    strcpy(PupImage->header, m->header);
 
	//Algoritmo para pegar o circulo com centro no centro da pupila
	int i,j;
	for(i=0; i < m->altura; i++) {
		for(j=0; j < m->largura; j++) {
    		//Caso o pixel pertenca a um circulo de mesmo centro que a pupila
    		//e com raio equivalente (5 pixels decrescidos para eliminar bordas da iris)
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
  		fprintf(stderr, "ERROW: Imagem da pupila segmentada saiu Nula\n");
  		freeImagem(PupImage);
  		freeImagem(m);
	}
	
	//freeImagem(m);
	return PupImage;
}

void marcacao_de_pupila_cor (Imagem *m, Centro *c) {
	unsigned int t;
	int xpos, ypos;
	
	//percorre a circunferencia do circulo com centro igual
	//a centro passado por parametro
	for (t = 0; t < 360; t++) {
		//calcula as coordenadas de pontos no raio
		ypos = c->r*sin(t*(PI/180.0));
		xpos = c->r*cos(t*(PI/180.0));

		//marca coordenada no raio de verde
		m->M[c->y+ypos][c->x+xpos].r = 255;
		m->M[c->y+ypos][c->x+xpos].g = 0;
		m->M[c->y+ypos][c->x+xpos].b = 255;
	}
}
