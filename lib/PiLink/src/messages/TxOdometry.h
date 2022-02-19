#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>

struct WheelOdometry {
  float poseX_m;
  float poseY_m;
  float heading_rad;
  float speedX_mps;
  float speedY_mps;
  float linear_speed_mps;
  float angular_speed_rps;
  float odometer_m;
  float speedL_mps;
  float speedR_mps;
};

class TxOdometry
{
public:
  TxOdometry(SerialTransfer& piXfer)
    : piXfer_(piXfer)
  {}

  // @brief Post a request to send current odometry data
  // @param pingType The type of ping received, which may trigger different pongs
  void post(WheelOdometry wheelOdometry)
  {
    wheelOdometry_ = wheelOdometry;
    tickCount_ = xTaskGetTickCount();
    odometryTxPosted_ = true;
  }

  // @brief If a request to send a pong has been posted, send it
  bool sendPosted()
  {
    if (!odometryTxPosted_)
      return true;

    bool isok = true;
    uint16_t sendSize = 0;
    sendSize = piXfer_.txObj(wheelOdometry_, sendSize);
    uint8_t sentSize = piXfer_.sendData(sendSize, pktIdOdometry);
    odometryTxPosted_ = false;
    if (sentSize != sendSize)
    {
      Log.errorln("Failed to send correct # of bytes in TxOdometry");
      isok = false;
    }
    return isok;
  }

private:
  SerialTransfer& piXfer_;
  volatile TickType_t tickCount_;  
  bool odometryTxPosted_ = false;
  WheelOdometry wheelOdometry_;
};

