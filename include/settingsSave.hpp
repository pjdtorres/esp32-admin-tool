// -------------------------------------------------------------------
// Guardar los estados de los Relays
// -------------------------------------------------------------------
boolean settingsSaveRelays()
{
    // Guarda configuración de los Relays
    StaticJsonDocument<200> jsonConfig;
    File file = SPIFFS.open(F("/settingrelays.json"), "w+");
    if (file)
    {
        jsonConfig["Relay01_status"] = Relay01_status;
        jsonConfig["Relay02_status"] = Relay02_status;
        serializeJsonPretty(jsonConfig, file);
        file.close();
        log(F("Info: Estado dos Relays gravado"));
        serializeJsonPretty(jsonConfig, Serial);
        return true;
    }
    else
    {
        log(F("Error: Falhou a gravação do estado dos Relay"));
        return false;
    }
}
