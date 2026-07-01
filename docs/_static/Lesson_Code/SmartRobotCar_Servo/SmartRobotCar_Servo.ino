#include <Arduino.h>
#include <Servo.h>
#include <avr/wdt.h>

namespace ServoConfig {
const uint8_t SERVO_PIN = 10;
const uint8_t CENTER_ANGLE = 90;
const uint8_t LEFT_ANGLE = 45;
const uint8_t RIGHT_ANGLE = 135;
const uint16_t MOVE_DELAY_MS = 800;
}

Servo g_servo;

void safeDelay(uint16_t ms) {
  for (uint16_t i = 0; i < ms; ++i) {
    delay(1);
    wdt_reset();
  }
}

void setServoAngle(uint8_t angle) {
  if (angle > 180) {
    angle = 180;
  }

  g_servo.write(angle);
  Serial.print(F("Servo angle: "));
  Serial.println(angle);
  safeDelay(ServoConfig::MOVE_DELAY_MS);
}

void setup() {
  wdt_enable(WDTO_2S);

  Serial.begin(9600);

  g_servo.attach(ServoConfig::SERVO_PIN);
  setServoAngle(ServoConfig::CENTER_ANGLE);

  Serial.println(F("Servo lesson ready"));
}

void loop() {
  wdt_reset();

  setServoAngle(ServoConfig::LEFT_ANGLE);
  setServoAngle(ServoConfig::CENTER_ANGLE);
  setServoAngle(ServoConfig::RIGHT_ANGLE);
  setServoAngle(ServoConfig::CENTER_ANGLE);
}
