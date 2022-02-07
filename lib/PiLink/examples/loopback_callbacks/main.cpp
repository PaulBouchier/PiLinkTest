#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <SerialTransfer.h>

HardwareSerial serial1(1);    // esp32 uart 1

SerialTransfer myTransfer;

void handleRxMsg();

/////////////////////////////////////////////////////////////////// Callbacks
void echo_cb()
{
  Serial.println("In echo_cb");
  Serial.print("packet bytesRead: ");
  Serial.print(myTransfer.packet.bytesRead);
  Serial.print(" SerialTransfer bytesRead: ");
  Serial.print(myTransfer.bytesRead);
  Serial.print(" packet status ");
  Serial.println(myTransfer.packet.status);
  handleRxMsg();
}

void list_cb()
{
  Serial.println("In list_cb");
  handleRxMsg();
}

// supplied as a reference - persistent allocation required
const functionPtr callbackArr[] = { echo_cb, list_cb };
///////////////////////////////////////////////////////////////////

void handleRxMsg()
{
    uint8_t rxPacketId = myTransfer.currentPacketID();

    Serial.print("Got a message ID: ");
    Serial.print(rxPacketId);
    Serial.print(" sending back msg len - one of the following two values: ");
    Serial.print(myTransfer.bytesRead);
    Serial.print(" ");
    Serial.println(myTransfer.packet.bytesRead);

    // send all received data back to Python
    //for(uint16_t i=0; i < myTransfer.bytesRead; i++)
    //  myTransfer.packet.txBuff[i] = myTransfer.packet.rxBuff[i];

    for(uint16_t i=0; i < myTransfer.packet.bytesRead; i++)
      myTransfer.packet.txBuff[i] = myTransfer.packet.rxBuff[i];
    
    //myTransfer.sendData(myTransfer.bytesRead, rxPacketId);
    myTransfer.sendData(myTransfer.packet.bytesRead, rxPacketId);
}

void setup()
{
  Serial.begin(115200);
  serial1.begin(115200);
  delay(2000); // let serial start

  ///////////////////////////////////////////////////////////////// Config Parameters
  configST myConfig;
  myConfig.debug        = false;
  myConfig.callbacks    = callbackArr;
  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);
  /////////////////////////////////////////////////////////////////
  
  myTransfer.begin(serial1, myConfig);
  //myTransfer.begin(serial1);

  Serial.println("SerialTransfer Loopback Test");
}


void loop()
{
  if (myTransfer.tick())
  //if (myTransfer.available() > 0)
  {
    Serial.println("myTransfer.tick() received a message");
    //handleRxMsg();
  }
  delay(500);
}