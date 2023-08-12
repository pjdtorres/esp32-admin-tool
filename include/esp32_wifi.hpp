#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

int wifi_mode = WIFI_STA;

unsigned long previousMillisWIFI = 0;
unsigned long intervalWIFI = 30000;

// hostname for ESPmDNS. Should work at least on windows. Try http://adminesp32.local
const char *esp_hostname = id;

void startAP()
{
    log("Info: Iniciando Modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP " + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}

// -------------------------------------------------------------------
// Start Client, attempt to connect to Wifi network
// -------------------------------------------------------------------
void startClient()
{
    if (wifi_staticIP)
    {
        if (!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS)))
        {
            log("Error: Falhou ao conectar no modo STATION");
        }
    }
    WiFi.hostname(deviceID());
    WiFi.begin(wifi_ssid, wifi_passw);
    log("Info: Conectando WiFi " + String(wifi_ssid));
    delay(50);
    byte b = 0;
    while (WiFi.status() != WL_CONNECTED && b < 4)
    {
        b++;
        log("Warning: Tentando conecção WiFi ... ");
        delay(500);
        // para cintilar o led WIFI quando está a conectar-se ao wifi
        // cintilar simples do Led em cada 100 ms
        blinkSingle(100, WIFILED);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        // WiFi Station conectado
        log("Info: WiFi conectado (" + String(WiFi.RSSI()) + ") IP " + ipStr(WiFi.localIP()));
        // cintilar Ramdom do Led
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    }
    else
    {
        // WiFi Station NÃO conectado
        log("Error: WiFi não conectado");
        // cintilar Ramdom do Led
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    }
}

// WiFi.mode(WIFI_STA)      - station mode: the ESP32 connects to an access point
// WiFi.mode(WIFI_AP)       - access point mode: stations can connect to the ESP32
// WiFi.mode(WIFI_AP_STA)   - access point and a station connected to another access point

void wifi_setup()
{
    WiFi.disconnect();
    // 1) Se está ativo o Modo AP
    if (ap_accessPoint)
    {
        startAP();
        log("Info: WiFI Modo AP");
    }
    // 2) Caso contrario em Modo Cliente
    else
    {
        WiFi.mode(WIFI_STA);
        wifi_mode = WIFI_STA;
        startClient();
        log("Info: WiFI Modo STATION");
    }

    // Iniciar hostname broadcast em modo STA ou AP
    if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP)
    {
        if (MDNS.begin(esp_hostname))
        {
            MDNS.addService("http", "tcp", 80);
        }
    }
}
// -------------------------------------------------------------------
// Loop Modo Cliente
// -------------------------------------------------------------------
void wifiLoop()
{

    unsigned long currentMillis = millis();

    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillisWIFI >= intervalWIFI))
    {
        // para cintilar o led quando está a conectar-se ao wifi
        // cintilar Simple del Led cada 100 ms
        blinkSingle(100, WIFILED);

        WiFi.disconnect();
        WiFi.reconnect();
        previousMillisWIFI = currentMillis;
    }
    else
    {
        // cintilar do led Tempo On e Tempo Off
        blinkSingleAsy(10, 500, WIFILED);
    }
}
// -------------------------------------------------------------------
// Loop Modo AP
// -------------------------------------------------------------------
void wifiAPLoop()
{
    // cintilar do Led com tempo variavel como transferencia de Dados
    blinkRandomSingle(50, 100, WIFILED);
    dnsServer.processNextRequest(); // Captive portal DNS re-direct
}
