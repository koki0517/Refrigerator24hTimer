#include <Arduino.h>
#include <esp_sntp.h>

#include "Notify.h"
#include "LED.h"

const uint8_t leftSensor = A1;
const uint8_t rightSensor = A0;

uint16_t thresholdLeft, thresholdRight; // 開いたことの閾値

void updateClock() {
  configTzTime("JST-9", "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
  while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET) {
    Serial.print(",");
    delay(1000); // １秒毎にリトライ
  }
}

void setup() {
  Serial.begin(115200);
  initLED();

  // WiFi接続
  onLED(LEDColor::BLUE);
  wifiConnect();  // WiFi接続
  updateClock();  // 時刻を更新
  while (1){
    Serial.println("WiFi connected");
    delay(1000);
  }

  // 閾値の設定
  onLED(LEDColor::YELLOW);
  unsigned long start = millis();
  uint16_t leftMax = 0, rightMax = 0, leftMin = 10000, rightMin = 10000;
  while (millis() - start < 10000) {
    leftMax = max(leftMax, analogRead(leftSensor));
    rightMax = max(rightMax, analogRead(rightSensor));
    leftMin = min(leftMin, analogRead(leftSensor));
    rightMin = min(rightMin, analogRead(rightSensor));
    delay(10);
  }
  thresholdLeft = (leftMax + leftMin) / 2;
  thresholdRight = (rightMax + rightMin) / 2;
  onLED(LEDColor::GREEN);
}

void loop() {
  long lastOpenedTime = time(nullptr);
  time_t t;
  struct tm *tm;
  bool hasNotified = false;
  send("電源に接続されました");

  while (1) {
    // 時刻を取得
    t = time(nullptr);
    tm = localtime(&t);
    // センサを読む
    if (analogRead(leftSensor) > thresholdLeft || analogRead(rightSensor) > thresholdRight){
      // 開いたとき最後に開いた時間を更新
      updateClock();
      lastOpenedTime = time(nullptr);
      onLED(LEDColor::WHITE);
      delay(1000);
      onLED(LEDColor::GREEN);
      delay(1000);
      continue;
    }

    // 24時間経過していたら通知
    if (ifNotifyEveryDay && time(nullptr) - lastOpenedTime > 24 * 60 * 60) {
      send("24時間以上開いていません");
      onLED(LEDColor::RED);
      while (1);
    }

    // 定期的に時刻を更新
    if (time(nullptr) - lastOpenedTime > timeToUpdateClock) {
      updateClock();
      continue;
    }

    // 1日に1回通知 (オプション)
    if (ifNotifyEveryDay) {
      // 通知する時間(timeToNotify)になったら通知
      if (tm->tm_hour == timeToNotify && !hasNotified) {
        send("[定期通知] 最後に開いたのは"+String(ctime(&lastOpenedTime)));
        hasNotified = true;
      }
      else {
        hasNotified = false;
      }
    }

    delay(1000);
  }
}