#pragma once

#include <PiLink.h>

class PiLink;
class TxLog;
class TxOdometry;
class RxDriveMotorsRqst;

class Mediator
{
public:
  virtual void sendLogMsg(char* logMsg, int length) = 0;
  virtual void setDrive(int8_t leftDrivePct, int8_t rightDrivePct) = 0;
};

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

private:
  PiLink& piLink_;
  TxLog& txLog_;
  TxOdometry& txOdometry_;
  RxDriveMotorsRqst& rxDriveMotorsRqst_;

};