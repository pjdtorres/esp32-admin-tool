// -------------------------------------------------------------------
// Valores por defeito Parametros WIFI
// -------------------------------------------------------------------
void settingResetWiFi()
{
    /* ------------------- GERAL -------------------- */
    strlcpy(id, "adminesp32", sizeof(id));
    bootCount = 0;
    /* ------------------- CLIENTE -------------------- */
    wifi_staticIP = false;
    strlcpy(wifi_ssid, "pjdtorres_2G", sizeof(wifi_ssid));
    strlcpy(wifi_passw, "abelhas2019", sizeof(wifi_passw));
    strlcpy(wifi_ip_static, "192.168.1.220", sizeof(wifi_ip_static));
    strlcpy(wifi_gateway, "192.168.1.1", sizeof(wifi_gateway));
    strlcpy(wifi_subnet, "255.255.255.0", sizeof(wifi_subnet));
    strlcpy(wifi_primaryDNS, "8.8.8.8", sizeof(wifi_primaryDNS));
    strlcpy(wifi_secondaryDNS, "8.8.4.4", sizeof(wifi_secondaryDNS));
    /* ------------------- AP ------------------------- */
    ap_accessPoint = false;
    strlcpy(ap_nameap, deviceID().c_str(), sizeof(ap_nameap));
    strlcpy(ap_passwordap, "adminesp32", sizeof(ap_passwordap));
    ap_canalap = 9;
    ap_hiddenap = false;
    ap_connetap = 4;
}
// -------------------------------------------------------------------
// Valores por defecto Parametros MQTT
// -------------------------------------------------------------------
void settingsResetMQTT()
{
    // Define configuración por defecto del equipo conexión MQTT
    strlcpy(mqtt_user, "cuba_iot", sizeof(mqtt_user));
    strlcpy(mqtt_passw, "cuba_iot", sizeof(mqtt_passw));
    strlcpy(mqtt_server, "cubaelectronica.com", sizeof(mqtt_server));
    strlcpy(mqtt_id, deviceID().c_str(), sizeof(mqtt_id));
    mqtt_time = 60000; // Un Minuto
    mqtt_port = 1883;
    mqtt_enable = true;
}
// -------------------------------------------------------------------
// Valores por defecto Relays
// -------------------------------------------------------------------
void settingsResetRelays()
{
    Relay01_status = LOW;
    Relay02_status = LOW;
}
