#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>
#include <Encoder.h>

#define LeftechoPin 2 
#define LefttrigPin 3 
#define RightechoPin 4 
#define RighttrigPin 5 

long LeftDuration;
int LeftDistance; 
long RightDuration; 
int RightDistance;

int LeftMotorPin = 6;
Encoder DriveEnc(7, 8);
Servo LeftMotor;

int RightMotorPin = 9;
Servo RightMotor;

int ArmMotorPin = 10;

int RollerMotorPin = 11;

int StraightAngle = 0;
MPU6050 mpu(Wire);
unsigned long timer = 0;

int dump = 0;

//bool STOP = true;
//int StopButton = 12;

void setup() {
  pinMode(LefttrigPin, OUTPUT); 
  pinMode(LeftechoPin, INPUT); 
  
  pinMode(RighttrigPin, OUTPUT); 
  pinMode(RightechoPin, INPUT); 
  
  pinMode(LeftMotorPin, OUTPUT);
  LeftMotor.attach(LeftMotorPin);
  
  pinMode(RightMotorPin, OUTPUT);
  RightMotor.attach(RightMotorPin);
  
  pinMode(ArmMotorPin, OUTPUT);

  pinMode(RollerMotorPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(200);

   Wire.begin();
 byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
 Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets(); // gyro and accelero
   Serial.println("Done!\n");
}

/////////////////// Main

void loop() {
  while (!Serial.available()){
    DriveControl(3);
  }
  DriveControl(0);
  
  String coordinates = Serial.readString();
  mpu.update();
  StraightAngle = mpu.getAngleZ();
  int i = coordinates.indexOf(',');
  int x = coordinates.substring(0, i).toInt();
  int y = coordinates.substring(i+1).toInt();
  
  if(x>0)
    Rotate(90);
  else if(x<0)
    Rotate(270);
  MoveDistance(x);
  
  if(y<0)
    Rotate(180);
  else
    Rotate(0);
  MoveDistance(y);
  
  digitalWrite(RollerMotorPin, HIGH);
  delay(5000);
  digitalWrite(RollerMotorPin, LOW);
  
  dump++;
  if(dump == 10)
    Dump();
  Serial.print("Done");
}

/////////////////////Functions

int DriveControl(int value){
    LeftMotor.writeMicroseconds(1500 + value*100);
    RightMotor.writeMicroseconds(1500 + value*100);
}
int Dump(){
  digitalWrite(RollerMotorPin, HIGH);
  while(analogRead(A0) < 500){}
  delay(2000);
  digitalWrite(RollerMotorPin, LOW);
}
int Rotate(int degrees){
  mpu.update();
  if(mpu.getAngleZ() - StraightAngle > degrees){
    LeftMotor.writeMicroseconds(1800);
    RightMotor.writeMicroseconds(-1800);
    while(true){
      mpu.update();
      if ((millis() - timer) > 10) { // print data every 10ms
        if(mpu.getAngleZ() > degrees+StraightAngle)
          break;
       timer = millis();
      }
    }
  }
  else if(mpu.getAngleZ()- StraightAngle < degrees){
    LeftMotor.writeMicroseconds(-1800);
    RightMotor.writeMicroseconds(1800);
    while(true){
      mpu.update();
      if ((millis() - timer) > 10) { // print data every 10ms
        if(mpu.getAngleZ() < degrees+StraightAngle)
          break;
       timer = millis();
      }
    }
  }
    DriveControl(0);
}
int MoveDistance(int dist){
  DriveEnc.write(0);
  DriveControl(3);
  while(DriveEnc.read()*10.3/360 < dist){}
    DriveControl(0);
}
int CheckSidwalk(){
  digitalWrite(LefttrigPin, LOW);
  digitalWrite(RighttrigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(LefttrigPin, HIGH);
  digitalWrite(RighttrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LefttrigPin, LOW);
  digitalWrite(RighttrigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  LeftDuration = pulseIn(LeftechoPin, HIGH);
  RightDuration = pulseIn(RightechoPin, HIGH);
  // Calculating the distance
  LeftDistance = LeftDuration * 0.034 / 2;
  RightDistance = RightDuration * 0.034 / 2;
  
  if(LeftDistance > 20 || LeftDistance < 30){
    Rotate(350);
    MoveDistance(10);
  }
  if(RightDistance > 20 || RightDistance < 30){
    Rotate(10);
    MoveDistance(10);
  }
}
//int STOP(){
//  STOP = true;
//  while(STOP){
//    if(digitalRead(StopButton) == HIGH){
//      STOP = false;
//    }
//  }
//}
