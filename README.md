# esp-skeleton

ESP8266 および ESP32 に対応した、汎用的なファームウェア開発用スケルトン（テンプレート）プロジェクトです。
Wi-Fi 接続、時刻同期、設定保存、Web サーバー、ロギング、OTA アップデートといった、多くの IoT プロジェクトで必要となる共通基盤機能があらかじめ実装されています。

## 特徴

- **マルチプラットフォーム対応**: PlatformIO を使用し、ESP8266 (ESP-WROOM-02等) と ESP32 の両方で動作します。
- **Wi-Fi 基盤**: STA（子機）モードでの接続と、接続失敗時の AP（親機）モードへの自動フォールバックに対応。
- **時刻同期 (NTP)**: `TimeModule` により、起動時に自動で日本標準時 (JST) への同期を行います。
- **Web サーバー**: 静的ファイルの配信 (LittleFS) と、JSON API の実装が容易な `CoreWebServer` を搭載。
- **設定管理**: EEPROM を使用した Wi-Fi 設定の保存・読み込みと、アプリケーション固有設定用の汎用読み書きメソッドを提供。
- **ロギング**: LittleFS 上の CSV ファイルに実時刻付きでデータを記録。
- **OTA (Over-the-Air)**: Wi-Fi 経由でのファームウェアアップデートに対応。

## プロジェクト構成

```
esp-skeleton/
├── data/               # Web UI 資産 (LittleFS に書き込まれる)
│   └── index.html      # デフォルトのダッシュボード
├── include/
│   └── config.h        # 基本設定・デフォルト値
├── src/
│   ├── main.cpp        # アプリケーションのエントリポイント
│   └── core/           # 基盤モジュール群
│       ├── CoreWebServer   # Webサーバー管理
│       ├── LogModule       # CSVロギング
│       ├── OTAModule       # OTAアップデート
│       ├── SystemConfig    # 設定保存 (EEPROM)
│       └── TimeModule      # 時刻同期 (NTP)
└── platformio.ini      # PlatformIO プロジェクト設定
```

## 使い方

1. **環境構築**: PlatformIO IDE がインストールされた VS Code 等でプロジェクトを開きます。
2. **Wi-Fi 設定**: `include/config.h` にデフォルトの SSID/パスワードを記述するか、起動後に AP モードで接続して設定を行います。
3. **ビルドと書き込み**:
   - `Upload` を実行してファームウェアを書き込みます。
   - `Upload Filesystem Image` を実行して `data/` ディレクトリの内容を書き込みます。
4. **アプリケーション開発**:
   - `src/main.cpp` の `loop()` 内にセンサーの読み取りなどのロジックを追加します。
   - アプリケーション固有の API は `webServer.server().on(...)` で追加可能です。

## ライセンス

MIT License
