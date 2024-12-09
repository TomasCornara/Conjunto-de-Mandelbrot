#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED
#include <complex>
#include <SDL3/SDL.h>

int es_divergente(std::complex<double> numero);
void imprimir_mandelbrot(SDL_Renderer* renderer,unsigned int resolucion, bool USAR_PRESETS, int preset,
                         double multiplicador_rojo, double multiplicador_verde, double multiplicador_azul);
void obtener_color(unsigned int iteraciones,
                   unsigned char& r, unsigned char& g, unsigned char& b,
                   double multiplicador_rojo, double multiplicador_verde, double multiplicador_azul);
void cargar_canal(std::string nombre, double& multiplicador,
                  unsigned int& velocidad_cambio_color,
                  unsigned int& velocidad_transicion_color);
void cargar_presets(unsigned int preset,unsigned int cant_interaciones,
                    unsigned char& r, unsigned char& g, unsigned char& b);

#endif // MANDELBROT_H_INCLUDED
