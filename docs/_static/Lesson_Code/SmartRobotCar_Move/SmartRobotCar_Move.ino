#include <Arduino.h>
#include <avr/wdt.h>

namespace Pins {
const uint8_t MOTOR_PWMA = 5;
const uint8_t MOTOR_PWMB = 6;
const uint8_t MOTOR_AIN_1 = 7;
const uint8_t MOTOR_BIN_1 = 8;
const uint8_t MOTOR_STBY = 3;
}

namespace Config {
const uint8_t MOTOR_SPEED = 80;
const uint16_t FORWARD_TIME_MS = 2000;
const uint16_t BACKWARD_TIME_MS = 2000;
}

void safeDelay(uint16_t ms) {
  for (uint16_t i = 0; i < ms; ++i) {
    delay(1);
    wdt_reset();
  }
}

void setLeftMotor(uint8_t speed, bool forward) {
  if (speed > 0) {
    digitalWrite(Pins::MOTOR_STBY, HIGH);
    digitalWrite(Pins::MOTOR_BIN_1, forward ? HIGH : LOW);
    analogWrite(Pins::MOTOR_PWMB, speed);
  } else {
    analogWrite(Pins::MOTOR_PWMB, 0);
  }
}

void setRightMotor(uint8_t speed, bool forward) {
  if (speed > 0) {
    digitalWrite(Pins::MOTOR_STBY, HIGH);
    digitalWrite(Pins::MOTOR_AIN_1, forward ? HIGH : LOW);
    analogWrite(Pins::MOTOR_PWMA, speed);
  } else {
    analogWrite(Pins::MOTOR_PWMA, 0);
  }
}

void stopMotors() {
  analogWrite(Pins::MOTOR_PWMA, 0);
  analogWrite(Pins::MOTOR_PWMB, 0);
  digitalWrite(Pins::MOTOR_STBY, LOW);
}

void moveForward(uint8_t speed) {
  setLeftMotor(speed, true);
  setRightMotor(speed, true);
}

void moveBackward(uint8_t speed) {
  setLeftMotor(speed, false);
  setRightMotor(speed, false);
}

void setup() {
  wdt_enable(WDTO_2S);

  Serial.begin(9600);

  pinMode(Pins::MOTOR_PWMA, OUTPUT);
  pinMode(Pins::MOTOR_PWMB, OUTPUT);
  pinMode(Pins::MOTOR_AIN_1, OUTPUT);
  pinMode(Pins::MOTOR_BIN_1, OUTPUT);
  pinMode(Pins::MOTOR_STBY, OUTPUT);

  stopMotors();

  Serial.println(F("Motor test ready"));
}

void loop() {
  wdt_reset();

  Serial.println(F("Forward"));
  moveForward(Config::MOTOR_SPEED);
  safeDelay(Config::FORWARD_TIME_MS);

  stopMotors();
  safeDelay(500);

  Serial.println(F("Backward"));
  moveBackward(Config::MOTOR_SPEED);
  safeDelay(Config::BACKWARD_TIME_MS);

  stopMotors();
  safeDelay(1000);
}
