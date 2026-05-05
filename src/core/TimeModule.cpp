#include "TimeModule.h"

TimeModule::TimeModule() : _timezone(9) {}

void TimeModule::begin(int timezone) {
    _timezone = timezone;
    // NTPサーバーの設定 (config.h の定数を使用するのが望ましいですが、ここでは一般的なサーバーを指定)
    configTime(_timezone * 3600, 0, "ntp.nict.jp", "time.google.com", "pool.ntp.org");
    Serial.println("[TimeModule] NTP sync started");
}

String TimeModule::getFormattedTime() {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    // 2000年以前の場合は未同期と判断
    if (timeinfo->tm_year < 100) {
        return "Not synchronized";
    }
    
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    return String(buf);
}

unsigned long TimeModule::getTimestamp() {
    return (unsigned long)time(nullptr);
}
