#include <Arduino.h>
#include "HX711.h"

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

const int currentpin = 34, //Arduino intances A4 - A7 = ESP32 pins 32 - 35
          voltagepin = 33,
          
          ADC_MAX = 1023, //4095 p/ ESP32
          ACSoffset = 0, //Analisar o retorno do ADC para corrente de 0A, esse sera o offset
          //add variavel voltageoffset se for necessario e ajustar os calculos

          cargaDTpin = 2,
          cargaSCKpin = 3;
          
const float VREF = 5; // 3.3 Para ESP32

double divTensaoACS = 1; // 1.5 para ESP32 (fator de multiplicação para div de tensao)
double sens = 0.066; //sensibilidade para o modelo de 30A
double corrente = 0.0;
double tensao = 0.0;
double normal = 0.0

HX711 scale

void setup() {
  Serial.begin(57600);

  scale.begin(cargaDTpin, cargaSCKpin);
  scale.set_scale();//Adicionar o fator de calibragem 
  //(calibrar a balança antes de rodar o codigo)
  //o fator sera = (valor obtido na calibracao/peso conhecido)
  scale.tare();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("EDRA");
  display.setTextSize(1);
  display.setCursor(1,0);
  display.print("BLDC motor testing");
  
  
  display.display();
  delay(2000);

  drawData();
}

void loop() {
  
  corrente = getCurrent();
  Serial.print("Valor da corrente:");
  Serial.println(corrente);

  tensao = getVoltage();
  
  Serial.print("valor da tensao:" );
  Serial.println(tensao);

  normal = scale.get_units(5);

  drawData();

  delay(1000);
}

double getCurrent(){
  int leituraADC = 0;
  double sample = 0.0,
        media = 0.0,
        dc_reading = 0.0,
        current = 0.0;

  for(int i = 0; i<1000; i++){
    leituraADC = analogRead(currentpin);
    sample = sample + leituraADC;
    delay(3);
  }

  media = sample/1000;
  dc_reading = (((media - ACSoffset) * VREF) / ADC_MAX) * divTensaoACS;
  current = dc_reading/sens;

  return current;
}

double getVoltage(){
  int voltagereading = analogRead(voltagepin);
  
  Serial.println(voltagereading);
  double voltage = voltagereading * ((5 * VREF) / ADC_MAX);

  return voltage;
}

void drawData(void) {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("A: ");
  display.println(corrente);
  display.print("V: ");
  display.println(tensao);
  display.print("M(g):");
  display.print(normal);

  display.display();
  delay(2000);
}
