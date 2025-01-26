byte leds[8][8];

int colunas[8] = {10, 14, 12, 13, 11, 15, 16, 17};
int linhas[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int linha = 0,
    coluna = 0;


void setup() {

  for(int thisPin = 0; thisPin < 8; thisPin++){
    pinMode(colunas[thisPin], OUTPUT);
    pinMode(linhas[thisPin], OUTPUT);

    digitalWrite(colunas[thisPin], HIGH);
  }

  //digitalWrite(colunas[0], LOW);
  //digitalWrite(linhas[7], HIGH);
}

void loop() {

  for(int thisPin = 0; thisPin < 8; thisPin++){
    digitalWrite(colunas[thisPin], HIGH);
    digitalWrite(linhas[thisPin], LOW);
  }

  digitalWrite(colunas[coluna], LOW);
  digitalWrite(linhas[linha], HIGH);

  if(coluna < 8){
    coluna++;
  } else if (coluna >= 8) {
    coluna = 0;
    if(linha < 8){
      linha++;
    } else if(linha >= 8) {
      linha = 0;
    }
  }

  delay(50);
  
}
