#include <ESP32Servo.h>
#include "BluetoothSerial.h"

//baixar aplicativo "serial bluetooth terminal"

const byte numChars = 32;
char receivedChars[numChars];

int escspd = 1000,
    esc_percent = 0,
    w = 0;

const int escpin = 18;

unsigned long previousMillis = 0;

const long intervalo = 10000;

Servo ESC;

BluetoothSerial serialBT;

void setup(){

  ESC.attach(escpin);
  ESC.writeMicroseconds(1000);
  serialBT.begin("bancada_de_testes");

  delay(5000);

  serialBT.print("ESC em ");
  serialBT.print(esc_percent);
  serialBT.println("% da velocidade");
  serialBT.print("'peso' do motor: ");
  serialBT.print(w);
  serialBT.println(" (g)");
}

void loop(){
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= intervalo){
    previousMillis = currentMillis;

    serialBT.println("***PARA O CONTROLE DO MOTOR, DIGITE VALOR DE 0 A 100 (%)***");
    serialBT.println();
    serialBT.print("ESC em ");
    serialBT.print(esc_percent);
    serialBT.println("% da velocidade");
    serialBT.println();

    escspd = 1000;
    esc_percent = 0;
  }

  set_escBT();

  ESC.writeMicroseconds(escspd);
  
  delay(20);
}


void set_escBT(){
  static byte i = 0;
  char endmarker = '\n';
  char rc;
  int recnum = 0;
  
  if (serialBT.available() > 0){
    rc = serialBT.read();

    if(rc!=endmarker){
      receivedChars[i] = rc;
      i++;

      if(i>=numChars){
        i = numChars - 1;
      }
    } else {
      receivedChars[i] = '\0';
      i = 0;
    }
  
    recnum = atoi(receivedChars);
    esc_percent = constrain(recnum, 0, 100);
    escspd = map(esc_percent, 0, 100, 1000, 2000);
  }
}
