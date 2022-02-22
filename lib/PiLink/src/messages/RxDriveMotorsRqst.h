#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <Mediator.h>
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
  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  SerialTransfer& piXfer_;
  int8_t leftDrivePct_;         // drive percent request
  int8_t rightDrivePct_;        // drive percent request
  
  Mediator* mediator_ = NULL;
};

