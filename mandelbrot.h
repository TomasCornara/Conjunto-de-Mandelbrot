#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED
#include <complex>

int es_divergente(std::complex<double> numero);
std::complex<double> calculo_iteraciones(unsigned int Z, std::complex<double>C);

#endif // MANDELBROT_H_INCLUDED
