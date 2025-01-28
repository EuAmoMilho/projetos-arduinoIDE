String str = "off";

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  Serial.println("Digite  comando:");
  while (Serial.available()==0) {}
    
  str = Serial.readString();
  str.trim();
  
  if(str == "on"){
    digitalWrite(LED_BUILTIN, HIGH);
  } else { digitalWrite(LED_BUILTIN, LOW); }

delay(1000);
}
