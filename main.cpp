#include <iostream>
#include <SDL3/SDL.h>
#include "mandelbrot.h"

using namespace std;

int main(int argc, char* argv[])
{
    ///DECLARACIONES
    unsigned int ALTO = 900;
    unsigned int ANCHO = 1600;
    bool listo = false;
    SDL_Event evento;
    SDL_Window* ventana = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::complex<double> aux_complejo;
    double real;
    double imaginario;
    int cantidad_generaciones;
    int resolucion = 1000;


    ///PROGRAMA
    //Inicio de la ventana
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Mandelbrot Set.",ANCHO,ALTO,0,&ventana,&renderer);

    //Limpio la pantalla pintandola de negro
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    //Recorro los numeros
    for(real = -2; real < 1; real+= 1.0 / resolucion){
        for(imaginario = -1.5; imaginario < 1.5; imaginario+= 1.0 / resolucion){
            //Declaro una variable compleja en la posicion que estoy
            //La corrijo al real y al imaginario por el tamanno de la pantalla
            //Y al real una vez mas por el rango de interes (De - 2 a 1)
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
                            (real + 3) * 400,
                            (imaginario + 1.1) * 400);
        }
        SDL_RenderPresent(renderer);
    }

    //Cuando termino, actualizo la pantalla
    SDL_RenderPresent(renderer);

    while(!listo)
    {
        //Verificacion de eventos
        while(SDL_PollEvent(&evento))
        {
            //Evento Boton de salida
            if(evento.type == SDL_EVENT_QUIT) listo = true;

            //Evento Presion teclas
            if(evento.type == SDL_EVENT_KEY_DOWN)
            {
                switch(evento.key.key)
                {
                case SDLK_ESCAPE:
                    cout << "ESC.\n";
                    listo = true;
                    break;
                }
            }
        }
        // Actualiza la pantalla
        //SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    return 0;
}
