#include <messages/RxDriveMotorsRqst.h>

extern PiLink piLink;

void
RxDriveMotorsRqst::handleDriveMotorsRqst()
{
  uint16_t recSize = piXfer_.rxObj(seq_);
  recSize = piXfer_.rxObj(linear_vel_, recSize);
  recSize = piXfer_.rxObj(angular_vel_, recSize);
  if (recSize != 12)
  {
    piLink.linkLog_.errorln("Incorrect # of bytes received in RxDriveMotorsRqst: %d", recSize);
  }
  piLink.linkLog_.traceln("handleDriveMotorsRqst got motors drive rqst: seq %d left %f right %f", seq_, linear_vel_, angular_vel_);
  mediator_->setDrive(seq_, linear_vel_, angular_vel_);
}

