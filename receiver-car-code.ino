/** GESTURE CONTROLLED ROBOT
 *  TRANSMITTER BOARD CODE
 *  CREATED BY - ARNAB MUKHERJEE
 *  CREATED ON - 19-02-2019 23:37 H
 *  LANGUAGE - C
 */

#include <SPI.h>      //SPI library for communicate with the nRF24L01+
#include "RF24.h"     //The main library of the nRF24L01+

//Define enable pins of the Motors
const int enbA = 3;
const int enbB = 5;

//Define control pins of the Motors
//If the motors rotate in the opposite direction, you can change the positions of the following pin numbers
const int IN1 = 2;    //Right Motor (-)
const int IN2 = 4;    //Right Motor (+)
const int IN3 = 7;    //Left Motor (+)
const int IN4 = 6;    //Right Motor (-)

//Define variable for the motors speeds
//I have defined a variable for each of the two motors 
//This way you can synchronize the rotation speed difference between the two motors
int RightSpd = 150;
int LeftSpd = 130;

//Define packet for the direction (X axis and Y axis)
int data[2];

//Define object from RF24 library - 9 and 10 are a digital pin numbers to which signals CE and CSN are connected
RF24 radio(9,10);

//Create a pipe addresses for the communicate
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  //Define the motor pins as OUTPUT
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate            
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();             
  }

void loop(){
  Serial.print("ReadData - ");
  if (radio.available()){
    radio.read(data, sizeof(data));
    Serial.print(data[0]);
    Serial.print("   ");
    Serial.println(data[1]);
  if(data[0] > 300 && data[0] < 325 && data[1] < 170 && data[1] > 120){
      //FORWARD
      analogWrite(enbA, 150);
      analogWrite(enbB, 185);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println(" FORWARD");
    }

    if(data[0] < 400 && data[0] > 375 && data[1] < 170 && data[1] > 120){
      //BACKWARD
      analogWrite(enbA, 150);
      analogWrite(enbB, 185);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.println(" BACKWARD");
    }

    if(data[1] > 100 && data[1] < 125){
      //left
      analogWrite(enbA, 100);
      analogWrite(enbB, 135);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.println(" LEFT");
    }

    if(data[1] > 175 && data[1] < 200){
      //right             
      analogWrite(enbA, 100);
      analogWrite(enbB, 135);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      Serial.println(" RIGHT");
    }

    if(data[0] > 330 && data[0] < 360 && data[1] > 130 && data[1] < 160){
      //stop car
      analogWrite(enbA, 0);
      analogWrite(enbB, 0);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.println(" NEUTRAL");
    }
  }
}
