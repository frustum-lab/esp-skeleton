#ifndef CONFIG_H
#define CONFIG_H

// Optional: Load private credentials if secrets.h exists
#if __has_include("secrets.h")
#include "secrets.h"
#endif

// Fallback to empty strings if not defined in secrets.h
#ifndef SECRET_WIFI_SSID
#define SECRET_WIFI_SSID ""
#endif
#ifndef SECRET_WIFI_PASS
#define SECRET_WIFI_PASS ""
#endif

// --- WiFi / Network Defaults ---
constexpr const char* WIFI_DEFAULT_SSID = SECRET_WIFI_SSID;
constexpr const char* WIFI_DEFAULT_PASS = SECRET_WIFI_PASS;
constexpr unsigned long WIFI_TIMEOUT_MS = 30000;
constexpr unsigned int DNS_PORT = 53;

// --- NTP Configuration ---
constexpr const char* NTP_SERVER = "pool.ntp.org";
constexpr unsigned int NTP_PORT = 123;
constexpr unsigned long NTP_TIMEOUT_MS = 1000;

#endif // CONFIG_H
