#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include <Arduino.h>

// EEPROM address map - Core area (0-95)
#define SC_EEPROM_SIZE   1024
#define SC_SSID_ADDR     0
#define SC_SSID_LEN      32
#define SC_PWD_ADDR      32
#define SC_PWD_LEN       64

// Application area (96-1023)
#define SC_APP_ADDR      96

class SystemConfig {
public:
    SystemConfig();
    void begin();
    void saveWiFi(const String& ssid, const String& password);
    
    String getWifiSSID() const { return _ssid; }
    String getWifiPassword() const { return _password; }

    // アプリケーション固有設定用の汎用メソッド
    void writeConfigStr(int addr, int maxLen, const String& val);
    String readConfigStr(int addr, int maxLen);

private:
    String _ssid;
    String _password;
};

#endif
