#include <ESP32Servo.h>
#include <Arduino.h>
#include "HX711.h"
#include "BluetoothSerial.h"

//baixar aplicativo "serial bluetooth terminal"

const byte numChars = 32;
char receivedChars[numChars];

int escspd = 0,
    esc_percent = 0,
    w = 0;
    
const int DTpin = 16,
          SCKpin = 4,
          escpin = 12;

const float hx711scale = -410.3535; //inserir fator de calibracao*******

unsigned long previousMillis = 0;

const long intervalo = 10000;

Servo ESC;

HX711 carga;

BluetoothSerial serialBT;

void setup(){
  Serial.begin(115200);

  ESC.attach(escpin, 1000, 2000);
  ESC.writeMicroseconds(1000);

  carga.begin(DTpin, SCKpin);
  carga.set_scale(hx711scale); //fator de calibracao - rodar codigo p/calibrar
  carga.tare(); // define o valor do 'peso 0' da balança
  
  carga.power_down();
  

  serialBT.begin("bancada_de_testes");
  Serial.println("Dispositivo ativo, pode parear o blutufe");

  serialBT.print("ESC em ");
      serialBT.print(esc_percent);
      serialBT.println("% da velocidade");
      serialBT.print("'peso' do motor: ");
      serialBT.print(w);
      serialBT.println(" (g)");

      Serial.print("ESC em ");
      Serial.print(esc_percent);  
      Serial.println("% da velocidade");
      Serial.print("'peso' do motor: ");
      Serial.print(w);
      Serial.println(" (g)");
  
}

void loop(){
  
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= intervalo){
    previousMillis = currentMillis;

    carga.power_up();
    
    w = carga.get_units(5);

    serialBT.println("***PARA O CONTROLE DO MOTOR, DIGITE VALOR DE 0 A 100 (%)***");
    serialBT.println();
    serialBT.print("ESC em ");
    serialBT.print(esc_percent);
    serialBT.println("% da velocidade");
    serialBT.print("'peso' do motor: ");
    serialBT.print(w);
    serialBT.println(" (g)");
    serialBT.println();

    Serial.println("***PARA O CONTROLE DO MOTOR, DIGITE VALOR DE 0 A 100 (%)***");
    Serial.println();
    Serial.print("ESC em ");
    Serial.print(esc_percent);  
    Serial.println("% da velocidade");
    Serial.print("'peso' do motor: ");
    Serial.print(w);
    Serial.println(" (g)");
    Serial.println();

    escspd = 1000;
    esc_percent = 0;
    carga.power_down();
  }

  set_escBT();
  set_escUSB();

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
  }

  recnum = atoi(receivedChars);
  esc_percent = constrain(recnum, 0, 100);
  escspd = map(esc_percent, 0, 100, 1000, 2000);
}

void set_escUSB(){
  static byte i = 0;
  char endmarker = '\n';
  char rc;
  int recnum = 0;
  
  if (Serial.available() > 0){
    rc = Serial.read();

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
  }

  recnum = atoi(receivedChars);
  esc_percent = constrain(recnum, 0, 100);
  escspd = map(esc_percent, 0, 100, 1000, 2000);
}
  
