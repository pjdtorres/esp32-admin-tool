<<<<<<< HEAD
#include <Arduino.h>

void setup()
{
}

void loop()
{
=======
// --------------------------------------------------
// Librerias
// --------------------------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

// --------------------------------------------------
// Archivos *.hpp - Fragmentar el Código
// --------------------------------------------------
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"

// --------------------------------------------------
// Setup
// --------------------------------------------------
void setup() {
    // Baudrate
    Serial.begin(115200);
    // CPU Freq
    setCpuFrequencyMhz(240);
    // Inicio do Log por serial
    log("\nInfo: Iniciando Setup");
    // Configurar los Pines
    settingPinos();
    // Inicio do SPIFFS                 
    if (!SPIFFS.begin()){
        log(F("Error: Falhou a inicialização do SPIFFS"));
        while (true);
    }
    // Ler a Configuração WiFi
    settingsReadWiFi();
    // Configuração WIFI
    WiFi.disconnect(true);
    delay(1000);
    // Setup do WiFI
    wifi_setup(); 
}

// --------------------------------------------------
// Loop Pincipal Nucleo 0
// --------------------------------------------------
void loop() {

    yield();
    // --------------------------------------------------
    // WIFI
    // --------------------------------------------------
    if (wifi_mode == WIFI_STA){
        wifiLoop();
    }else if (wifi_mode == WIFI_AP){
        wifiAPLoop();
    } 

>>>>>>> 69db24fe33141dabfa8e0f9ed85333e6c3ce270c
}