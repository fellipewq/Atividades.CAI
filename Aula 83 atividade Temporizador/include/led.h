#ifndef LED_H
#define LEDH

#include <Arduino.h>

class led 
{
    private://Atributos(Caracteristicas)
        int pino;
        bool estadoLed;
        bool modoPiscar = false;
        unsigned long ultimaTroca = 0;
        unsigned long intervalo = 0;



    public://Metodos(Acoes)
        led(int pin); //*Metodo construtor tem o mesmo nome da classe

        void ligar();
        void desligar();
        void inverter();

        void piscar(float frequencia);
        void update();

        int getPino();
        unsigned long getIntervalo();
};



#endif