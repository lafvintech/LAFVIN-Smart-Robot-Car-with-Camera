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
const uint8_t MIN_DISTANCE = 5;
const uint8_t STOP_DISTANCE = 20;
const uint8_t FOLLOW_DISTANCE = 30;
const uint8_t BACKWARD_SPEED = 80;
const uint8_t FORWARD_SPEED = 100;
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

  Serial.println(F("Follow mode ready"));
}

void loop() {
  wdt_reset();

  if (g_firstEnter) {
    setServoAngle(Config::SERVO_CENTER);
    g_firstEnter = false;
  }

  const uint16_t distance = readUltrasonicDistance();

  if (distance > 0 && distance <= Config::MIN_DISTANCE) {
    moveBackward(Config::BACKWARD_SPEED);
  } else if (distance >= (Config::MIN_DISTANCE + 1) &&
             distance <= Config::STOP_DISTANCE) {
    stopMotors();
  } else if (distance >= (Config::STOP_DISTANCE + 1) &&
             distance <= Config::FOLLOW_DISTANCE) {
    moveForward(Config::FORWARD_SPEED);
  } else {
    stopMotors();
  }
}
