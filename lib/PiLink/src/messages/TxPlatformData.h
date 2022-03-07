#pragma once

#include <Arduino.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>
#include <PlatformDataMsg.h>

class TxPlatformData
{
public:
  TxPlatformData(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  // @brief Post a request to send current platform hardware data
  // @param platformHw The platform hardware message
  void post(PlatformDataMsg platformData)
  {
    platformDataMsg_ = platformData;
    platformDataTxPosted_ = true;
  }

  // @brief If a request to send odometry has been posted, send it
  bool sendPosted()
  {
    if (!platformDataTxPosted_)
      return true;

    bool isok = true;
    uint16_t sendSize = 0;
    sendSize = piXfer_.txObj(platformDataMsg_);
    uint8_t sentSize = piXfer_.sendData(sendSize, pktIdPlatformData);
    platformDataTxPosted_ = false;
    if (sentSize != sendSize)
    {
      linkLog_.errorln("Failed to send correct # of bytes in TxPlatformData");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  bool platformDataTxPosted_ = false;
  PlatformDataMsg platformDataMsg_;
  Logging& linkLog_;
};

