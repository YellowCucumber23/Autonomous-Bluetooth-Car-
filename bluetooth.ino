/*[bluetootht.ino]
 * This program uses RemoteXY to drive a car using bluetooth
 * @author Adrian and Derek
 * @version 1.0
 * Date: December 3rd, 2021
 */

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__HARDSERIAL

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
{ 255, 4, 0, 0, 0, 39, 0, 13, 13, 0,
  5, 32, 34, 23, 30, 30, 2, 26, 31, 1,
  0, 77, 7, 12, 12, 2, 31, 82, 105, 103,
  104, 116, 0, 1, 0, 11, 7, 12, 12, 2,
  31, 76, 101, 102, 116, 0
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  int8_t moveStick_x; // =-100..100 x-coordinate joystick position
  int8_t moveStick_y; // =-100..100 y-coordinate joystick position
  uint8_t rightButton; // =1 if button pressed, else =0
  uint8_t leftButton; // =1 if button pressed, else =0

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
//Pin Setup Motor 1
int enablePin1 = 5;
int in1 = 7;
int in2 = 6;

//Pin Setup Motor 2
int enablePin2 = 3;
int in3 = 4;
int in4 = 2;


void setup()
{
  RemoteXY_Init ();

  // TODO you setup code

  //Motor pin set up
  pinMode(enablePin1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{
  RemoteXY_Handler ();

  //move car forward first
  moveForward(RemoteXY.moveStick_y);

  //If left button is pressed, turn the car left
  if (RemoteXY.leftButton == 1) {
    turnLeft();
  } else if (RemoteXY.rightButton == 1) {   //If right button is pressed turn the car right
    turnRight();
  }

  if (RemoteXY.moveStick_y > 0) {     //If the stick is forward, move car forward
    moveForward(RemoteXY.moveStick_y);
  } else if (RemoteXY.moveStick_y < 0) {  //If stick is abckward, move car backward
    moveBackward(abs(RemoteXY.moveStick_y));
  }
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay()

}

/*moveForward
 * This function moves the car forward at a specified speed
 * @param zoom The speed of the car
 */
void moveForward(int zoom) {
  analogWrite(enablePin1, zoom * 2.5);
  analogWrite(enablePin2, zoom * 2.5);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

/*moveBackward
 * This function moves the car backward at a specified speed
 * @param zoom The speed of the car
 */
void moveBackward(int zoom) {
  analogWrite(enablePin1, zoom * 2.5);
  analogWrite(enablePin2, zoom * 2.5);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/*turnRight
 * This function turns the car right
 */
void turnRight() {
  analogWrite(enablePin1, 1023);
  analogWrite(enablePin2, 1023);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

/*turnLeft
 * This function turns the car left
 */
void turnLeft() {
  analogWrite(enablePin1, 1023);
  analogWrite(enablePin2, 1023);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
