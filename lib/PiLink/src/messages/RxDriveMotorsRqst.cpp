#include <messages/RxDriveMotorsRqst.h>

extern PiLink piLink;

void
RxDriveMotorsRqst::handleDriveMotorsRqst()
{
  uint16_t recSize = piXfer_.rxObj(leftDrivePct_);
  recSize = piXfer_.rxObj(rightDrivePct_, recSize);
  if (recSize != 2)
  {
    piLink.linkLog_.errorln("Incorrect # of bytes received in RxDriveMotorsRqst: %d", recSize);
  }
  piLink.linkLog_.infoln("handleDriveMotorsRqst got motors drive rqst: left %d right %d", leftDrivePct_, rightDrivePct_);
  mediator_->setDrive(leftDrivePct_, rightDrivePct_);
}

