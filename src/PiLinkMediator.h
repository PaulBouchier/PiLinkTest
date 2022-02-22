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
  void setDrive(int8_t leftDrivePct, int8_t rightDrivePct);

  // dummy defs to staisfy Mediator
  void setWheelDirections(bool leftFwd, bool rightFwd) {}
  void publishOdometry(OdometryMsg odom) {}

private:
  PiLink& piLink_;
  TxLog& txLog_;
  TxOdometry& txOdometry_;
  RxDriveMotorsRqst& rxDriveMotorsRqst_;

};