#include <Arduino.h>

int opentime = 5000; 
String cmd;
#define limit_up 18
#define limit_down 19

class Barrier {
  private:
    int pinA = 0;
    int pinB = 0;
  public:
    void setPin(int pin_a, int pin_b) {
      pinA = pin_a;
      pinB = pin_b;
      pinMode(pinA, OUTPUT);
      pinMode(pinB, OUTPUT);
    }
    void stop() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
    }
    void up() {
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      while(digitalRead(limit_up) == HIGH) {
        delay(10);
      }
      stop();
    }
    void down() {
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      while(digitalRead(limit_down) == HIGH) {
        delay(10);
      }
      stop();
    }
};

Barrier bar;

void setup() {
  Serial.begin(9600);
  bar.setPin(16, 17);
  pinMode(limit_up, INPUT_PULLUP);
  pinMode(limit_down, INPUT_PULLUP);
}

void loop() {
  if (Serial.available() > 0) {
    cmd = Serial.readString();
  }
  
  if (cmd == "u") {
    bar.up();
  } else if (cmd == "d") {
    bar.down();
  } else {
    bar.stop();
  }
  cmd = "";
}

