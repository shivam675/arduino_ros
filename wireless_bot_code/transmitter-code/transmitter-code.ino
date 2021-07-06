/*
---- Transmitter Code ----
Mert Arduino Tutorial & Projects (YouTube)
Please Subscribe for Support
*/

#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"                     //the library which helps us to control the radio modem

//define the input pins
int x_axis = A0;
int y_axis = A1;
int potPin = A2;

//define variable values
int xValue;
int yValue;
int potValue;


int data[1];

RF24 radio(9,10);                     //5 and 10 are a digital pin numbers to which signals CE and CSN are connected.
                                      
const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.


void setup(void){
  Serial.begin(9600);
  radio.begin();                      //it activates the modem.
  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
}

void loop(){
  
  //Send X-axis data
  xValue = analogRead(x_axis);
  xValue = map(xValue, 0, 1023, 0, 10);
  data[0] = xValue;
  radio.write(data, 1); 
  
  //Send Y-axis data
  yValue = analogRead(y_axis);
  yValue = map(yValue, 0, 1023, 11, 20);
  data[0] = yValue;
  radio.write(data, 1);

  Serial.println(xValue);
  Serial.println(yValue);
  delay(1000);
  
  //Send Potentiometer data
  potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 21, 30);
  data[0] = potValue;
  radio.write(data, 1);
}
