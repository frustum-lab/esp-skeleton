#ifndef TIME_MODULE_H
#define TIME_MODULE_H

#include <Arduino.h>
#include <WiFiUdp.h>
#include <time.h>

/**
 * TimeModule - NTPによる時刻同期と管理
 */
class TimeModule {
public:
    TimeModule();
    
    // timezone: JSTなら 9
    void begin(int timezone = 9);
    
    // 現在時刻を YYYY-MM-DD HH:MM:SS 形式で取得
    String getFormattedTime();
    
    // UNIXタイムスタンプを取得
    unsigned long getTimestamp();

private:
    int _timezone;
};

#endif
