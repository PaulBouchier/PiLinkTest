#include <PiLinkMediator.h>

class TxLog;
class TxOdometry;
class RxDriveMotorsRqst;

PiLinkMediator::PiLinkMediator(
                              PiLink& piLink,
                              TxLog& txLog,
                              TxOdometry& txOdometry,
                              RxDriveMotorsRqst& rxDriveMotorsRqst)
  : piLink_(piLink)
  , txLog_(txLog)
  , txOdometry_(txOdometry)
  , rxDriveMotorsRqst_(rxDriveMotorsRqst)
{
  piLink.setMediator(this);
  rxDriveMotorsRqst_.setMediator(this);
}

void
PiLinkMediator::sendLogMsg(char* logMsg, int length)
{
  txLog_.post(logMsg, length);
}

void
PiLinkMediator::setDrive(int32_t seq, float linear_vel, float angular_vel)
{
  piLink_.linkLog_.traceln("PiLinkMediator got setDrive linear: %F angular: %F", linear_vel, angular_vel);
}