#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED
#include <complex>
#include <SDL3/SDL.h>

int es_divergente(std::complex<double> numero);
void imprimir_mandelbrot(SDL_Renderer* renderer,unsigned int resolucion);

#endif // MANDELBROT_H_INCLUDED
