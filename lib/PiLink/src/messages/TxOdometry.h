#pragma once

#include <Arduino.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>
#include <OdometryMsg.h>

class TxOdometry
{
public:
  TxOdometry(SerialTransfer& piXfer, Logging& linkLog)
    : piXfer_(piXfer)
    , linkLog_(linkLog)
  {}

  // @brief Post a request to send current odometry data
  // @param odom The odometry message
  void post(OdometryMsg odom)
  {
    odom_ = odom;
    odometryTxPosted_ = true;
  }

  // @brief If a request to send odometry has been posted, send it
  bool sendPosted()
  {
    if (!odometryTxPosted_)
      return true;

    bool isok = true;
    uint16_t sendSize = 0;
    sendSize = piXfer_.txObj(odom_);
    uint8_t sentSize = piXfer_.sendData(sendSize, pktIdOdometry);
    odometryTxPosted_ = false;
    if (sentSize != sendSize)
    {
      // Fixme: add logging this error
      linkLog_.errorln("Failed to send correct # of bytes in TxOdometry");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  volatile TickType_t tickCount_;  
  bool odometryTxPosted_ = false;
  OdometryMsg odom_;
  Logging& linkLog_;
};

