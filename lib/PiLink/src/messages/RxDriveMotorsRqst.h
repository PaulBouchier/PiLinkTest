#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <PiLink.h>
#include <RL500CommsTask.h>


class RxDriveMotorsRqst
{
public:
  RxDriveMotorsRqst(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  void handleDriveMotorsRqst()
  {
    uint16_t recSize = piXfer_.rxObj(leftDrivePct_);
    recSize += piXfer_.rxObj(rightDrivePct_, recSize);
    if (recSize != 2)
    {
      Log.errorln("Incorrect # of bytes received in RxDriveMotorsRqst: %d", recSize);
    }
    Log.traceln("received motors drive rqst: left %d right %d", leftDrivePct_, rightDrivePct_);
  }

private:
  SerialTransfer& piXfer_;
  uint8_t leftDrivePct_;         // drive percent request
  uint8_t rightDrivePct_;        // drive percent request
  
};

