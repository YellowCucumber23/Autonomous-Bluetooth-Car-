#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(8,9,10,11,12,13);

//Pins for Sensor
int trigPin = A5;
int echoPin = A4;

//Pin Setup Motor 1
int enablePin1 = 6;
int in1 = 7;
int in2 = 5;

//Pin Setup Motor 2
int enablePin2 = 3;
int in3 = 4;
int in4 = 2;

//Pin Setup Servo
int servoPin = A0;
Servo servoMotor; 

float pingTime;
float targetDistance;
float speedOfSound = 0.034;  //cm per microseconds

int leftDistance;
int rightDistance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Sensor Pins and LCD
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);
  LCD.begin(16,2);
  LCD.setCursor(0,0);
  LCD.print("Target Distance: ");

  //Motor Pins
  pinMode(enablePin1, OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //Servo Pin
  servoMotor.attach(servoPin);
  servoMotor.write(90);

}

void loop() {
  // put your main code here, to run repeatedly:
  getDistance();

  //Spin Servor Motor
  if(targetDistance <= 30){
    stopMoving();
    delay(1000);
    moveBackward();
    delay(1000);
    stopMoving();
    servoMotor.write(0);
    delay(2000);
    getDistance();
    rightDistance = targetDistance;
    servoMotor.write(180);
    delay(2000);
    getDistance();
    leftDistance = targetDistance;
    servoMotor.write(90);
    delay(250);
    if(rightDistance > leftDistance){
      turnLeft();
      delay(2000);
    }else{
      turnRight();
      delay(2000);
    }
    delay(1000);
    moveForward();
  }

  moveForward();
}

void getDistance(){
  analogWrite(trigPin,0);   //Start ranging
  delayMicroseconds(2000);
  analogWrite(trigPin,1023);  //Send high pulse
  delayMicroseconds(15);
  analogWrite(trigPin,0);   //wait for highpulse to return
  delayMicroseconds(10);

  pingTime = pulseIn(echoPin,HIGH);  //measure time from the pulse

  targetDistance = speedOfSound * pingTime / 2; //find the distance from the object in cm
  LCD.setCursor(0,1);         //Output distance to LCD screen
  LCD.print("            ");
  LCD.setCursor(0,1);
  LCD.print(targetDistance);
  LCD.print(" cm");
}


void stopMoving(){
  analogWrite(enablePin1,LOW);
  analogWrite(enablePin2,LOW);
}

void moveForward(){
  analogWrite(enablePin1,HIGH);
  analogWrite(enablePin2,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void moveBackward(){
  analogWrite(enablePin1,HIGH);
  analogWrite(enablePin2,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void turnRight(){
  analogWrite(enablePin1,HIGH);
  analogWrite(enablePin2,50);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void turnLeft(){
  analogWrite(enablePin1,50);
  analogWrite(enablePin2,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
