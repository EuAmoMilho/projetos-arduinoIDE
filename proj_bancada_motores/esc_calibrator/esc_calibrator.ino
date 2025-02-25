#include <ESP32Servo.h>

const int escPin = 18,
          min_pulse = 1000,
          max_pulse = 2000;

Servo esc;

void setup(){
  
  esc.attach(escPin);
  
  // > retire a alimentacao da ESC
  
  esc.writeMicroseconds(max_pulse);
  
  // > alimente a ESC (~8,7V a 14V)
  
  delay(10000);
  
  esc.writeMicroseconds(min_pulse);
  
  delay(500);

}

void loop() {}
