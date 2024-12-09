#include <iostream>
#include "mandelbrot.h"
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    ///DECLARACIONES
    SDL_Event evento;
    SDL_Window* ventana = nullptr;
    SDL_Renderer* renderer = nullptr;
    int resolucion;
    unsigned int velocidad_cambio_R, velocidad_transicion_R,
    velocidad_cambio_G, velocidad_transicion_G,
    velocidad_cambio_B, velocidad_transicion_B;
    unsigned int preset_elegido = 0;
    unsigned int ALTO = 900;
    unsigned int ANCHO = 1000;
    bool LISTO = false;
    bool PRESETS = false;
    double multiplicador_R;
    double multiplicador_G;
    double multiplicador_B;
    string respuesta;


    ///PROGRAMA
    //Settings

    //PRECISION
    cout<<"Ingrese la presicion del calculo (Se recomienda de 400 en adelante): ";
    cin>>resolucion;
    while(resolucion <= 0){
        cout<<"Ingrese un valor mayor que 0: ";
        cin>>resolucion;
    }
    system("cls");

    //PRESETS
    cout<<"Quiere usar presets? (SI|NO): ";
    cin >> respuesta;
    //Pasa a mayuscula
    for(char& c: respuesta){
        c = toupper(c);
    }
    while(respuesta != "SI" && respuesta != "NO"){
        cout<<"Respuesta no valida. Responda SI o NO: ";
        cin >> respuesta;
        //Pasa a mayuscula
        for(char& c: respuesta){
            c = toupper(c);
        }
    }
    PRESETS = (respuesta == "SI")? true:false;

    //Si se quieren presets, se debe pedir cual
    if(PRESETS){
        cout << "Ingrese el preset:\n";
        cout << "1- Blanco y Negro.\n";
        cout << "2- Rojo.\n";
        cout << "3- Verde.\n";
        cout << "4- Azul.\n";
        cout << "5- Azul profundo.\n";
        cout << "6- Psicodelico.\n";
        cout << "7- Azul Electrico.\n";
        cout << "8- Violeta Electrico.\n";
        cout << "9- Verde.\n";
        cout << "10- Fuxia.\n";
        cout << "11- Spark.\n";
        cout << "12- Colorido.\n";
        cout << "13- Circo.\n";
        cin>>preset_elegido;
        while(preset_elegido > 13 || preset_elegido < 1){
            cout<< "Ingrese un numero entre 1 y 13: ";
            cin>>preset_elegido;
        }
    }
    system("cls");

    //Si no se quieren, se tienen que cargar los canales
    if(!PRESETS){
        //Cargar canales de color
        cargar_canal("Rojo",multiplicador_R,velocidad_cambio_R,velocidad_transicion_R);
        cargar_canal("Verde",multiplicador_G,velocidad_cambio_G,velocidad_transicion_G);
        cargar_canal("Azul",multiplicador_B,velocidad_cambio_B,velocidad_transicion_B);
    }

    /*
    //Solo para testing
    resolucion = 400;
    PRESETS = true;
    preset_elegido = 5;*/

    cout<<"Procesando..\n";
    //Inicio de la ventana
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Mandelbrot Set.",
                                ANCHO,
                                ALTO,
                                0,
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
    imprimir_mandelbrot(renderer,resolucion,PRESETS,preset_elegido,multiplicador_R,multiplicador_G,multiplicador_B);
    system("cls");
    cout<<"Cierre o Precione ESC dentro de la nueva ventana para cerrar el programa.\n";
    //Entro en un bucle para esperar que el usuario use el ESC
    while(!LISTO)
    {
        //Verificacion de eventos
        while(SDL_PollEvent(&evento))
        {
            //Evento Boton de salida
            if(evento.type == SDL_EVENT_QUIT) LISTO = true;

            //Evento Presion teclas
            if(evento.type == SDL_EVENT_KEY_DOWN)
            {
                switch(evento.key.key)
                {
                case SDLK_ESCAPE:
                    cout << "ESC.\n";
                    LISTO = true;
                    break;
                }
            }
        }
        // Actualiza la pantalla
        SDL_Delay(100);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);

    return 0;
}
