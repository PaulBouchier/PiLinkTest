#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <messages/TxPong.h>

extern TxPong txPong;

class RxPing
{
public:
  RxPing(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  void handlePing()
  {
    uint16_t recSize = piXfer_.rxObj(pingType_);
    if (recSize != 1)
    {
      Log.errorln("Incorrect # of bytes in RxPing: %d", recSize);
    }
    txPong.post(pingType_);
  }

private:
  SerialTransfer& piXfer_;
  uint8_t pingType_;         // flavors supported: 0 = return timestamp in pong
  
};

