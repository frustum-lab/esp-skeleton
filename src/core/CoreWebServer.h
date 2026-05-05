#ifndef CORE_WEB_SERVER_H
#define CORE_WEB_SERVER_H

#if defined(ESP8266)
  #include <ESP8266WebServer.h>
  typedef ESP8266WebServer WebServerType;
#elif defined(ESP32)
  #include <WebServer.h>
  typedef WebServer WebServerType;
#endif
#include <LittleFS.h>

/**
 * CoreWebServer - ESP8266/ESP32 HTTP サーバーのコア基盤
 *
 * 担当する機能:
 *  - 静的ファイル配信 (LittleFS)
 *  - CORS対応 / OPTIONSハンドリング
 *  - キャプティブポータルリダイレクト (APモード時)
 *  - 404レスポンス
 *  - AppAPI が routes を追加するための server() アクセサ提供
 */
class CoreWebServer {
public:
    CoreWebServer();

    // captivePortalMode=true の場合、未知URLをsetup.htmlへリダイレクト
    void begin(bool captivePortalMode = false);
    void handle();

    // ルートを登録するために使用
    WebServerType& server() { return _server; }

    // CORSヘッダ付きJSONレスポンス送信ヘルパー
    void sendJson(int code, const String& json);

private:
    WebServerType _server;
    bool _isCaptivePortal;
};

#endif
