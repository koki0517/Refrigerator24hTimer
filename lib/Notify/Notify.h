#pragma once

#include <WiFi.h>
#include <HTTPClient.h>

#include "settings.h"

void wifiConnect() {
  WiFi.begin(ssid, password);  // WiFi接続
  while (WiFi.status() != WL_CONNECTED) {  // WiFi 接続待ち
    delay(100);
    Serial.printf(".");
  }
  Serial.println("\nwifi connect ok");
}

void send(String message) {
  const char* host = "notify-api.line.me";
  WiFiClientSecure client;
  Serial.println("Try to connect");
  //LineのAPIサーバに接続
  if (!client.connect(host, 443)) {
    Serial.println("Connection failed");
    return;
  }
  Serial.println("Connected");
  //リクエストを送信
  String query = String("message=") + message;
  String request = String("") +
                "POST /api/notify HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "Authorization: Bearer " + token + "\r\n" +
                "Content-Length: " + String(query.length()) +  "\r\n" + 
                "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";
  client.print(request);

  //受信終了まで待つ 
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") {
      break;
    }
  }

  String line = client.readStringUntil('\n');
  Serial.println(line);
}