#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <ArduinoLog.h>
#include <SerialTransfer.h>
#include <messages/TxLog.h>
#include <messages/TxOdometry.h>
#include <messages/RxDriveMotorsRqst.h>
#include <messages/RxPing.h>

class PiLink
{
public:
  PiLink(HardwareSerial& linkSerial);

  // @brief initialize this object
  // @return True for success, Hangs in the funtion otherwise
  bool init(int logLevel, Stream* logStream=NULL);

  // @brief entry point for the PiLink task
  void run(void* params);

  SerialTransfer piXfer_;    // SerialTransfer object for communicating with Pi
  Logging linkLog_;
  void setMediator(Mediator* mediator) { mediator_ = mediator; }

private:
  HardwareSerial& linkSerial_;
  TaskHandle_t piLinkTaskHandle_ = NULL;
  Mediator* mediator_ = NULL;

  // private messages
};
