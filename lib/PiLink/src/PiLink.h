#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <SerialTransfer.h>
#include <messages/RxPing.h>

class PiLink
{
public:
  PiLink();

  // @brief initialize this object
  // @return True for success, False otherwise
  bool init();

  // @brief entry point for the PiLink task
  void run(void* params);

private:
HardwareSerial serial1 = HardwareSerial(1);     // esp32 uart 1
SerialTransfer piXfer;                          // SerialTransfer object for communicating with Pi

// messages
RxPing rxPing_;

};