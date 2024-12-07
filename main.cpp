#include <iostream>
#include "mandelbrot.h"

using namespace std;

int main(int argc, char* argv[])
{
    ///DECLARACIONES
    unsigned int ALTO = 900;
    unsigned int ANCHO = 1000;
    bool listo = false;
    SDL_Event evento;
    SDL_Window* ventana = nullptr;
    SDL_Renderer* renderer = nullptr;
    int resolucion;


    ///PROGRAMA
    //Settings
    cout<<"Ingrese la presicion del calculo (Se recomienda de 400 en adelante): ";
    cin>>resolucion;
    while(resolucion <= 0){
        cout<<"Ingrese un valor mayor que 0: ";
        cin>>resolucion;
    }
    cout<<"Procesando..\n";

    //Inicio de la ventana
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Mandelbrot Set.",
                                ANCHO,
                                ALTO,
                                SDL_WINDOW_BORDERLESS,
                                &ventana,
                                &renderer);

    //Carga y coloca el icono
    auto icono = SDL_LoadBMP("icono.bmp");
    if(!icono){
        cout<<"Error al cargar el icono: "<<SDL_GetError();
    } else {
        SDL_SetWindowIcon(ventana,icono);
        SDL_DestroySurface(icono);
    }

    //Limpio la pantalla pintandola de negro
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


    //Calculo el mandelbrot dentro del renderer
    imprimir_mandelbrot(renderer,resolucion);

    cout<<"Precione ESC dentro de la nueva ventana para cerrar el programa.";
    //Entro en un bucle para esperar que el usuario use el ESC
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
        SDL_Delay(100);
    }

    return 0;
}
