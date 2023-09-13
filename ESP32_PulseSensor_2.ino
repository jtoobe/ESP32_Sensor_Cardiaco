/*
 * pograma que usa un sensor cardiaco y muestra los latidos con un led
 * tiene conectado un potenciometro para ajustar un valor que se  
 * compara con lo leido para determinar el pulso
 * 
 */


//  Variables
int PulseSensorPin = 33;        // Pin de señal del sensor
int LED = 32;   //  pin Led
int PinPote = 35; // potenciometro para ajustar valor de comparacion


int Signal;                
int Threshold = 550;        // valor inicial para comparacion 


// The SetUp Function:
void setup() {
  pinMode(LED,OUTPUT);         // Led que va a representar los latidos
   Serial.begin(115200);       

}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPin);  // Realizo una lectura del sensor

  Threshold = analogRead(PinPote); // leo del potenciometro un valor para comparar 

   Serial.println(Threshold);                    // muestro por el monitor serial el valor de comparacion


   if(Signal > Threshold){                          
     digitalWrite(LED,HIGH);               // Si la señal es mayor que el valor de comparacion es un latido
   } else {
     digitalWrite(LED,LOW);                
   }


delay(10);


}
