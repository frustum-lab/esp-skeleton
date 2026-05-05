#ifndef LOG_MODULE_H
#define LOG_MODULE_H

#include <LittleFS.h>
#include <Arduino.h>

class TimeModule;

class LogModule {
public:
    LogModule();
    void begin(TimeModule* timeModule, const String& header = "");
    void logRow(const String& dataLine);
    String getLogFilePath();
    void clearLog();

private:
    const char* _logFilePath = "/system_log.csv";
    TimeModule* _timeModule;
    String _header;
    unsigned long _lastLogTime;
    const unsigned long _logInterval = 60000; // 1 minute
    const size_t _maxLogSize = 100 * 1024;    // 100KB
    void writeHeaderIfNeeded();
};

#endif // LOG_MODULE_H
