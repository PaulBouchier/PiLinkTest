#pragma once

#include <Arduino.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>
#include <OdometryMsg.h>

class TxOdometry
{
public:
  TxOdometry(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  // @brief Post a request to send current odometry data
  // @param pingType The type of ping received, which may trigger different pongs
  void post(OdometryMsg odom)
  {
    odom_ = odom;
    odometryTxPosted_ = true;
  }

  // @brief If a request to send a pong has been posted, send it
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
      Serial.println("Failed to send correct # of bytes in TxOdometry");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  volatile TickType_t tickCount_;  
  bool odometryTxPosted_ = false;
  OdometryMsg odom_;
};

