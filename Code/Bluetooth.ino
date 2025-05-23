#include <PS4Controller.h>
void setup() 
{
  Serial.begin(115200);   //sets the baud rate for bluetooth communication
  Serial2.begin(9600, SERIAL_8N1, 16, 17);    //connects through serial connumication to the second arduino
  PS4.begin();    //Starts the PS4 Communication Library
}
void loop() 
{
  delay(100);
  Serial2.write(255);
  Serial2.write(254);
  Serial2.write(253);
  Serial2.write(252);
  Serial2.write(PS4.LStickX());
  Serial2.write(PS4.LStickY());
  Serial2.write(PS4.RStickX());
  Serial2.write(PS4.RStickY());
  Serial2.write(PS4.Square());
  Serial2.write(PS4.Cross());
  Serial2.write(PS4.Circle());
  Serial2.write(PS4.Triangle());
  Serial2.write(PS4.R2());
}
