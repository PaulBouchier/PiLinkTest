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
  rxDriveMotorsRqst_.setMediator(this);
}

void
PiLinkMediator::sendLogMsg(char* logMsg, int length)
{
  txLog_.post(logMsg, length);
}

void
PiLinkMediator::setDrive(int8_t leftDrivePct, int8_t rightDrivePct)
{
  piLink_.linkLog_.infoln("PiLinkMediator got setDrive left: %d right: %d", leftDrivePct, rightDrivePct);
}