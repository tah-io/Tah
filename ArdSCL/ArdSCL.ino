/*
  TAH(http://tah.io) ArdSCL

  This sketch demonstrates the use of Tah App with board.
  Tah by default ships with this sketch preuploaded.

  Circuit:
  Plug in your Tah in USB port or power it up with external 5V power supply.

  Protocol:
  Tah protocol we use to communicate between the App and a Tah is basically a comma seprated string with end character "R".
  This protocol string is composed of 3 integer values with the end suffix "R" which represents end of string.

  1st Integer represents--> Pin Type:
  0 = DIGITAL,
  1 = ANALOG,
  2 = SERVO,
  3 = Send Analog Status,
  4 = Send Digital Status

  2nd Integer represents--> Pin No: From 2 to 13 for digital pins and 410 to 415 represents A0 to A5 analog pins
 
  3rd Integer represents--> Pin Value: 
  0 or 1 for Digital
  0 to 255 for Analog
  0 to 179 for Servo
 
  e.g: If we want to turn ON the default led attached to pin 13 then the protocol string would be => 0,13,1R

  Created Sep 2014
  by Dhiraj Jadhao

*/

#include <Servo.h>
#include <Tah.h>

TAH myTah;

int Pin_Type;    /* Stores Pin Type */
int Pin_No;      /* Stores Pin Number */
int Pin_Value;   /* Stores Pin Value */
int D2state, D3state, D4state, D5state, D6state, D7state, D8state, D9state,
  D10state, D11state, D12state, D13state;
int A0state, A1state, A2state, A3state, A4state, A5state;
int AppValueUpdateRate = 14;   /* minimum value: 14 milliseconds */

int Input_Buffer[11];
Servo myservo[12];

void setup()
{
  Serial.begin(9600);
  myTah.begin(9600);
  myTah.enterCommandMode();
  myTah.setName("Tah");
  myTah.setWorkRole(SLAVE);
  myTah.setAuth(OPEN);
  myTah.setWorkMode(REMOTE_CONTROL);
  myTah.setiBeaconMode(ON);

  myTah.exitCommandMode();

  for (int i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);

  for (int i = 2; i <= 13; i++)
    digitalWrite(i, LOW);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void loop(void)
{
  if (myTah.available()) {
    Pin_Type = myTah.parseInt();
    Pin_No = myTah.parseInt();
    Pin_Value = myTah.parseInt();
    Serial.print(Pin_Type);
    Serial.print(",");
    Serial.print(Pin_No);
    Serial.print(",");
    Serial.println(Pin_Value);

    if (myTah.read() == 'R') {
      /* Pin Type Digital  */
      if (Pin_Type == 0)
	digitalWrite(Pin_No, Pin_Value);
      else if (Pin_Type == 1)
	analogWrite(Pin_No, Pin_Value);
      else if (Pin_Type == 2) {
	myservo[Pin_No].attach(Pin_No);
	myservo[Pin_No].write(Pin_Value);
      }
      else if (Pin_Type == 3)
	updateAnalogstate();
      else if (Pin_Type == 4)
	updateDigitalstate();
    }
  }
}

void updateAnalogstate(void)
{
  /* Check Analog Pin Status  */
  A0state = analogRead(A0);
  A1state = analogRead(A1);
  A2state = analogRead(A2);
  A3state = analogRead(A3);
  A4state = analogRead(A4);
  A5state = analogRead(A5);

  /*  Update Analog Values  */
  myTah.print("A0:");
  myTah.println(A0state);
  delay(AppValueUpdateRate);

  myTah.print("A1:");
  myTah.println(A1state);
  delay(AppValueUpdateRate);

  myTah.print("A2:");
  myTah.println(A2state);
  delay(AppValueUpdateRate);

  myTah.print("A3:");
  myTah.println(A3state);
  delay(AppValueUpdateRate);

  myTah.print("A4:");
  myTah.println(A4state);
  delay(AppValueUpdateRate);

  myTah.print("A5:");
  myTah.println(A5state);
  delay(AppValueUpdateRate);

}

void updateDigitalstate(void)
{

  /* Check Digital Pin Status  */
  D2state = digitalRead(2);
  D3state = digitalRead(3);
  D4state = digitalRead(4);
  D5state = digitalRead(5);
  D6state = digitalRead(6);
  D7state = digitalRead(7);
  D8state = digitalRead(8);
  D9state = digitalRead(9);
  D10state = digitalRead(10);
  D11state = digitalRead(11);
  D12state = digitalRead(12);
  D13state = digitalRead(13);
  /*
    myTah.print("D");
    myTah.print(",");
    myTah.print(D2state);
    myTah.print(D3state);
    myTah.print(D4state);
    myTah.print(D5state);
    myTah.print(D6state);
    myTah.print(D7state);
    myTah.print(D8state);
    myTah.print(D9state);
    myTah.print(D10state);
    myTah.print(D11state);
    myTah.print(D12state);
    myTah.println(D13state);
  */


  /* Update Digital Values */

  myTah.print("D2:");
  myTah.println(D2state);
  delay(AppValueUpdateRate);

  myTah.print("D3:");
  myTah.println(D3state);
  delay(AppValueUpdateRate);

  myTah.print("D4:");
  myTah.println(D4state);
  delay(AppValueUpdateRate);

  myTah.print("D5:");
  myTah.println(D5state);
  delay(AppValueUpdateRate);

  myTah.print("D6:");
  myTah.println(D6state);
  delay(AppValueUpdateRate);

  myTah.print("D7:");
  myTah.println(D7state);
  delay(AppValueUpdateRate);

  myTah.print("D8:");
  myTah.println(D8state);
  delay(AppValueUpdateRate);

  myTah.print("D9:");
  myTah.println(D9state);
  delay(AppValueUpdateRate);

  myTah.print("D10:");
  myTah.println(D10state);
  delay(AppValueUpdateRate);

  myTah.print("D11:");
  myTah.println(D11state);
  delay(AppValueUpdateRate);

  myTah.print("D12:");
  myTah.println(D12state);
  delay(AppValueUpdateRate);

  myTah.print("D13:");
  myTah.println(D13state);
  delay(AppValueUpdateRate);
}
