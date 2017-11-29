#ifndef Importa_h
#define Importa_h

#include "uteis.h"

//Definicao do valor de pi
#define PI 3.141592

//Funcao de criacao da minha imagem entrada em tons de cinza
Imagem *make_PPM_cinza (Imagem *m);

//Funcao de aplicacao do filtro de gauss na minha imagem passada por parametro
Imagem *GaussFilter (Imagem *m, int blurtimes);

//Funcao de aplicacao do filtro de sobel na minha imagem passada por parametro
Imagem *SobelFilter (Imagem *m, int limite);

//Funcao de aplicacao da binarizacao na minha imagem passada por parametro
Imagem *Binarizacao (Imagem *m, int limiar);

//Funcao de aplicacao da Transformada de Hough para a obtencao de centros e raios de possiveis circulos
Centro *Transformada_Hough (Imagem *m);

//Funcao para segmentacao da pupila do restante da imagem
Imagem *pupila_segmentada (Imagem *m, Centro *c);

//Procedimento para o contorno da pupila em RGB
void marcacao_de_pupila_cor (Imagem *m, Centro *c);

//Funcao para porcentagem de pixels com catarata
double pixels_comprometidos (Imagem *m, Imagem *img);

//Funcao para segmentacao do flash do restante da imagem
Imagem *flash_segmentado (Imagem *m, unsigned short int limiar);

#endif
