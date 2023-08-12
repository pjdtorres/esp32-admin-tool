// -------------------------------------------------------------------
// Definições
// -------------------------------------------------------------------
#define RELAY1 27  // GPIO27 para salida de Relay 1
#define RELAY2 26  // GPIO26 para salida de Relay 2
#define WIFILED 12 // GPIO12 LED INDICADOR WIFI
#define MQTTLED 13 // GPIO13 LED INDICADOR MQTT
// -------------------------------------------------------------------
// Versão do Hardware
// -------------------------------------------------------------------
#define HW "ADMINESP32 v1 00000000" // Versão do Hardware
// -------------------------------------------------------------------
// Zona Configuração Geral
// -------------------------------------------------------------------
char id[30];   // ID do dispositivo
int bootCount; // Número de reinicios
// -------------------------------------------------------------------
// Zona WIFI
// -------------------------------------------------------------------
bool wifi_staticIP;         // Uso de IP Estática
char wifi_ssid[30];         // Rede WiFi
char wifi_passw[30];        // Password da Red WiFi
char wifi_ip_static[15];    // IP Estático
char wifi_gateway[15];      // Gateway
char wifi_subnet[15];       // Subrede
char wifi_primaryDNS[15];   // DNS primario
char wifi_secondaryDNS[15]; // DNS secundario
// -------------------------------------------------------------------
// Zona AP
// -------------------------------------------------------------------
bool ap_accessPoint;    // Uso de Modo AP
char ap_nameap[31];     // SSID AP
char ap_passwordap[63]; // Password AP
int ap_canalap;         // Canal AP
int ap_hiddenap;        // Visivel ou não o AP  (0 - Visivel  1 - Oculto)
int ap_connetap;        // Número de conecções no AP
// -------------------------------------------------------------------
// Zona configuração MQTT
// -------------------------------------------------------------------
bool mqtt_enable;     // Habilitar MQTT Broker
char mqtt_user[30];   // Usuario MQTT Broker
char mqtt_id[30];     // ID MQTT Broker
char mqtt_passw[30];  // Password MQTT Broker
char mqtt_server[39]; // Servidor del MQTT Broker
int mqtt_port;        // Porto servidor MQTT Broker
int mqtt_time;        // Tempo de envio por MQTT
// -------------------------------------------------------------------
// Zona Outras
// -------------------------------------------------------------------
uint8_t ip[4];  // Variavel função converter string a IP
float temp_cpu; // Temperatura do CPU em °C
// -------------------------------------------------------------------
// Zona Relays
// -------------------------------------------------------------------
bool Relay01_status, Relay02_status; // Estados de los Relay de Salida
