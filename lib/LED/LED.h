#pragma once
#include <Arduino.h>

enum class LEDColor {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  WHITE,
};

static const uint8_t RED_PIN = 0;
static const uint8_t GREEN_PIN = 0;
static const uint8_t BLUE_PIN = 0;

void initLED(){
  pinMode(RED_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void onLED(const LEDColor col){
  switch (col){
    case LEDColor::RED:
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
      break;
    case LEDColor::GREEN:
      analogWrite(RED_PIN, 0);
      pinMode(RED_PIN, INPUT);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
      break;
    case LEDColor::BLUE:
      analogWrite(RED_PIN, 0);
      pinMode(RED_PIN, INPUT);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
      break;
    case LEDColor::YELLOW:
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
      break;
    case LEDColor::WHITE:
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
      break;
  }
}

void offLED(){
  analogWrite(RED_PIN, 0);
  pinMode(RED_PIN, INPUT);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);
}