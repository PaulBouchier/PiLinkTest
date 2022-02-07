#include <Arduino.h>
#include <PiLink.h>

PiLink piLink;


///////////////////////////////////////////////////////////////////

void handleRxMsg()
{
    uint8_t rxPacketId = piXfer.currentPacketID();

    Serial.print("Got a message ID: ");
    Serial.print(rxPacketId);
    Serial.print(" sending back msg len: ");
    Serial.println(piXfer.packet.bytesRead);

    for(uint16_t i=0; i < piXfer.packet.bytesRead; i++)
      piXfer.packet.txBuff[i] = piXfer.packet.rxBuff[i];
    
    piXfer.sendData(piXfer.packet.bytesRead, rxPacketId);
}

void setup()
{
  bool isok = true;

  Serial.begin(115200);
  delay(2000); // let serial start

  Log.begin(LOG_LEVEL_INFO, &Serial);
  Log.infoln("--- PiXfer Test ---");

  isok = piLink.init();
  if (!isok)
  {
    while(true)   // hang here forever if initialization fails
    {
      Log.fatalln("piXfer init() failed");
      delay(10000);
    }
  }

}


void loop()
{
  if (piXfer.tick())
  {
    Serial.println("piXfer.tick() received a message");
  }
  delay(500);
}