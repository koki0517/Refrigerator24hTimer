#pragma once
#include <Arduino.h>

enum class LEDColor {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  WHITE,
};

static const uint8_t RED_PIN = D5;
static const uint8_t GREEN_PIN = D6;
static const uint8_t BLUE_PIN = D9;

void initLED();
void onLED(const LEDColor col);
void offLED();

void initLED(){
  pinMode(RED_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  offLED();
}


void onLED(const LEDColor col){
  switch (col){
    case LEDColor::RED:
    pinMode(RED_PIN, OUTPUT);
      analogWrite(RED_PIN, 0); // 255 - 255 = 0
      analogWrite(GREEN_PIN, 255); // 255 - 0 = 255
      analogWrite(BLUE_PIN, 255); // 255 - 0 = 255
      break;
    case LEDColor::GREEN:
      analogWrite(RED_PIN, 255); // 255 - 0 = 255
      pinMode(RED_PIN, INPUT);
      analogWrite(GREEN_PIN, 0); // 255 - 255 = 0
      analogWrite(BLUE_PIN, 255); // 255 - 0 = 255
      break;
    case LEDColor::BLUE:
      analogWrite(RED_PIN, 255); // 255 - 0 = 255
      pinMode(RED_PIN, INPUT);
      analogWrite(GREEN_PIN, 255); // 255 - 0 = 255
      analogWrite(BLUE_PIN, 0); // 255 - 255 = 0
      break;
    case LEDColor::YELLOW:
      pinMode(RED_PIN, OUTPUT);
      analogWrite(RED_PIN, 0); // 255 - 255 = 0
      analogWrite(GREEN_PIN, 0); // 255 - 255 = 0
      analogWrite(BLUE_PIN, 255); // 255 - 0 = 255
      break;
    case LEDColor::WHITE:
      pinMode(RED_PIN, OUTPUT);
      analogWrite(RED_PIN, 0); // 255 - 255 = 0
      analogWrite(GREEN_PIN, 0); // 255 - 255 = 0
      analogWrite(BLUE_PIN, 0); // 255 - 255 = 0
      break;
  }
}

void offLED(){
  analogWrite(RED_PIN, 255); // 255 - 0 = 255
  pinMode(RED_PIN, INPUT);
  analogWrite(GREEN_PIN, 255); // 255 - 0 = 255
  analogWrite(BLUE_PIN, 255); // 255 - 0 = 255
}