#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <ArduinoLog.h>
#include <SerialTransfer.h>

// Tx & Rx messages
#include <messages/TxLog.h>
#include <messages/TxOdometry.h>
#include <messages/TxPlatformData.h>

#include <messages/RxBITMode.h>
#include <messages/RxDriveMotorsRqst.h>
#include <messages/RxLogLevel.h>
#include <messages/RxPing.h>
#include <messages/RxReboot.h>

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
  UBaseType_t getStackHighWaterMark() { return uxTaskGetStackHighWaterMark(piLinkTaskHandle_);}

private:
  HardwareSerial& linkSerial_;
  TaskHandle_t piLinkTaskHandle_ = NULL;
  Mediator* mediator_ = NULL;

  // private messages
};
