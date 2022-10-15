//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX A1
#define REMOTEXY_SERIAL_TX A0
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,5,0,0,0,47,0,13,13,0,
  5,32,34,15,30,30,2,26,31,1,
  0,77,4,12,12,2,31,82,105,103,
  104,116,0,1,0,12,4,12,12,2,
  31,76,101,102,116,0,4,128,41,53,
  18,7,2,26 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t moveStick_x; // =-100..100 x-coordinate joystick position 
  int8_t moveStick_y; // =-100..100 y-coordinate joystick position 
  uint8_t rightButton; // =1 if button pressed, else =0 
  uint8_t leftButton; // =1 if button pressed, else =0 
  int8_t speedControl; // =0..100 slider position 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
#include <AFMotor.h>
AF_DCMotor motor1(2, MOTOR12_64KHZ);
AF_DCMotor motor2 (3, MOTOR34_64KHZ);
char command;


void setup() 
{
  RemoteXY_Init (); 
  
  
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  command = bt.read();
  motor1.setSpeed(RemoteXY.speedControl * 2.5);
  motor2.setSpeed(RemoteXY.speedControl * 2.5);
  if (RemoteXY.rightButton == 1){
    right();
  }

  if(RemoteXY.leftButton == 1){
    left();
  }

  
  
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}

void forward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
void backward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}
void left(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}
void right(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}
