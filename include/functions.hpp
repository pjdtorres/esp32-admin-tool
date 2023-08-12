#include "LedBlink.hpp"

// -------------------------------------------------------------------
// Sensor Temp Interno CPU
// -------------------------------------------------------------------
#ifdef __cplusplus
extern "C"
{
#endif
    uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

// -------------------------------------------------------------------
// Gera um log no porto Serie
// -------------------------------------------------------------------
void log(String s)
{
    Serial.println(s);
}
// -------------------------------------------------------------------
// Definir a Plataforma
// -------------------------------------------------------------------
String platform()
{
// Obter a plataforma de hardware
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}
// -------------------------------------------------------------------
// Converte um char em IP
// -------------------------------------------------------------------
IPAddress CharToIP(const char *str)
{
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}
// -------------------------------------------------------------------
// Retorna IPAddress em formato "n.n.n.n" de IP para String
// -------------------------------------------------------------------
String ipStr(const IPAddress &ip)
{
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}
// -------------------------------------------------------------------
// De HEX para String
// -------------------------------------------------------------------
String hexStr(const unsigned long &h, const byte &l = 8)
{
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}
// -------------------------------------------------------------------
// Criar um ID unico com a direção MAC
// -------------------------------------------------------------------
String idUnique()
{
    // Retorna os ultimos 4 Bytes do MAC rodados
    char idunique[15];
    uint64_t chipid = ESP.getEfuseMac();
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}
// -------------------------------------------------------------------
// ID do Dispositivo para a Base de Dados
// -------------------------------------------------------------------
String deviceID()
{
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}
// -------------------------------------------------------------------
// Configurar os Pinos de Saida
// -------------------------------------------------------------------
void settingPinos()
{
    // Pinos de Saida
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    // Iniciamos o nivel LOW
    setOffSingle(RELAY1);
    setOffSingle(RELAY2);
    setOffSingle(WIFILED);
    setOffSingle(MQTTLED);
}
// -------------------------------------------------------------------
// Cintilação do LED MQTT de Transmissão
// -------------------------------------------------------------------
void mqttTX()
{
    for (int i = 0; i < 2; i++)
    {
        setOnSingle(MQTTLED);
        delay(50);
        setOffSingle(MQTTLED);
        delay(10);
    }
}
// -------------------------------------------------------------------
// Cintilação do LED MQTT de Receção
// -------------------------------------------------------------------
void mqttRX()
{
    for (int i = 0; i < 1; i++)
    {
        blinkRandomSingle(5, 50, MQTTLED);
        delay(5);
    }
}
// -------------------------------------------------------------------
// Retorna la qualidad de sinal WIFI en %
// -------------------------------------------------------------------
int getRSSIasQuality(int RSSI)
{
    int quality = 0;
    if (RSSI <= -100)
    {
        quality = 0;
    }
    else if (RSSI >= -50)
    {
        quality = 100;
    }
    else
    {
        quality = 2 * (RSSI + 100);
    }
    return quality;
}
// -------------------------------------------------------------------
// Retorna a temperatura do CPU
// -------------------------------------------------------------------
float TempCPUValue()
{
    return temp_cpu = (temprature_sens_read() - 32) / 1.8;
}