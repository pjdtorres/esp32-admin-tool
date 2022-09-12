#include "LedBlink.hpp"

// --------------------------------------------------
// Gera um log no porto Serie
// --------------------------------------------------
void log(String s){
    Serial.println(s);
}
// --------------------------------------------------
// Definir la Plataforma
// --------------------------------------------------
String platform(){
// Optiene la plataforma de hardware
#ifdef ARDUINO_ESP32_DEV
    return "ESP32";
#endif
}
// --------------------------------------------------
// Converte un char a IP
// --------------------------------------------------
IPAddress CharToIP(const char *str){
    sscanf(str, "%hhu.%hhu.%hhu.%hhu", &ip[0], &ip[1], &ip[2], &ip[3]);
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
}

// --------------------------------------------------
// Retorna IPAddress en formato "n.n.n.n" de IP a String
// --------------------------------------------------
String ipStr(const IPAddress &ip){    
    String sFn = "";
    for (byte bFn = 0; bFn < 3; bFn++)
    {
        sFn += String((ip >> (8 * bFn)) & 0xFF) + ".";
    }
    sFn += String(((ip >> 8 * 3)) & 0xFF);
    return sFn;
}

// --------------------------------------------------
// Converter HEX para String
// --------------------------------------------------
String hexStr(const unsigned long &h, const byte &l = 8){
    String s;
    s = String(h, HEX);
    s.toUpperCase();
    s = ("00000000" + s).substring(s.length() + 8 - l);
    return s;
}
// --------------------------------------------------
// Crear un ID unico desde la direccion MAC
// --------------------------------------------------
String idUnique(){
    // Retorna los ultimos 4 Bytes del MAC rotados
    char idunique[15]; 
    uint64_t chipid = ESP.getEfuseMac();           
    uint16_t chip = (uint16_t)(chipid >> 32);
    snprintf(idunique, 15, "%04X", chip);
    return idunique;
}
// --------------------------------------------------
// ID del Dispositivo para La Base de Datos
// --------------------------------------------------
String deviceID(){
    return String(platform()) + hexStr(ESP.getEfuseMac()) + String(idUnique());
}

// --------------------------------------------------
// Configurar os Pinos de Saida
// --------------------------------------------------
void settingPinos(){
    // Pinos de Saida
    pinMode(WIFILED, OUTPUT);
    pinMode(MQTTLED, OUTPUT);
    pinMode(RELAY1, OUTPUT);  
    pinMode(RELAY2, OUTPUT);  

    // Reiniciar en nivel LOW            
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);    
    digitalWrite(MQTTLED, LOW);    
    digitalWrite(WIFILED, LOW);
}
