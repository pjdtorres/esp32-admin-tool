#include <Arduino.h>

bool ioBlink = false;
unsigned long milOld;
int rndTemp = 0;

// -------------------------------------------------------------------
// Simples função cintilar - cintilar para Alarmes Tempo variavel
// -------------------------------------------------------------------
void blinkSingle(int speed, int _pin)
{
    if ((milOld + speed) < millis())
    {
        milOld = millis();
        if (ioBlink == false)
        {
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else
        {
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }
}
// -------------------------------------------------------------------
// cintilar Assincrono Tempo On, Tempo Off, Tempo variable
// -------------------------------------------------------------------
void blinkSingleAsy(int timeHigh, int timeLow, int _pin)
{
    if (ioBlink == false)
    {
        if ((milOld + timeHigh) < millis())
        {
            milOld = millis();
            digitalWrite(_pin, LOW);
            ioBlink = true;
        }
    }
    else
    {
        if ((milOld + timeLow) < millis())
        {
            milOld = millis();
            digitalWrite(_pin, HIGH);
            ioBlink = false;
        }
    }
}
// -------------------------------------------------------------------
// cintilar com atraso aleatorio (random) como para TX/RX de Dados
// -------------------------------------------------------------------
void blinkRandomSingle(int minTime, int maxTime, int _pin)
{
    if ((milOld + rndTemp) < millis())
    {
        milOld = millis();
        rndTemp = random(minTime, maxTime);
        if (ioBlink == false)
        {
            digitalWrite(_pin, HIGH);
            ioBlink = true;
        }
        else
        {
            digitalWrite(_pin, LOW);
            ioBlink = false;
        }
    }
}
// -------------------------------------------------------------------
// ON Led/Relay/Actuador
// -------------------------------------------------------------------
void setOnSingle(int _pin)
{
    digitalWrite(_pin, HIGH);
}
// -------------------------------------------------------------------
// Off Led/Relay/Actuador
// -------------------------------------------------------------------
void setOffSingle(int _pin)
{
    digitalWrite(_pin, LOW);
}
// -------------------------------------------------------------------
// On/Off Led/Relay/Actuador conforme os Estados
// -------------------------------------------------------------------
void setOnOffSingle(int _pin, bool status)
{
    if (status)
    {
        digitalWrite(_pin, HIGH);
    }
    else
    {
        digitalWrite(_pin, LOW);
    }
}
