#pragma once

#include <Mediator.h>
#include <PiLink.h>

class PiLink;
class TxLog;
class TxOdometry;
class RxDriveMotorsRqst;

class PiLinkMediator : public Mediator
{
public:
  PiLinkMediator(
                PiLink& piLink,
                TxLog& txLog,
                TxOdometry& txOdometry,
                RxDriveMotorsRqst& rxDriveMotorsRqst);
  void sendLogMsg(char* logMsg, int length);
  void setDrive(int32_t seq, float linear_vel, float angular_vel);

  // dummy defs to staisfy Mediator
  void setWheelDirections(bool leftFwd, bool rightFwd) {}
  void publishOdometry(OdometryMsg odom) {}
  void setLogLvl(int32_t pilinkLogLevel, int32_t rl500LogLevel, int32_t odomLogLevel) {}
  void publishPlatformData(PlatformDataMsg platformData) {}
  void setRL500BITMode() {}

private:
  PiLink& piLink_;
  TxLog& txLog_;
  TxOdometry& txOdometry_;
  RxDriveMotorsRqst& rxDriveMotorsRqst_;

};