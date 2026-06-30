#include <Arduino.h>
#include <Servo.h>
#include <avr/wdt.h>

namespace Pins {
const uint8_t MOTOR_PWMA = 5;
const uint8_t MOTOR_PWMB = 6;
const uint8_t MOTOR_AIN_1 = 7;
const uint8_t MOTOR_BIN_1 = 8;
const uint8_t MOTOR_STBY = 3;
const uint8_t ULTRASONIC_TRIG = 13;
const uint8_t ULTRASONIC_ECHO = 12;
const uint8_t SERVO_PIN = 10;
}

namespace Config {
const uint8_t DETECTION_DISTANCE = 20;
const uint8_t MOVE_SPEED = 70;
const uint8_t TURN_SPEED = 70;
const uint16_t BACKUP_TIME_MS = 100;
const uint16_t TURN_TIME_MS = 50;
const uint16_t MAX_DISTANCE_CM = 300;
const uint8_t SERVO_CENTER = 90;
}

Servo g_servo;
bool g_firstEnter = true;

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

void turnLeft(uint8_t speed) {
  setRightMotor(speed, true);
  setLeftMotor(speed, false);
}

void turnRight(uint8_t speed) {
  setRightMotor(speed, false);
  setLeftMotor(speed, true);
}

void setServoAngle(uint8_t angle) {
  if (angle > 180) {
    angle = 180;
  }
  g_servo.write(angle);
  safeDelay(500);
}

uint16_t readUltrasonicDistance() {
  const unsigned long timeout = Config::MAX_DISTANCE_CM * 58UL + 2000UL;

  digitalWrite(Pins::ULTRASONIC_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(Pins::ULTRASONIC_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(Pins::ULTRASONIC_TRIG, LOW);

  unsigned long duration = pulseIn(Pins::ULTRASONIC_ECHO, HIGH, timeout);
  uint16_t distance = static_cast<uint16_t>(duration / 58UL);

  if (distance > 150) {
    distance = 150;
  }

  safeDelay(60);
  return distance;
}

void setup() {
  wdt_enable(WDTO_2S);

  Serial.begin(9600);

  pinMode(Pins::MOTOR_PWMA, OUTPUT);
  pinMode(Pins::MOTOR_PWMB, OUTPUT);
  pinMode(Pins::MOTOR_AIN_1, OUTPUT);
  pinMode(Pins::MOTOR_BIN_1, OUTPUT);
  pinMode(Pins::MOTOR_STBY, OUTPUT);

  pinMode(Pins::ULTRASONIC_TRIG, OUTPUT);
  pinMode(Pins::ULTRASONIC_ECHO, INPUT);
  digitalWrite(Pins::ULTRASONIC_TRIG, LOW);

  stopMotors();

  g_servo.attach(Pins::SERVO_PIN);
  setServoAngle(Config::SERVO_CENTER);

  Serial.println(F("Obstacle mode ready"));
}

void loop() {
  wdt_reset();

  if (g_firstEnter) {
    setServoAngle(Config::SERVO_CENTER);
    g_firstEnter = false;
  }

  uint16_t distance = readUltrasonicDistance();

  if (distance > 0 && distance <= Config::DETECTION_DISTANCE) {
    stopMotors();

    for (uint8_t i = 1; i <= 5; i += 2) {
      const uint8_t angle = 30 * i;
      setServoAngle(angle);
      safeDelay(5);

      const uint16_t scanDistance = readUltrasonicDistance();
      if (scanDistance > Config::DETECTION_DISTANCE) {
        stopMotors();

        switch (i) {
          case 1:
            turnRight(Config::TURN_SPEED);
            break;
          case 3:
            moveForward(Config::MOVE_SPEED);
            break;
          case 5:
            turnLeft(Config::TURN_SPEED);
            break;
        }

        safeDelay(Config::TURN_TIME_MS);
        g_firstEnter = true;
        return;
      }

      if (i == 5) {
        stopMotors();
        moveBackward(Config::MOVE_SPEED);
        safeDelay(Config::BACKUP_TIME_MS);
        turnRight(Config::TURN_SPEED);
        safeDelay(Config::TURN_TIME_MS);
        g_firstEnter = true;
        return;
      }
    }
  } else {
    moveForward(Config::MOVE_SPEED);
  }
}
