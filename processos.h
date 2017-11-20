#ifndef Importa_h
#define Importa_h

#include "uteis.h"

Imagem* make_PPM_cinza (Imagem *m);

Imagem *GaussFilter (Imagem *m, int blurtimes);

Imagem *SobelFilter (Imagem *m, int limite);

Imagem *Binarizacao (Imagem *m, int limiar);

#endif
