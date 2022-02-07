#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>

class RxPing
{
public:
  RxPing(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  uint8_t getPingType()
  {
    int recSize = piXfer_(pingType_, 1);
    Serial.print("received ping type ");
    Serial.println(pingType_);
  }

private:
  SerialTransfer piXfer_;
  uint8_t pingType_;         // flavors supported: 0 = return timestamp in pong
};

