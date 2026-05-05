#include "SystemConfig.h"
#include <EEPROM.h>

SystemConfig::SystemConfig() : _ssid(""), _password("") {}

void SystemConfig::begin() {
    EEPROM.begin(SC_EEPROM_SIZE);
    _ssid     = readConfigStr(SC_SSID_ADDR, SC_SSID_LEN);
    _password = readConfigStr(SC_PWD_ADDR,  SC_PWD_LEN);
}

void SystemConfig::writeConfigStr(int addr, int maxLen, const String& val) {
    for (int i = 0; i < maxLen; i++) {
        EEPROM.write(addr + i, (i < (int)val.length()) ? val[i] : 0);
    }
    EEPROM.commit();
}

String SystemConfig::readConfigStr(int addr, int maxLen) {
    String result = "";
    for (int i = 0; i < maxLen; i++) {
        char c = EEPROM.read(addr + i);
        if (c == 0 || (byte)c == 0xFF) break;
        result += c;
    }
    return result;
}

void SystemConfig::saveWiFi(const String& ssid, const String& password) {
    writeConfigStr(SC_SSID_ADDR, SC_SSID_LEN, ssid);
    writeConfigStr(SC_PWD_ADDR,  SC_PWD_LEN,  password);
    _ssid = ssid;
    _password = password;
}
