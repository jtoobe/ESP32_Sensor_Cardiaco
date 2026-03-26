// AUTORES: Maria Jose Rosales, Thiago Aguilar y Lucio Zampella
// Sensor de pulsos basico funcional para un MAX30100
// Utiliza la libreria sparkfun/SparkFun MAX3010x Pulse and Proximity Sensor Library



#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <Arduino.h>
#define SDA_PIN 21
#define SCL_PIN 22

MAX30105 particleSensor;

const byte RATE_SIZE = 15;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;
unsigned long lastMsgTime = 0;


void onBeatDetected() {
  Serial.println("¡Latido detectado!");
}

void setup() {
    
  Serial.begin(115200);
  delay(3000);
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("Escaneando I2C...");
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("Sensor no encontrado");
    while (1);
  }
  

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
  Serial.println("Sensor listo! Apoya el dedo...");
}

void loop() {

 long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++) {
        beatAvg += rates[x];
      }
      beatAvg /= RATE_SIZE;
    }
  }

  if (millis() - lastMsgTime > 500) {
    lastMsgTime = millis();
     Serial.print("IR=");
     Serial.print("IR=");
    Serial.print(irValue);
    Serial.print(", BPM=");
    Serial.print(beatsPerMinute);
    Serial.print(", Avg BPM=");
    Serial.print(beatAvg);

    if (irValue < 50000) {
      Serial.print(" -- No hay dedo!");
    }
    Serial.println();
}
}