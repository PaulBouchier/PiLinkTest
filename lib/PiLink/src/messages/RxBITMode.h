#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <Mediator.h>

class RxBITMode
{
public:
  RxBITMode(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  void handleBITMode()
  {
    linkLog_.infoln("Sending SetBITMode request to RL500CommsTask");
    mediator_->setRL500BITMode();
  }

  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  SerialTransfer& piXfer_;
  Logging& linkLog_;
  Mediator* mediator_ = NULL;
};

