// --------------------------------------------------
// Ler configurações dos Parametros WIFI
// --------------------------------------------------
boolean settingsReadWiFi(){
    StaticJsonDocument<500> jsonConfig;
    File file = SPIFFS.open("/settingwifi.json", "r");
    if(deserializeJson(jsonConfig, file)){
        // Se falha a leitura inicia valores por defeito
        settingResetWiFi();
        log("Error: Falhou a lectura da configuração WiFi, tomando valores por defeito");
        return false;
    }else{
        /* ------------------- GERAL -------------------- */
        strlcpy(id, jsonConfig["id"], sizeof(id)); 
        bootCount = jsonConfig["boot"];
        /* ------------------- CLIENTE ------------------ */
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
        log("Info: Leitura configuração WiFi correta");
        return true;
    }

}