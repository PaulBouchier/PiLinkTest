#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>

class TxLog
{
public:
  TxLog(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  // @brief Post a request to send a log message over the link
  // @param log The null-terminated message to send
  void post(char* logMsg, int logLength)
  {
    tickCount_ = xTaskGetTickCount();
    logLength_ = logLength;
    buffp_ = logMsg;
    logTxPosted_ = true;
  }

  // @brief If a request to send a log has been posted, send it
  bool sendPosted()
  {
    if (!logTxPosted_)
      return true;

    bool isok = true;
    uint16_t sendSize = 0;
    sendSize += piXfer_.txObj(tickCount_);
    sendSize += piXfer_.txObj(*buffp_, sendSize, logLength_);
    uint8_t sentSize = piXfer_.sendData(sendSize, pktIdLog);
    logTxPosted_ = false;
    if (sentSize != sendSize)
    {
      Log.errorln("Failed to send correct # of bytes in TxLog");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  volatile TickType_t tickCount_;  
  bool logTxPosted_ = false;
  char* buffp_;
  int logLength_;
};

