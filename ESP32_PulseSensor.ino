/*
 *  Programa muuuuyyyyy sencillo para leer un sensor de pulso cardiaco
 *  no arroja valores muy precisos, solo para experimentacion
 */

const int pulseSensorPin = 33; // Pin analógico al que está conectado el sensor de pulso


void setup() {
  Serial.begin(115200);
 
}

void loop() {
  int sensorValue = analogRead(pulseSensorPin);
  
  int pulseRate = map(sensorValue, 0, 4095, 0, 200)/2 ; 

  // Envia el valor del pulso al Monitor Serie
  Serial.println(" Valor leido " + String(sensorValue) + "    Pulso: " + String(pulseRate) + " BPM" );
  //Serial.println(pulseRate);
  
  delay(1000); // Puedes ajustar la frecuencia de muestreo
}
