#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <SerialTransfer.h>

HardwareSerial serial1(1);    // esp32 uart 1

SerialTransfer myTransfer;

double y;


void setup()
{
  Serial.begin(115200);
  serial1.begin(115200);
  delay(2000); // let serial start
  myTransfer.begin(serial1);

  y = 4.5;
  Serial.println("SerialTransferTest");
}


void loop()
{
  myTransfer.sendDatum(y);
  delay(500);
}