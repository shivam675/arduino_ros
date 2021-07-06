/*
---- Receiver Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/

#include <Servo.h>    //the library which helps us to control the servo motor
#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem (nRF24L)

//define our L298N control pins
//Motor A
const int RightMotorForward = 3;    // IN1
const int RightMotorBackward = 4;   // IN2
//Motor B
const int LeftMotorForward = 5;     // IN3
const int LeftMotorBackward = 6;    // IN4

//define the servo name
Servo myServo;


RF24 radio(8,10);     /*This object represents a modem connected to the Arduino. 
                      Arguments 5 and 10 are a digital pin numbers to which signals 
                      CE and CSN are connected.*/

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem,that will receive data from the Arduino.

int data[1];


void setup(){
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  //define the servo input pins
  myServo.attach(14); //A0
  
  radio.begin();                    //it activates the modem.
  Serial.begin(9600);
  radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data.
  radio.startListening();           //enable receiving data via modem
  }

void loop(){
  if(radio.available()){
    radio.read(data, 1);
    Serial.print(data[0]);
    if(data[0] < 11 && data[0] > 6){
    // This is backward
    // Set a Motor A backward
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);
    // Set a Motor B backward
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, HIGH);
    }
    if(data[0] > -1 && data[0] < 4){
    // This is forward
    // Set a Motor A forward
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    // Set a Motor B forward
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    }
    if (data[0] == 5){
    // Stop Motors
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
    }
    // This is Backward
    // Set a Motor A Backward
    if(data[0] < 21 && data[0] > 16){
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    // Set a Motor B Backward
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, HIGH);
    }
    // Turn Right
    if(data[0] > 10 && data[0] < 14){
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, HIGH);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    }
    // Turn Left
    if(data[0] == 15){
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(LeftMotorBackward, LOW);
    }
    // for the servo motor
    if(data[0] < 31 && data[0] > 21){
      int potValue = data[0];
      int potPos = map(potValue, 21, 30, 10, 170);
      myServo.write(potPos); 
    }
  }
}
