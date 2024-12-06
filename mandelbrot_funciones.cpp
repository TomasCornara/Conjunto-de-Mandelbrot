#include "mandelbrot.h"
#include <numeric>

int es_divergente(std::complex<double> C) {
    std::complex<double> Z(0,0);
    int i;

    // Iteraciones
    for(i = 0; i < 255; i++)
    {
        // Z = (Z ^ 2) + C
        Z = Z * Z + C;

        // Si |Z| > 2, es divergente
        if(std::abs(Z) > 2){
            return i;
        }
    }

    //No es divergente, devuelve un valor de 0-255
    return i;
}
