// -------------------------------------------------------------------
// Livrarias
// -------------------------------------------------------------------
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

// -------------------------------------------------------------------
// Arquivos *.hpp - Fragmentar o Código
// -------------------------------------------------------------------
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"
// #include "esp32_mqtt.hpp"

// -------------------------------------------------------------------
// Setup
// -------------------------------------------------------------------
void setup()
{
    // Baudrate
    Serial.begin(115200); // igual a monitor_speed = 115200 de platformio.ini
    // CPU Freq
    setCpuFrequencyMhz(240);
    // Inicio del Log por serial
    log("\nInfo: Iniciou Setup");
    // Configurar os Pinos
    settingPinos();
    // Inicio do SPIFFS
    if (!SPIFFS.begin())
    {
        log("Error: Falhou a inicialização do SPIFFS");
        while (true)
            ;
    }
    // Ler os estados dos Relays
    settingsReadRelays();
    // Passa estados aos pinos dos Relays
    setOnOffSingle(RELAY1, Relay01_status);
    setOnOffSingle(RELAY2, Relay02_status);
    // Ler a Configuração WiFi
    settingsReadWiFi();
    // Configuração WIFI
    WiFi.disconnect(true);
    delay(1000);
    // Setup do WiFI
    wifi_setup();
    // // Ler a Configuração MQTT
    // // settingsReadMQTT();
}

// -------------------------------------------------------------------
// Loop Pincipal Nucleo 0
// -------------------------------------------------------------------
void loop()
{

    yield();
    // -------------------------------------------------------------------
    // WIFI
    // -------------------------------------------------------------------
    if (wifi_mode == WIFI_STA)
    {
        wifiLoop();
    }
    else if (wifi_mode == WIFI_AP)
    {
        wifiAPLoop();
    }
    // -------------------------------------------------------------------
    // MQTT
    // -------------------------------------------------------------------
    // if ((WiFi.status() == WL_CONNECTED) && (wifi_mode == WIFI_STA))
    // {
    //     if (mqtt_server != 0)
    //     {
    //         mqttLoop();
    //         if (mqttclient.connected())
    //         {
    //             if (millis() - lastMsg > mqtt_time)
    //             {
    //                 lastMsg = millis();
    //                 mqtt_publish();
    //             }
    //         }
    //     }
    // }
}