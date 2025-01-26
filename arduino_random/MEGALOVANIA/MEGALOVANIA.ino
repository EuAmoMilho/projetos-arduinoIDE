#include "pitches.h"

int melodia[] = {
  NOTE_D4, NOTE_D4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
  NOTE_C4, NOTE_C4, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
  NOTE_B3, NOTE_B3, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4,
  NOTE_AS3, NOTE_AS3, NOTE_D5, NOTE_A4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_F4, NOTE_G4
} ;

int duracaoNotas[] = {
  125, 125, 250, 375, 250, 250, 250, 125, 125, 125,
  125, 125, 250, 375, 250, 250, 250, 125, 125, 125,
  125, 125, 250, 375, 250, 250, 250, 125, 125, 125,
  125, 125, 250, 375, 250, 250, 250, 125, 125, 125
} ;

int melodiaDisplay[] = {
  2, 2, 2, 9, 8, 7, 5, 2, 5, 7,
  0, 0, 2, 9, 8, 7, 5, 2, 5, 7,
  11, 11, 2, 9, 8, 7, 5, 2, 5, 7,
  10, 10, 2, 9, 8, 7, 5, 2, 5, 7,
} ;

int nota = 0;

/*
byte matDisplay[12][8] = {
  { 0, 1, 1, 0, 0, 0, 1, 1}, // C4 - 0
  { 0, 1, 1, 0, 0, 0, 1, 0}, // C4# - 1
  { 1, 0, 0, 0, 0, 1, 0, 1}, // d4 - 2
  { 1, 0, 0, 0, 0, 1, 0, 0}, // d4# - 3
  { 0, 1, 1, 0, 0, 0, 0, 1}, // E4 - 4
  { 0, 1, 1, 1, 0, 0, 0, 1}, // F4 - 5
  { 0, 1, 1, 1, 0, 0, 0, 0}, // F4# - 6
  { 0, 1, 0, 0, 0, 0, 1, 1}, // G4 - 7
  { 0, 1, 0, 0, 0, 0, 1, 0}, // G4# - 8
  { 0, 0, 0, 1, 0, 0, 0, 1}, // A4 - 9
  { 0, 0, 0, 1, 0, 0, 0, 0}, // A4# - 10
  { 1, 1, 0, 0, 0, 0, 0, 1} //  b4 - 11
} ; 
*/

byte matDisplay[12][8] = {
  { 1, 0, 0, 1, 1, 1, 0, 0}, // C4 - 0
  { 1, 0, 0, 1, 1, 1, 0, 1}, // C4# - 1
  { 0, 1, 1, 1, 1, 0, 1, 0}, // d4 - 2
  { 0, 1, 1, 1, 1, 0, 1, 1}, // d4# - 3
  { 1, 0, 0, 1, 1, 1, 1, 0}, // E4 - 4
  { 1, 0, 0, 0, 1, 1, 1, 0}, // F4 - 5
  { 1, 0, 0, 0, 1, 1, 1, 1}, // F4# - 6
  { 1, 0, 1, 1, 1, 1, 0, 0}, // G4 - 7
  { 1, 0, 1, 1, 1, 1, 0, 1}, // G4# - 8
  { 1, 1, 1, 0, 1, 1, 1, 0}, // A4 - 9
  { 1, 1, 1, 0, 1, 1, 1, 1}, // A4# - 10
  { 0, 0, 1, 1, 1, 1, 1, 0} //  b4 - 11
} ; 

void setup() {

  for(int i=2; i<=10; i++){
    pinMode(i, OUTPUT);
  }
  
  pinMode(11, INPUT);
}

void loop() {

  if(digitalRead(11)==HIGH){
    for (int thisNote = 0; thisNote < 40; thisNote++) {

    int noteDuration = duracaoNotas[thisNote];
    nota = melodiaDisplay[thisNote];

    tone(10, melodia[thisNote], noteDuration);

    ligaSegmentosDisplay(nota);
    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

     int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    } 
  } else {
    tone(10, NOTE_C8, 100);
    ligaSegmentosDisplay(0);

  }

  delay(3000);
}

void ligaSegmentosDisplay(int digito){ //função para acionar o display com o digito correspondente

  byte pino = 2;
   
  //Liga os segmentos de acordo com o digito correspondente
  for (byte contadorSegmentos = 0; contadorSegmentos < 8; ++contadorSegmentos){ 
    digitalWrite(pino, matDisplay[digito][contadorSegmentos]);
    ++pino; 
  }
}