#include <SD.h>

const int chipSelect = 10;

//motor pins
int m1_speed = A0;
int m1_forward = 2;
int m1_reverse = 3;

int m2_speed = A1;
int m2_forward = 4;
int m2_reverse = 5;

int m3_speed = A2;
int m3_forward = 6;
int m3_reverse = 7;

int m4_speed = A3;
int m4_forward = 8;
int m4_reverse = 9;

char command = '0';
char prev_command = '0';

void setup() {
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(chipSelect)) // see if the card is present and can be initialized:
  {
    Serial.println("Card failed, or not present");
    return;// don't do anything more
  }
  Serial.println("card initialized.");
  File dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) // if the file is available, write to it
  {
    dataFile.println("Test radio logging");
    dataFile.close();
  }else // if the file isn't open, pop up an error:
  {
    Serial.println("error opening data.csv");
    return;// don't do anything more
  }
  
  //initialize motor pins
  pinMode(m1_forward, OUTPUT);
  pinMode(m1_reverse, OUTPUT);
  pinMode(m2_forward, OUTPUT);
  pinMode(m2_reverse, OUTPUT);
  pinMode(m3_forward, OUTPUT);
  pinMode(m3_reverse, OUTPUT);
  pinMode(m4_forward, OUTPUT);
  pinMode(m4_reverse, OUTPUT);
}

void loop() {
  prev_command = command;
  if(Serial.available() > 0){
    command = Serial.read();
  }
  
  if(prev_command != command){
    File dataFile = SD.open("data.csv",FILE_WRITE);
    if (dataFile)
    {
      //Serial.println("Creative juices");
      dataFile.println(command);
      dataFile.close();

    }
    else 
    {
      Serial.println("error!");
    }
  }
  
  
  //use motor
  if(command == 'w'){
    m1Forward(130);
    m2Forward(130);
  }
  
  if(command == 's'){
    m1Reverse(130);
    m2Reverse(130);
  }
  
  if(command == 'd'){
    m3Forward(130);
    m4Forward(130);
  }
  
  if(command == 'a'){
    m3wReverse(130);
    m4Reverse(130);
  }
  
  delay(20);
  
  resetMotors();
  

}

void m1Forward(int motorSpeed){
  digitalWrite(m1_forward, HIGH);
  digitalWrite(m1_reverse, LOW);
  analogWrite(m1_speed, motorSpeed);
}

void m1Reverse(int motorSpeed){
  digitalWrite(m1_forward, LOW);
  digitalWrite(m1_reverse, HIGH);
  analogWrite(m1_speed, motorSpeed);
}

void m2Forward(int motorSpeed){
  digitalWrite(m2_forward, LOW);
  digitalWrite(m2_reverse, HIGH);
  analogWrite(m2_speed, motorSpeed);
}

void m2Reverse(int motorSpeed){
  digitalWrite(m2_forward, HIGH);
  digitalWrite(m2_reverse, LOW);
  analogWrite(m2_speed, motorSpeed);
}

void m3Forward(int motorSpeed){
  digitalWrite(m3_forward, HIGH);
  digitalWrite(m3_reverse, LOW);
  analogWrite(m3_speed, motorSpeed);
}

void m3Reverse(int motorSpeed){
  digitalWrite(m3_forward, LOW);
  digitalWrite(m3_reverse, HIGH);
  analogWrite(m3_speed, motorSpeed);
}

void m4Forward(int motorSpeed){
  digitalWrite(m4_forward, LOW);
  digitalWrite(m4_reverse, HIGH);
  analogWrite(m4_speed, motorSpeed);
}

void m4Reverse(int motorSpeed){
  digitalWrite(m4_forward, HIGH);
  digitalWrite(m4_reverse, LOW);
  analogWrite(m4_speed, motorSpeed);
}

void resetMotors(){
  digitalWrite(m1_forward, LOW);
  digitalWrite(m1_reverse, LOW);
  digitalWrite(m2_forward, LOW);
  digitalWrite(m2_reverse, LOW);
  digitalWrite(m3_forward, LOW);
  digitalWrite(m3_reverse, LOW);
  digitalWrite(m4_forward, LOW);
  digitalWrite(m4_reverse, LOW);
}
