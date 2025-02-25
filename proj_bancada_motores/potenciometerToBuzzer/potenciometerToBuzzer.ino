#include "pitches.h"

const int pitador = 32,
          potenciometro = 33,
          duracao = 250,
          adcValor = 4095;

const float rdiv = 0.62,
            tensaoRef = 5.0;

int adc = 0,
    graus = 0;
    
float tensao = 0.0;

void setup() {
  pinMode(pitador, OUTPUT);
  Serial.begin(115200);
  
}

void loop() {

  adc = analogRead(33);
  tensao = (adc*rdiv*tensaoRef)/adcValor;
  graus = map(adc, 0, adcValor, 0, 180);

  if(graus >= 30 && graus < 55){
    tone(pitador, NOTE_C6, duracao);
  }
  else if (graus > 75 && graus < 100){
    tone(pitador, NOTE_E6, duracao);
  }
  else if (graus > 120 && graus < 145){
    tone(pitador, NOTE_G6, duracao);
  }
  else if (graus > 170){
    tone(pitador, NOTE_C7, duracao);
  }

Serial.print(tensao);
Serial.println("V");
Serial.println(adc);


delay(3000);
}
