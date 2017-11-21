#ifndef Importa_h
#define Importa_h

#include "uteis.h"

#define PI 3.1415926535

Imagem* make_PPM_cinza (Imagem *m);

Imagem *GaussFilter (Imagem *m, int blurtimes);

Imagem *SobelFilter (Imagem *m, int limite);

Imagem *Binarizacao (Imagem *m, int limiar);

Centro *Transformada_Hough (Imagem *m);

#endif
