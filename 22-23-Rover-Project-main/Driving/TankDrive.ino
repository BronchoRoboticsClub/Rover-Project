//Define the motors and servos to their respective pins
#define FrontRightMotorPower 6
#define MiddleRightMotorPower 12
#define BackRightMotorPower 9
#define FrontLeftMotorPower 3
#define MiddleLeftMotorPower 12
#define BackLeftMotorPower 5
#define FrontRightMotorDirection 7
#define MiddleRightMotorDirection 12
#define BackRightMotorDirection 8
#define FrontLeftMotorDirection 2
#define MiddleLeftMotorDirection 12
#define BackLeftMotorDirection 4
#define FrontRightServo 12
#define MiddleRightServo 12
#define BackRightServo 12
#define FrontLeftServo 12
#define MiddleLeftServo 12
#define BackLeftServo 12
#define num 64    //Sets the varible num to a maximum number
int Lpower, Rpower;   //Initializes the Left Power and Right Power variable for drive motor powers
int8_t LStickX, LStickY, RStickX, RStickY, Cross, Circle, Square, Triangle, RTrigger; //Creates a signed byte for all inputs from the controller
int deadZone = 20, endZone = 140, center = 90;    //Creates varibles for various code uses
byte inputs[num] = {};    //Creates an array for the input variables coming from the controller
byte header[4] = {255, 254, 253, 252};    //Creates a header
//The headers purpose is to locate and varify the correct block of inputs and will be removed later
void TankDrive()    //Function definition which can be referenced in the main code
{
  //Centers all the servos to 90 degrees
  digitalWrite(FrontLeftServo, center);
  digitalWrite(MiddleLeftServo, center);
  digitalWrite(BackLeftServo, 180 - center);
  digitalWrite(FrontRightServo, center);
  digitalWrite(MiddleRightServo, center);
  digitalWrite(BackRightServo, 180 - center);
  if (LStickY >= 0)     //If the left joystick is above the x-axis
  {
    //Sets the left motors direction to forwards
    digitalWrite(FrontLeftMotorDirection, HIGH);
    digitalWrite(MiddleLeftMotorDirection, HIGH);
    digitalWrite(BackLeftMotorDirection, HIGH);
  }
  else    //If the left joystick is not above the x-axis
  {
    //Sets the left motors direction to backwards
    digitalWrite(FrontLeftMotorDirection, LOW);
    digitalWrite(MiddleLeftMotorDirection, LOW);
    digitalWrite(BackLeftMotorDirection, LOW);
  }
  
  if (RStickY >= 0)   //If the right joystick above the x-axis
  {
    //Sets the right motors direction to forwards
    digitalWrite(FrontRightMotorDirection, HIGH);
    digitalWrite(MiddleRightMotorDirection, HIGH);
    digitalWrite(BackRightMotorDirection, HIGH);
  }
  else    //If the right joystick is not above the x-axis
  {
    //Sets the right motors direction to backwards
    digitalWrite(FrontRightMotorDirection, LOW);
    digitalWrite(MiddleRightMotorDirection, LOW);
    digitalWrite(BackRightMotorDirection, LOW);
  }
  Lpower = abs(LStickY);   //Sets the left motor power varriable to the value y component of the left joystick
  Rpower = abs(RStickY);   //Sets the right motor power varriable to the value y component of the right joystick
  if (RTrigger == 1)    //Checks to see if the R2 or the Right Trigger is depressed
  {
    //Halves the motors power. Also refered to as "snail mode"
    Lpower = (Lpower / 2);
    Rpower = (Rpower / 2);
  }
  //Sets the left side motors equal to the left power varriable
  analogWrite(FrontLeftMotorPower, abs(Lpower));
  analogWrite(MiddleLeftMotorPower, abs(Lpower));
  analogWrite(BackLeftMotorPower, abs(Lpower));
  //Sets the right side motors equal to the right power varriable
  analogWrite(FrontRightMotorPower, abs(Rpower));
  analogWrite(MiddleRightMotorPower, abs(Rpower));
  analogWrite(BackRightMotorPower, abs(Rpower));
}

void JoystickZones()    //The function definition for correcting the joysticks
{
  //Finds if the joystick is within the deadzone range to set to 0
  if (LStickX <= deadZone && LStickX >= -deadZone) {
    LStickX = 0;
  }
  if (LStickY <= deadZone && LStickY >= -deadZone) {
    LStickY = 0;
  }
  if (RStickX <= deadZone && RStickX >= -deadZone) {
    RStickX = 0;
  }
  if (RStickY <= deadZone && RStickY >= -deadZone) {
    RStickY = 0;
  }
//Finds if the joystick is within the endzone or largest range to set to max power
  if (LStickX > endZone) {
    LStickX = 255;
  }
  if (LStickY > endZone) {
    LStickY = 255;
  }
  if (RStickX > endZone) {
    RStickX = 255;
  }
  if (RStickY > endZone) {
    RStickY = 255;
  }

  if (LStickX < -endZone) {
    LStickX = -255;
  }
  if (LStickY < -endZone) {
    LStickY = -255;
  }
  if (RStickX < -endZone) {
    RStickX = -255;
  }
  if (RStickY < -endZone) {
    RStickY = -255;
  }
}

void setup()
{
  Serial.begin(9600);   //Sets the baud rate to 9600 which is typical for arduino
  //declares the pinMode for the motors and servos
  pinMode(FrontRightMotorPower, OUTPUT);
  pinMode(MiddleRightMotorPower, OUTPUT);
  pinMode(BackRightMotorPower, OUTPUT);
  pinMode(FrontLeftMotorPower, OUTPUT);
  pinMode(MiddleLeftMotorPower, OUTPUT);
  pinMode(BackLeftMotorPower, OUTPUT);
  pinMode(FrontRightMotorDirection, OUTPUT);
  pinMode(MiddleRightMotorDirection, OUTPUT);
  pinMode(BackRightMotorDirection, OUTPUT);
  pinMode(FrontLeftMotorDirection, OUTPUT);
  pinMode(MiddleLeftMotorDirection, OUTPUT);
  pinMode(BackLeftMotorDirection, OUTPUT);
  pinMode(FrontRightServo, OUTPUT);
  pinMode(MiddleRightServo, OUTPUT);
  pinMode(BackRightServo, OUTPUT);
  pinMode(FrontLeftServo, OUTPUT);
  pinMode(MiddleLeftServo, OUTPUT);
  pinMode(BackLeftServo, OUTPUT);
}

void loop()
{
  if (Serial.available() > 8)
  {
    int numBytes = Serial.readBytes(inputs, Serial.available());    //Finds the data size of the serial communication
    int h = 0;    //creates a temporary variable for tracking header
    int i;    //creates a temporary variable for tracking the placement in the input array
    for (i = 0; i < numBytes; i++)    //Loops through the array of inputs checking each placement
    {
      if (inputs[i] == header[h])   //If the current value is equal to the header value
      {
        if (h == 3) //If its the last header value
        {
          i++;    //Increment i
          break;    // leave the loop
        }
        h++;    //If not at last header increase header placement
      }
      else //If it fails to collect the header in the right order
      {
        h = 0;    //resets header placement
      }
    }
    if (i < numBytes - 3)   //If there is data collected after the header is removed
    {
      //Sets each varible equal to the correct placement in the input array
      LStickX = inputs[i];
      LStickY = inputs[i + 1];
      RStickX = inputs[i + 2];
      RStickY = inputs[i + 3];
      Cross = inputs[i + 4];
      Square = inputs[i + 5];
      Circle = inputs[i + 6];
      Triangle = inputs[i + 7];
      RTrigger = inputs[i + 8];
      //Changes the joystick value for -128 through 128 to -255 through 255
      LStickX = map(LStickX, -128, 128, -255, 255);
      LStickY = map(LStickY, -128, 128, -255, 255);
      RStickX = map(RStickX, -128, 128, -255, 255);
      RStickY = map(RStickY, -128, 128, -255, 255);
      Serial.flush();   //Clears the serial communication for a new set of data
    }
  }
  JoystickZones();    //calls the joystick setting function for correcting values
  TankDrive();    //Runs the drive funciton
}
