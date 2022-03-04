#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <Mediator.h>
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
  Mediator* mediator_ = NULL;

  int seq_;
  float linear_vel_;
  float angular_vel_;
};

