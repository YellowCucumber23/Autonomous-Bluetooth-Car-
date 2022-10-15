/*[move.ino]
 * This program drives an autonomous car and disdplays the distance of the ultrasonic sensor on an LCD display
 * @author Adrian and Derek
 * @version 1.0
 * Date: December 3rd, 2021
 */


//Imports
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(8,9,10,11,12,13);  //Create LCD object

//Pins for Sensor
int trigPin = A4;
int echoPin = A5;

//Pin Setup Motor 1
int enablePin1 = 5;
int in1 = 7;
int in2 = 6;

//Pin Setup Motor 2
int enablePin2 = 3;
int in3 = 4;
int in4 = 2;

//Pin Setup Servo
int servoPin = A0;
Servo servoMotor;

//Variables for finding distance
float pingTime;
float targetDistance;
float speedOfSound = 0.034;  //cm per microseconds

//Storage variables
int leftDistance;
int rightDistance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Sensor Pins and LCD
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin, INPUT);

  //LCD set up
  LCD.begin(16,2);
  LCD.setCursor(0 ,0);
  LCD.print("Target Distance: ");

  //Motor Pin set up
  pinMode(enablePin1, OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //Servo Pin set up
  servoMotor.attach(servoPin);
  servoMotor.write(90);

}

void loop() {
  //
  LCD.setCursor(0 ,0);
  LCD.print("Target Distance: ");
  moveForward();
  getDistance();
  displayDistance("Target Distance: ");

  //When object is less than 30cm from car
  if (targetDistance <= 30){
    stopMoving();     //stop moving car
    delay(1000);
    servoMotor.write(0);   //turn servo right
    delay(1500);
    getDistance();    //get the right distance
    displayDistance("Right Distance: ");
    rightDistance = targetDistance;
    servoMotor.write(90);  //turn servo middle
    delay(750);
    servoMotor.write(180);  //turn motor left
    delay(1500);
    getDistance();   //get the left distance
    displayDistance("Left Distance: ");
    leftDistance = targetDistance;
    servoMotor.write(90);   //turn servo middle
    delay(750);
    moveBackward();  //move car backwards
    delay(100);
    stopMoving();   //stop moving car
    delay(250);

    //Turn right if right distance is greater than left distance
    if (leftDistance < rightDistance){
      Serial.println("Turning Right");
      turnRight();
      delay(360);
      stopMoving();
      delay(500);
    }

    //Turn left if left distance is greater than right distasnce
    else if (rightDistance < leftDistance){
      Serial.println("Turning Left");
      turnLeft();
      delay(360);
      stopMoving();
      delay(500);
    }
  }
}

/*getDistance()
 * This function gets the distance of an object by using the ultrasonic sensor
 */

void getDistance(){
  analogWrite(trigPin,0);   //Start ranging
  delayMicroseconds(2000);
  analogWrite(trigPin,1023);  //Send high pulse
  delayMicroseconds(15);
  analogWrite(trigPin,0);   //wait for highpulse to return
  delayMicroseconds(10);

  pingTime = pulseIn(echoPin,HIGH);  //measure time from the pulse

  targetDistance = speedOfSound * pingTime / 2; //find the distance from the object in cm
}

/*displayDistance()
 * This function displays the distance of an object on the LCD display
 * @param directionPrint is the direciton of the object relative to the car
 */
void displayDistance(String directionPrint){
  LCD.setCursor(0 ,0);
  LCD.print(directionPrint);
  LCD.setCursor(0, 1);
  LCD.print("                 ");
  LCD.setCursor(0, 1);
  LCD.print(targetDistance);
  LCD.print("cm");
}

/*stopMoving()
 * This function stops moving the car
 */
void stopMoving(){
  analogWrite(enablePin1,0);
  analogWrite(enablePin2,0);
}

/*moveForward()
 * This function moves the car forward
 */
void moveForward(){
  analogWrite(enablePin1,1020);
  analogWrite(enablePin2,1023);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

/*moveBackward()
 * This function moves the car backward
 */
void moveBackward(){
  analogWrite(enablePin1,1022);
  analogWrite(enablePin2,1023);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

/*turnRight()
 * This function turns the car right
 */
void turnRight(){
  analogWrite(enablePin1,1023);
  analogWrite(enablePin2,1023);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

/*turnLeft()
 * This function turns the car left
 */
void turnLeft(){
  analogWrite(enablePin1,1023);
  analogWrite(enablePin2,1023);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
