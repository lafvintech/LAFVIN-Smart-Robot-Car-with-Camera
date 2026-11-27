#include <Arduino.h>
#include <avr/wdt.h>

namespace Pins {
const uint8_t MOTOR_PWMA = 5;
const uint8_t MOTOR_PWMB = 6;
const uint8_t MOTOR_AIN_1 = 7;
const uint8_t MOTOR_BIN_1 = 8;
const uint8_t MOTOR_STBY = 3;
const uint8_t LINE_SENSOR_LEFT = A2;
const uint8_t LINE_SENSOR_MIDDLE = A1;
const uint8_t LINE_SENSOR_RIGHT = A0;
}

namespace Config {
const uint8_t NORMAL_SPEED = 100;
const uint8_t TURN_SPEED = 60;
const uint8_t SHARP_TURN_SPEED = 90;
const uint16_t SCAN_TIMEOUT_MS = 3000;
}

bool g_timestampReady = true;
bool g_blindDetection = true;
uint32_t g_scanStartTime = 0;

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

void turnLeft(uint8_t speed) {
  setRightMotor(speed, true);
  setLeftMotor(speed, false);
}

void turnRight(uint8_t speed) {
  setRightMotor(speed, false);
  setLeftMotor(speed, true);
}

bool isInRange(uint32_t value, uint32_t minValue, uint32_t maxValue) {
  return value >= minValue && value <= maxValue;
}

void setup() {
  wdt_enable(WDTO_2S);

  Serial.begin(9600);

  pinMode(Pins::MOTOR_PWMA, OUTPUT);
  pinMode(Pins::MOTOR_PWMB, OUTPUT);
  pinMode(Pins::MOTOR_AIN_1, OUTPUT);
  pinMode(Pins::MOTOR_BIN_1, OUTPUT);
  pinMode(Pins::MOTOR_STBY, OUTPUT);

  pinMode(Pins::LINE_SENSOR_LEFT, INPUT);
  pinMode(Pins::LINE_SENSOR_MIDDLE, INPUT);
  pinMode(Pins::LINE_SENSOR_RIGHT, INPUT);

  stopMotors();

  Serial.println(F("Line tracking mode ready"));
}

void loop() {
  wdt_reset();

  const bool detL = (digitalRead(Pins::LINE_SENSOR_LEFT) == HIGH);
  const bool detM = (digitalRead(Pins::LINE_SENSOR_MIDDLE) == HIGH);
  const bool detR = (digitalRead(Pins::LINE_SENSOR_RIGHT) == HIGH);

  if (!detL && detM && !detR) {
    moveForward(Config::NORMAL_SPEED);
    g_timestampReady = true;
    g_blindDetection = true;
  } else if (detL && detM && !detR) {
    turnLeft(Config::TURN_SPEED);
    g_timestampReady = true;
    g_blindDetection = true;
  } else if (detL && !detM && !detR) {
    turnLeft(Config::SHARP_TURN_SPEED);
    g_timestampReady = true;
    g_blindDetection = true;
  } else if (!detL && !detM && detR) {
    turnRight(Config::SHARP_TURN_SPEED);
    g_timestampReady = true;
    g_blindDetection = true;
  } else if (!detL && detM && detR) {
    turnRight(Config::TURN_SPEED);
    g_timestampReady = true;
    g_blindDetection = true;
  } else if (detL && detM && detR) {
    stopMotors();
    g_timestampReady = true;
    g_blindDetection = true;
  } else {
    if (g_timestampReady) {
      g_timestampReady = false;
      g_scanStartTime = millis();
      stopMotors();
    }

    const uint32_t elapsed = millis() - g_scanStartTime;

    if ((isInRange(elapsed, 0, 200) || isInRange(elapsed, 1600, 2000)) &&
        g_blindDetection) {
      turnRight(Config::NORMAL_SPEED);
    } else if (isInRange(elapsed, 200, 1600) && g_blindDetection) {
      turnLeft(Config::NORMAL_SPEED);
    } else if (isInRange(elapsed, Config::SCAN_TIMEOUT_MS,
                         Config::SCAN_TIMEOUT_MS + 500)) {
      g_blindDetection = false;
      stopMotors();
    }
  }
}
