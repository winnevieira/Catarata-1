#ifndef Importa_h
#define Importa_h

#include "uteis.h"

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
//void marcacao_de_pupila_cor (Imagem *m, Centro *c);

#endif
