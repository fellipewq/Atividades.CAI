#include "Led.h"

led::led(int pin)
{
    pino = pin;
    estadoLed = false;
    pinMode(pino, OUTPUT);
    digitalWrite(pin, LOW);
}

void led::ligar()
{
    estadoLed = true;
    modoPiscar = false;
    digitalWrite(pino, HIGH);
}

void led::desligar()
{
    estadoLed = false;
    modoPiscar = false;
    digitalWrite(pino, LOW);
}

void led::inverter()
{
    estadoLed = !estadoLed;
    digitalWrite(pino, estadoLed);
}

void led::piscar(float frequencia)
{
    if(frequencia == 0) return;
    intervalo = 1000.0/(frequencia * 2);
    ultimaTroca = millis();
    modoPiscar = true;
}

void led::update()
{
    if(!modoPiscar) return;

    unsigned long agora = millis();
    if(agora - ultimaTroca >= intervalo)
    {
        inverter();
        ultimaTroca = agora;
    }
}

int led::getPino()
{
    return pino;
}

unsigned long led::getIntervalo()
{
    return intervalo;
}