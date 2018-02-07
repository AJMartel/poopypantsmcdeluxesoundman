#include <Wire.h>
#include <SoftSerial.h>
//OLED
//#include "DigisparkOLED_light.h"
//#include "font8x16.h"

//MP3 Settings
SoftSerial mySerial(1, 3);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

const int buttonPin = 0;
int buttonState = 0;

void setup() {
  //OLED
  //oled.begin();
  //MP3
  mySerial.begin(9600);
  delay(1000);
  //playFirst();
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}


uint8_t i = 0;
short int t = 30;

void loop() {
  /*
    //Get vol
    execute_CMD(0x43, 0, 0);
    delay(500);
    while (mySerial.available() > 0) {
    oled.print(mySerial.read());
    oled.print(" ");
    }
  */
  digitalWrite(1, HIGH);
  delay(1000);               // wait for a second
  //digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(1, LOW); 
  delay(1000); 
  //oled.println(F("Tiny85 MP3 Player"));
  //oled.print(F("\nPlaying Track "));
  //oled.println(i + 1);
//  while (t > 0) {
//  //digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
//  digitalWrite(1, HIGH);
//  delay(1000);               // wait for a second
//  //digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
//  digitalWrite(1, LOW); 
//  delay(1000); 
//    //delay(1000);
//    //oled.setCursor(18, 4);
//    //oled.print("\n     ");
//    delay(1);
//    t--;
//  }
  //oled.fill(0x00);
    buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    playNext();
    //digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    //digitalWrite(ledPin, LOW);
    int hold = 1;
  }
  //playNext();
//  t = 30;
//  if (i < 2) {
//    i++;
//  } else {
//    i = 0;
//  }
}

void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(500);
  setVolume(30);
  delay(500);
  execute_CMD(0x11, 0, 1);
  delay(500);
}

void pause()
{
  execute_CMD(0x0E, 0, 0);
  delay(500);
}

void play()
{
  execute_CMD(0x0D, 0, 1);
  delay(500);
}

void playNext()
{
  execute_CMD(0x01, 0, 1);
  delay(500);
}

void playPrevious()
{
  execute_CMD(0x02, 0, 1);
  delay(500);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                            Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
                          };
  //Send the command line to the module
  for (byte k = 0; k < 10; k++)
  {
    mySerial.write( Command_line[k]);
  }
}
