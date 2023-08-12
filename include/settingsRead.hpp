// -------------------------------------------------------------------
// Leer configuraciones de los Parametros WIFI
// -------------------------------------------------------------------
bool settingsReadWiFi()
{
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/settingwifi.json", "r");
    if (deserializeJson(jsonConfig, file))
    {
        // Se falha a leitura inicia valores por defeito
        settingResetWiFi();
        log("Error: Falha na leitura da configuração WiFi, tomando valores por defeito!");
        return false;
    }
    else
    {
        /* ------------------- GERAL ---------------------- */
        strlcpy(id, jsonConfig["id"], sizeof(id));
        bootCount = jsonConfig["boot"];
        /* ------------------- CLIENTE -------------------- */
        wifi_staticIP = jsonConfig["wifi_staticIP"];
        strlcpy(wifi_ssid, jsonConfig["wifi_ssid"], sizeof(wifi_ssid));
        strlcpy(wifi_passw, jsonConfig["wifi_passw"], sizeof(wifi_passw));
        strlcpy(wifi_ip_static, jsonConfig["wifi_ip_static"], sizeof(wifi_ip_static));
        strlcpy(wifi_gateway, jsonConfig["wifi_gateway"], sizeof(wifi_gateway));
        strlcpy(wifi_subnet, jsonConfig["wifi_subnet"], sizeof(wifi_subnet));
        strlcpy(wifi_primaryDNS, jsonConfig["wifi_primaryDNS"], sizeof(wifi_primaryDNS));
        strlcpy(wifi_secondaryDNS, jsonConfig["wifi_secondaryDNS"], sizeof(wifi_secondaryDNS));
        /* ------------------- AP ------------------------ */
        ap_accessPoint = jsonConfig["ap_accessPoint"];
        strlcpy(ap_nameap, jsonConfig["ap_nameap"], sizeof(ap_nameap));
        strlcpy(ap_passwordap, jsonConfig["ap_passwordap"], sizeof(ap_passwordap));
        ap_canalap = jsonConfig["ap_canalap"];
        ap_hiddenap = jsonConfig["ap_hiddenap"];
        ap_connetap = jsonConfig["ap_connetap"];
        file.close();
        log("Info: Leitura de configuração WiFi correcta");
        return true;
    }
}
// -------------------------------------------------------------------
// Leer configurações dos Parametros MQTT
// -------------------------------------------------------------------
boolean settingsReadMQTT()
{
    // Lee la configuración MQTT
    StaticJsonDocument<500> jsonConfig;

    File file = SPIFFS.open(F("/settingmqtt.json"), "r");
    if (deserializeJson(jsonConfig, file))
    {
        // Si falla la lectura asume valores por defecto
        settingsResetMQTT();
        log(F("Error: Falló la lectura de la configuración MQTT, tomando valores por defecto"));
        return false;
    }
    else
    {
        // Si lee el archivo
        strlcpy(mqtt_user, jsonConfig["mqtt_user"], sizeof(mqtt_user));
        strlcpy(mqtt_passw, jsonConfig["mqtt_passw"], sizeof(mqtt_passw));
        strlcpy(mqtt_server, jsonConfig["mqtt_server"], sizeof(mqtt_server));
        strlcpy(mqtt_id, jsonConfig["mqtt_id"], sizeof(mqtt_id));
        mqtt_time = jsonConfig["mqtt_time"];
        mqtt_port = jsonConfig["mqtt_port"];
        mqtt_enable = jsonConfig["mqtt_enable"];
        file.close();
        log(F("Info: Lectura de configuración MQTT correta"));
        return true;
    }
}
// -------------------------------------------------------------------
// Ler estados dos Relays
// -------------------------------------------------------------------
bool settingsReadRelays()
{
    StaticJsonDocument<200> jsonConfig;
    File file = SPIFFS.open("/settingrelays.json", "r");
    if (deserializeJson(jsonConfig, file))
    {
        // Si falla la lectura inicia valores por defecto
        settingsResetRelays();
        log("Error: Falha na leitura do estado dos Relays, tomando valores por defeito!");
        return false;
    }
    else
    {
        Relay01_status = jsonConfig["Relay01_status"];
        Relay02_status = jsonConfig["Relay02_status"];
        file.close();
        log("Info: Leitura dos Relays correta");
        return true;
    }
}