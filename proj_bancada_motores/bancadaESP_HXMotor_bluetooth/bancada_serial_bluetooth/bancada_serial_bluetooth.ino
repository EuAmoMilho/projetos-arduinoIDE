#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#include "HX711.h"

//baixar aplicativo "serial bluetooth terminal"

const byte numChars = 32;
char receivedChars[numChars];

int escspd = 0,
    esc_percent = 0,
    w = 0;
    
const int DTpin = 16,
          SCKpin = 4,
          escpin = 12;

float hxfactor = 0; //fator de calibracao*******

unsigned long previousMillis = 0;

const long intervalo = 10000;

Servo ESC;

HX711 carga;

BluetoothSerial serialBT;

void setup(){

  ESC.attach(escpin);
  ESC.writeMicroseconds(1000);

  carga.begin(DTpin, SCKpin);
  
  while(hxfactor == 0){ setCaliFactor(); delay(500); }
  
  carga.set_scale(hxfactor); //fator de calibracao - rodar codigo p/calibrar
  carga.tare(); // define o valor do 'peso 0' da balança
  
  carga.power_down();
  

  serialBT.begin("bancada_de_testes");

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
    
    carga.power_down();

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
  }

  recnum = atoi(receivedChars);
  esc_percent = constrain(recnum, 0, 100);
  escspd = map(esc_percent, 0, 100, 1000, 2000);
}

void setCaliFactor(){
  if(carga.is_ready()){
    
    carga.set_scale();
    
    serialBT.println("Calibrando... remova todos os pesos da balança.");
    delay(6000);

    carga.tare();

    serialBT.println("Calibragem concluida. Agora, coloque um peso conhecido na balança.");

    delay(6000);
    
    long reading = carga.get_units(10);

    serialBT.print("Resultado (anote esse numero): ");
    serialBT.println(reading);

    serialBT.println("Divida o resultado pelo valor do peso conhecido (em gramas)");

    for(int j=0; j<1; ){
      
      static byte i = 0;
      char endmarker = '\n';
      char rc;
  
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
      
      hxfactor = atof(receivedChars);

      j++;
    }
  } else { serialBT.println("HX711 not found");}
  
  delay(1000);
}
