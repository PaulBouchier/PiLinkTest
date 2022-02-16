#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <SerialTransfer.h>
#include <messages/RxPing.h>
#include <messages/TxLog.h>

class PiLink
{
public:
  PiLink(HardwareSerial& linkSerial);

  // @brief initialize this object
  // @return True for success, False otherwise
  bool init();

  // @brief entry point for the PiLink task
  void run(void* params);

  SerialTransfer piXfer_;                         // SerialTransfer object for communicating with Pi

private:
  HardwareSerial& linkSerial_;

  // private messages
};
