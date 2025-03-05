#include "pitches.h"

bool pitar = true;

const int pitador = 32,
          potenciometro = 33,
          duracao = 250,
          adcValor = 4095;

const float rdiv = 0.62,
            tensaoRef = 5.0;

int adc = 0,
    previous_graus = 0,
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

  if(abs(graus - previous_graus) > 5){
  pitar = true;
  }

  if(graus >= 30 && graus < 55 && pitar){
    tone(pitador, NOTE_C6, duracao);
    pitar = false;
  }
  else if (graus > 75 && graus < 100 && pitar){
    tone(pitador, NOTE_E6, duracao);
    pitar = false;
  }
  else if (graus > 120 && graus < 145 && pitar){
    tone(pitador, NOTE_G6, duracao);
    pitar = false;
  }
  else if (graus > 170) && pitar{
    tone(pitador, NOTE_C7, duracao);
    pitar = false;
  }
  
  previous_graus = graus;
  
  Serial.print(tensao);
  Serial.println("V");
  Serial.println(adc);


  delay(3000);
}
