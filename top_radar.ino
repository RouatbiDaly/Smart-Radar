//Created by Rouatbi
-----------------------------------

#include <SoftwareSerial.h>
#include <Servo.h>
#define trigPin 6  //Trig Ultrasons (sortie)
#define echoPin 5  //Echo Ultrasons (entrée)
#define Green 13      //Led verte
#define Red 11     //Led rouge
Servo myservo; 
int bluetoothTx = 9; // bluetooth tx to 10 pin
int bluetoothRx = 10;
int pos = 0;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() {
  Serial.begin(9600);
   bluetooth.begin(9600);
    
  pinMode(trigPin, OUTPUT);  //Trig est une sortie
  pinMode(echoPin, INPUT);   //Echo est le retour, en entrée
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
   myservo.attach(3);
}

void loop() {
  if(bluetooth.available()> 0 ) // receive number from bluetooth
  {
    int pos = bluetooth.read(); // save the received number to servopos
    Serial.println(pos); // serial print servopos current number received from bluetooth
    myservo.write(pos); // roate the servo the angle received from the android app
  }
 
    long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(10); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Trig déclenché 10ms sur HIGH
  digitalWrite(trigPin, LOW);
  
  // Calcul de l'écho
  duration = pulseIn(echoPin, HIGH);
  // Distance proportionnelle à la durée de sortie
  distance = duration*340/(2*10000);  //Vitesse du son théorique
   
  if (distance > 18) {  // Distance trop près
    digitalWrite(Green,HIGH); //Vert éclairé seulement
    digitalWrite(Red,LOW);
  
}
  else if (distance >13) {
    digitalWrite(Green,LOW);
    digitalWrite(Red,HIGH);
      tone(Red, 900); 
      delay(1000);
      noTone(Red);     // Stop sound...
      delay(1000); 
  }
 else if (distance >9){
    digitalWrite(Green,LOW);
    digitalWrite(Red,HIGH);
      tone(Red, 500); 
      delay(1000);
      noTone(Red);     // Stop sound...
      delay(1000); 
  }
  else if (distance >4){
    digitalWrite(Green,LOW);
    digitalWrite(Red,HIGH);
      tone(Red, 300); 
      delay(1000);
      noTone(Red);     // Stop sound...
      delay(1000); 
  }
  if ( distance <= 0){  
    //Serial.print(duration);
    Serial.println("Hors de portee");
  }
  else {
    Serial.print(distance);
    Serial.print(" cm ");
    Serial.print(duration);
    Serial.println(" ms");
  }
  delay(100);  //0.1 sec entre deux mesures

  }
  

 

