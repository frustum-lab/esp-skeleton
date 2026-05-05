#include "log_module.h"
#include "TimeModule.h"
#include <LittleFS.h>

LogModule::LogModule() : _timeModule(nullptr), _lastLogTime(0) {}

void LogModule::begin(TimeModule* timeModule, const String& header) {
    _timeModule = timeModule;
    _header = header;
    if (!LittleFS.begin()) {
        Serial.println("[ERROR] LogModule: LittleFS Mount Failed!");
        return;
    }
    writeHeaderIfNeeded();
}

void LogModule::writeHeaderIfNeeded() {
    if (_header.length() == 0) return;
    
    File logFile = LittleFS.open(_logFilePath, "r");
    if (!logFile || logFile.size() == 0) {
        if (logFile) logFile.close();
        logFile = LittleFS.open(_logFilePath, "w");
        if (logFile) {
            logFile.println(_header);
            logFile.close();
            Serial.println("[INFO] LogModule: Log file header written.");
        }
    } else {
        logFile.close();
    }
}

void LogModule::logRow(const String& dataLine) {
    if (millis() - _lastLogTime < _logInterval) {
        return;
    }
    _lastLogTime = millis();

    File logFile = LittleFS.open(_logFilePath, "a");
    if (logFile) {
        if (logFile.size() >= _maxLogSize) {
            logFile.close();
            clearLog();
            logFile = LittleFS.open(_logFilePath, "a");
            if (!logFile) return;
        }

        String timestamp = _timeModule ? _timeModule->getFormattedTime() : String(millis());
        logFile.println(timestamp + "," + dataLine);
        logFile.close();
    }
}

String LogModule::getLogFilePath() {
    return String(_logFilePath);
}

void LogModule::clearLog() {
    if (LittleFS.remove(_logFilePath)) {
        writeHeaderIfNeeded();
    }
}
