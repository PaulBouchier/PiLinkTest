#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <Mediator.h>


class RxClearOdom
{
public:
  RxClearOdom(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  void handleClearOdom()
  {
    uint16_t recSize = 0;
    uint32_t dummy = 0;

    recSize = piXfer_.rxObj(dummy, recSize);
    linkLog_.infoln("Clearing odometry");
    mediator_->clearOdometry();
  }

  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  SerialTransfer& piXfer_;
  Logging& linkLog_;
  Mediator* mediator_ = NULL;
};

