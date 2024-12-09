#include "mandelbrot.h"
#include <numeric>
#include <iostream>
#include <cstdlib>

//Funcion que calcula el mandelbrot
void imprimir_mandelbrot(SDL_Renderer* renderer,unsigned int resolucion, bool USAR_PRESETS, int preset,
                         double multiplicador_rojo, double multiplicador_verde, double multiplicador_azul){

    std::complex<double> aux_complejo;
    double real;
    double imaginario;
    unsigned int cantidad_generaciones;
    unsigned char r, g, b;

    //Recorro los numeros
    for(real = -2; real < 1; real+= 1.0 / resolucion){
        for(imaginario = -1.5; imaginario < 1.5; imaginario+= 1.0 / resolucion){
            //Armo una variable compleja en la posicion que estoy
            aux_complejo = std::complex<double>(real,imaginario);

            //Calculo la cantidad de generaciones
            cantidad_generaciones = es_divergente(aux_complejo);

            // Obtiene el color basado en las iteraciones
            if(!USAR_PRESETS){
                obtener_color(cantidad_generaciones, r, g, b,
                    multiplicador_rojo,multiplicador_verde,multiplicador_azul);
            } else {
                cargar_presets(preset,cantidad_generaciones,r,g,b);
            }

            SDL_SetRenderDrawColor(renderer,
                                    r,
                                    g,
                                    b,
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

    // No es divergente
    return 0;
}

//Calcula la paleta de colores usando un degrado
void obtener_color(unsigned int iteraciones,
                   unsigned char& r, unsigned char& g, unsigned char& b,
                   double multiplicador_rojo, double multiplicador_verde, double multiplicador_azul) {
    double t = (double)iteraciones / 255.0;

    //Formula de degradado
    r = (unsigned char)(multiplicador_rojo  * pow(1-t, 1) * pow(t,4) * 255); // Rojo
    g = (unsigned char)(multiplicador_verde * pow(1-t, 2) * pow(t,2) * 255); // Verde
    b = (unsigned char)(multiplicador_azul  * pow(1-t, 3) * pow(t,1) * 255); // Azul
}

void cargar_presets(unsigned int preset,unsigned int cant_interaciones,
                    unsigned char& r, unsigned char& g, unsigned char& b){
    //Blanco y negro
    if(preset == 1){
        r = cant_interaciones;
        g = cant_interaciones;
        b = cant_interaciones;
    }

    //Rojo
    if(preset == 2){
        r = cant_interaciones;
        g = 0;
        b = 0;
    }

    //Verde
    if(preset == 3){
        r = 0;
        g = cant_interaciones;
        b = 0;
    }

    //Azul
    if(preset == 4){
        r = 0;
        g = 0;
        b = cant_interaciones;
    }

    //Azul profundo
    if(preset == 5){
        double t = (double)cant_interaciones / 150.0;
        // Ajuste para obtener un color cálido y cremoso
        r = (unsigned char)(10 * pow(1-t, 3) * pow(t, 2) * 255);  // Rojo
        g = (unsigned char)(8 * pow(1-t, 2) * pow(t, 2) * 255);   // Verde
        b = (unsigned char)(3 * pow(1-t, 1) * pow(t, 0) * 255);   // Azul
    }


    //Psicodelico.
    if(preset == 6){
        double t = (double)cant_interaciones / 255.0;

        r = 227 / t;
        g = 208/ t;
        b = 188 / t;
    }

    //Azul electrico.
    if(preset == 7){
        double t = (double)cant_interaciones / 255.0;
        r = (unsigned char)(9  * pow(1-t, 1) * pow(t,4) * 255); // Rojo
        g = (unsigned char)(15 * pow(1-t, 2) * pow(t,2) * 255); // Verde
        b = (unsigned char)(8.5  * pow(1-t, 3) * pow(t,1) * 255); // Azul
    }

    //Violeta Electrico.
    if(preset == 8){
        double t = (double)cant_interaciones / 255.0;
        r = (unsigned char)(9  * pow(1-t, 1) * pow(t,2) * 255); // Rojo
        g = (unsigned char)(15 * pow(1-t, 2) * pow(t,3) * 255); // Verde
        b = (unsigned char)(8.5  * pow(1-t, 3) * pow(t,1) * 255); // Azul
    }

    //Verde.
    if(preset == 9){
        double t = (double)cant_interaciones / 255.0;
        r = (unsigned char)(9  * pow(1-t, 2) * pow(t,2) * 255); // Rojo
        g = (unsigned char)(15 * pow(1-t, 2) * pow(t,2) * 255); // Verde
        b = (unsigned char)(8.5  * pow(1-t, 2) * pow(t,2) * 255); // Azul
    }

    //Fuxia.
    if(preset == 10){
        double t = (double)cant_interaciones / 255.0;
        r = (unsigned char)(20  * pow(1-t,1) * pow(t,1) * 255); // Rojo
        g = (unsigned char)(10 * pow(1-t, 1) * pow(t,2) * 255); // Verde
        b = (unsigned char)(20  * pow(1-t, 1) * pow(t,1) * 255); // Azul
    }

    //Spark.
    if(preset == 11){
        double t = (double)cant_interaciones / 255.0;
        r = (unsigned char)2.27 * (20  * pow(1-t,2) * pow(t,2) * 255); // Rojo
        g = (unsigned char)2.08 * (10 * pow(1-t, 3) * pow(t,3) * 255); // Verde
        b = (unsigned char)1.88* (20  * pow(1-t, 1) * pow(t,1) * 255); // Azul
    }

    //Colorido
    if(preset == 12){
        double t = (double)cant_interaciones / 150.0;
        r = (unsigned char)2.27 * (20  * pow(1-t,0) * pow(t,1) * 255); // Rojo
        g = (unsigned char)2.08 * (10 * pow(1-t, 1) * pow(t,1) * 255); // Verde
        b = (unsigned char)1.88* (20  * pow(1-t, 0) * pow(t,0) * 255); // Azul
    }

    //Circo
    if(preset == 13){
        double t = (double)cant_interaciones / 150.0;
        r = (unsigned char)100 * (20  * pow(1-t,0) * pow(t,1) * 255); // Rojo
        g = (unsigned char)10 * (10 * pow(1-t, 1) * pow(t,3) * 255); // Verde
        b = (unsigned char)100* (20  * pow(1-t, 0) * pow(t,0) * 255); // Azul
    }
}

void cargar_canal(std::string nombre, double& multiplicador,
                  unsigned int& velocidad_cambio_color,
                  unsigned int& velocidad_transicion_color)
{
    system("cls");
    // Multiplicador
    std::cout << "Ingrese un multiplicador del canal " << nombre << " [0 - 20]: ";
    std::cin >> multiplicador;
    while (multiplicador > 20 || multiplicador < 0) {
        std::cout << "Ingrese un valor entre 0 y 20: ";
        std::cin >> multiplicador;
    }
    system("cls");

    // Velocidad de cambio de color
    std::cout << "Ingrese la velocidad de cambio de un color a otro [0 - 3]: ";
    std::cin >> velocidad_cambio_color;
    while (velocidad_cambio_color > 3 || velocidad_cambio_color < 0) {
        std::cout << "Ingrese un valor entre 0 y 3: ";
        std::cin >> velocidad_cambio_color;
    }
    system("cls");

    // Velocidad de transición de tonos
    std::cout << "Ingrese la velocidad de transicion de tonos en el mismo color [0 - 3]: ";
    std::cin >> velocidad_transicion_color;
    while (velocidad_transicion_color > 3 || velocidad_transicion_color < 0) {
        std::cout << "Ingrese un valor entre 0 y 3: ";
        std::cin >> velocidad_transicion_color;
    }
    system("cls");
}

