#include <FrequencyTimer2.h>
 
//matriz que "mapeia" todos os LEDs que estarao ligados
#define frame1 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 1, 1, 1, 1, 0, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame2 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame3 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame4 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame5 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame6 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1} \
}
 
#define frame7 { \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 1, 1, 1, 1, 0, 1}, \
{1, 0, 0, 1, 1, 0, 0, 1}, \
{1, 1, 1, 1, 1, 1, 1, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 0, 0, 0, 0, 0, 0, 1}, \
{1, 1, 0, 0, 0, 0, 1, 1} \
}

//coluna da matriz
byte col = 0;

byte leds[8][8];
 
//obs: os pinos da matriz nao necessariamente seguem um padrao. eh bom olhar o datasheet para decifrar
int pinos[17] = { 0, 5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9, 8, 7, 6 };

//identificar os pinos dos anodos e catodos
int colunas[8] = {10, 14, 12, 13, 11, 15, 16, 17};
 
int linhas[8] = {2, 3, 4, 5, 6, 7, 8, 9};
 
const int termos = 19;

//matriz animacao
byte padroes[termos][8][8] = { frame1, frame2, frame3, frame4, frame5, frame5, frame5, frame5,
                              frame6, frame4, frame1, frame7, frame1, frame7, frame1, frame7,
                              frame1, frame7, frame1};

int padrao = 0;

void setup() {

  pinMode(A4, INPUT);

//inicializar todos os pinos como saida
  for (int i = 1; i <= 16; i++) {
    pinMode(pinos[i], OUTPUT);
  }

//funcao para exibir os LEDs um por um em frequencia ininterrupta
  FrequencyTimer2::setOnOverflow(display);
 
  setpadrao(padrao);
}
 
void loop() {

//modifica os frames
  padrao = ++padrao % termos;
  setpadrao(padrao);

//modifica a velocidade da animacao
  delay(map(analogRead(A4), 0, 1023, 0, 1000));
}
 

void setpadrao(int padrao) {
 
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = padroes[padrao][i][j];
    }
  }
}

void display() {
 
  digitalWrite(colunas[col], HIGH);
  col++;
  if (col == 8) {
    col = 0;
  }
  for (int linha = 0; linha < 8; linha++) {
    if (leds[col][7 - linha] == 1) {
 
      digitalWrite(linhas[linha], HIGH);
    } else {
 
      digitalWrite(linhas[linha], LOW);
    }
  }
 
  digitalWrite(colunas[col], LOW);
  delay(analogRead(A4));
}
