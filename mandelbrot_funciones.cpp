#include "mandelbrot.h"
#include <numeric>

//Funcion que calcula el mandelbrot
void imprimir_mandelbrot(SDL_Renderer* renderer,unsigned int resolucion){
    std::complex<double> aux_complejo;
    double real;
    double imaginario;
    unsigned int cantidad_generaciones;

    //Recorro los numeros
    for(real = -2; real < 1; real+= 1.0 / resolucion){
        for(imaginario = -1.5; imaginario < 1.5; imaginario+= 1.0 / resolucion){
            //Armo una variable compleja en la posicion que estoy
            aux_complejo = std::complex<double>(real,imaginario);

            //Calculo la cantidad de generaciones
            cantidad_generaciones = es_divergente(aux_complejo);

            SDL_SetRenderDrawColor(renderer,
                                    cantidad_generaciones,
                                    cantidad_generaciones,
                                    cantidad_generaciones,
                                    255);
            //Dibuja
            SDL_RenderPoint(renderer,
                            (real + 2) * 400,
                            (imaginario + 1.1) * 400);
        }
        SDL_RenderPresent(renderer);
    }

    //Cuando termino, actualizo la pantalla
    SDL_RenderPresent(renderer);
}

// Esta funcion comprueba si un numero complejo diverge antes de alcanzar 255 iteraciones
// Si no diverge, devuelve el numero total de iteraciones realizadas (hasta 255)
int es_divergente(std::complex<double> C) {
    std::complex<double> Z(0, 0);
    int i;

    // Iteraciones
    for (i = 0; i < 255; i++) {
        // Z = (Z ^ 2) + C
        Z = Z * Z + C;

        // Si |Z| > 2, es divergente
        if (std::abs(Z) > 2) {
            return i;  // Devuelve el número de iteraciones hasta que diverge
        }
    }

    // No es divergente, devuelve el número total de iteraciones (255)
    return i;
}

