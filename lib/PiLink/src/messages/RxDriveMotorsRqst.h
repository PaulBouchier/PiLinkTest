#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include "../../../src/PiLinkMediator.h"
#include <PiLink.h>

class Mediator;

class RxDriveMotorsRqst
{
public:
  RxDriveMotorsRqst(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  void handleDriveMotorsRqst();
  void setMediator(Mediator* mediator);

private:
  SerialTransfer& piXfer_;
  uint8_t leftDrivePct_;         // drive percent request
  uint8_t rightDrivePct_;        // drive percent request
  
  Mediator* mediator_ = NULL;
};

