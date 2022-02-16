#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>

class TxPong
{
public:
  TxPong(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  // @brief Post a request to send a pong responding to pingType
  // @param pingType The type of ping received, which may trigger different pongs
  void post(uint8_t pingType)
  {
    pingType_ = pingType;
    tickCount_ = xTaskGetTickCount();
    pongTxPosted_ = true;
  }

  // @brief If a request to send a pong has been posted, send it
  bool sendPosted()
  {
    if (!pongTxPosted_)
      return true;

    bool isok = true;
    uint16_t sendSize = 0;
    sendSize += piXfer_.txObj(tickCount_, sendSize);
    sendSize = piXfer_.txObj(pingType_, sendSize);
    uint8_t sentSize = piXfer_.sendData(sendSize, pktIdPong);
    pongTxPosted_ = false;
    if (sentSize != sendSize)
    {
      Log.errorln("Failed to send correct # of bytes in TxPong");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  volatile TickType_t tickCount_;  
  bool pongTxPosted_ = false;
  uint8_t pingType_;
};

