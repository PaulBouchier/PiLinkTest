#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <Mediator.h>

class RxReboot
{
public:
  RxReboot(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  void handleReboot()
  {
    linkLog_.infoln("ESP32 REBOOTING in 5 SECONDS");
    delay(5000);
    // add reboot here
  }

  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  SerialTransfer& piXfer_;
  Logging& linkLog_;
  Mediator* mediator_ = NULL;
};

