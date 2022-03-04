#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <Mediator.h>


class RxLogLevel
{
public:
  RxLogLevel(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  void handleLogLevel()
  {
    uint16_t recSize = 0;

    recSize = piXfer_.rxObj(pilinkLogLevel_, recSize);
    recSize = piXfer_.rxObj(rl500LogLevel_, recSize);
    recSize = piXfer_.rxObj(odomLogLevel_, recSize);
    linkLog_.infoln("Set log levels to: piLink: %d, rl500: %d, odom: %d", pilinkLogLevel_, rl500LogLevel_, odomLogLevel_);
    mediator_->setLogLvl(pilinkLogLevel_, rl500LogLevel_, odomLogLevel_);
  }

  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  SerialTransfer& piXfer_;
  Logging& linkLog_;
  Mediator* mediator_ = NULL;

  int32_t pilinkLogLevel_;
  int32_t rl500LogLevel_;
  int32_t odomLogLevel_;

  
};

