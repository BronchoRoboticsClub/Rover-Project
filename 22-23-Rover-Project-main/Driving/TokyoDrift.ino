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
#define num 64
int Lpower, Rpower;
int8_t LStickX, LStickY, RStickX, RStickY, Cross, Circle, Square, Triangle, RTrigger;
int deadZone = 20, endZone = 140, magL, magR, center = 90, driveMode = 2;
double degreeL, degreeR;
byte inputs[num] = {};
byte header[4] = {255, 254, 253, 252};

void TokyoDrift()
{
  if (LStickY >= 0)
  {
    digitalWrite(FrontLeftMotorDirection, HIGH);
    digitalWrite(MiddleLeftMotorDirection, HIGH);
    digitalWrite(BackLeftMotorDirection, HIGH);
    digitalWrite(FrontRightMotorDirection, HIGH);
    digitalWrite(MiddleRightMotorDirection, HIGH);
    digitalWrite(BackRightMotorDirection, HIGH);
  }
  else
  {
    digitalWrite(FrontLeftMotorDirection, LOW);
    digitalWrite(MiddleLeftMotorDirection, LOW);
    digitalWrite(BackLeftMotorDirection, LOW);
    digitalWrite(FrontRightMotorDirection, LOW);
    digitalWrite(MiddleRightMotorDirection, LOW);
    digitalWrite(BackRightMotorDirection, LOW);
  }
  if (RTrigger == 1)
  {
    Lpower = (Lpower / 2);
    Rpower = (Rpower / 2);
  }
  Lpower = magL;
  Rpower = magL;
  analogWrite(FrontLeftMotorPower, abs(Lpower));
  analogWrite(MiddleLeftMotorPower, abs(Lpower));
  analogWrite(BackLeftMotorPower, abs(Lpower));
  analogWrite(FrontRightMotorPower, abs(Rpower));
  analogWrite(MiddleRightMotorPower, abs(Rpower));
  analogWrite(BackRightMotorPower, abs(Rpower));
  int angle;
  if (LStickY >= 0)
  {
    angle = map(LStickX, -255, 255, 0, 180);
  }
  else
  {
    angle = map(LStickX, -255, 255, 180, 0);
  }
  digitalWrite(FrontLeftServo, angle);
  digitalWrite(MiddleLeftServo, angle);
  digitalWrite(BackLeftServo, angle);
  digitalWrite(FrontRightServo, angle);
  digitalWrite(MiddleRightServo, angle);
  digitalWrite(BackRightServo, angle);
}

void JoystickZones()
{
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
  Serial.begin(9600);
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
    int numBytes = Serial.readBytes(inputs, Serial.available());
    int h = 0;
    int i;
    for (i = 0; i < numBytes; i++)
    {
      if (inputs[i] == header[h])
      {
        if (h == 3)
        {
          i++;
          break;
        }
        h++;
      }
      else
      {
        h = 0;
      }
    }
    if (i < numBytes - 3)
    {
      LStickX = inputs[i];
      LStickY = inputs[i + 1];
      RStickX = inputs[i + 2];
      RStickY = inputs[i + 3];
      Cross = inputs[i + 4];
      Square = inputs[i + 5];
      Circle = inputs[i + 6];
      Triangle = inputs[i + 7];
      RTrigger = inputs[i + 8];
      LStickX = map(LStickX, 0, 1024, -255, 255);
      LStickY = map(LStickY, 0, 1024, -255, 255);
      RStickX = map(RStickX, 0, 1024, -255, 255);
      RStickY = map(RStickY, 0, 1024, -255, 255);
      Serial.flush();
    }
  }
  JoystickZones();
  magL = sqrt(sq(LStickX) + sq(LStickY));
  magR = sqrt(sq(RStickX) + sq(RStickY));
  degreeL = atan(LStickY / LStickX);
  degreeR = atan(RStickY / RStickX);
  TokyoDrift();
}
