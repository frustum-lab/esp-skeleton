#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif
#include <LittleFS.h>

#include "core/SystemConfig.h"
#include "core/CoreWebServer.h"
#include "core/OTAModule.h"
#include "core/log_module.h"
#include "core/TimeModule.h"
#include "../include/config.h"

// --- 基盤モジュール ---
SystemConfig sysConfig;
CoreWebServer webServer;
OTAModule ota;
LogModule logger;
TimeModule timeModule;

// --- アプリケーション状態 (例) ---
float sensorValue = 0.0f;

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\n[System] Starting esp-skeleton...");

    // 1. ファイルシステム
    if (!LittleFS.begin()) {
        Serial.println("[System] LittleFS mount failed");
    }

    // 2. 設定の読み込み
    sysConfig.begin();

    // 3. 時刻同期 (NTP)
    timeModule.begin(9); // JST

    // 4. ロガー (時刻同期モジュールを渡す)
    logger.begin(&timeModule, "Timestamp,Event,Value");
    logger.logRow("System Started,0.0");

    // 5. Wi-Fi 接続フロー
    String ssid = sysConfig.getWifiSSID();
    String pass = sysConfig.getWifiPassword();

    if (ssid.length() == 0) {
        ssid = WIFI_DEFAULT_SSID;
        pass = WIFI_DEFAULT_PASS;
    }

    if (ssid.length() > 0) {
        Serial.printf("[WiFi] Connecting to %s\n", ssid.c_str());
        WiFi.begin(ssid.c_str(), pass.c_str());
        
        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) {
            Serial.print(".");
            delay(500);
        }
        Serial.println();
        
        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf("[WiFi] Connected! IP: %s\n", WiFi.localIP().toString().c_str());
        } else {
            Serial.println("[WiFi] Connection failed. Starting AP Mode...");
            WiFi.mode(WIFI_AP);
            WiFi.softAP("ESP-SKELETON-SETUP");
        }
    } else {
        Serial.println("[WiFi] No credentials. Starting AP Mode...");
        WiFi.mode(WIFI_AP);
        WiFi.softAP("ESP-SKELETON-SETUP");
    }

    // 6. Web サーバー (APIルートの登録)
    bool isAP = (WiFi.getMode() == WIFI_AP || WiFi.getMode() == WIFI_AP_STA);
    
    // --- アプリ固有のAPIルート登録 ---
    webServer.server().on("/api/status", HTTP_GET, []() {
        String json = "{\"status\":\"ok\", \"time\":\"" + timeModule.getFormattedTime() + "\"}";
        webServer.sendJson(200, json);
    });

    webServer.server().on("/api/sensor", HTTP_GET, []() {
        String json = "{\"value\":" + String(sensorValue, 2) + "}";
        webServer.sendJson(200, json);
    });

    webServer.begin(isAP);

    // 7. OTA アップデート
    ota.begin("esp-skeleton");

    Serial.println("[System] Setup complete.");
}

void loop() {
    webServer.handle();
    ota.handle();

    // --- センサー処理などのアプリケーションロジック ---
    static unsigned long lastUpdate = 0;
    if (millis() - lastUpdate > 10000) {
        lastUpdate = millis();
        // ここでセンサーの値を更新したりログを記録したりする
        sensorValue = (float)random(2000, 3000) / 100.0f; 
        logger.logRow("Sensor Update," + String(sensorValue, 2));
    }
}
