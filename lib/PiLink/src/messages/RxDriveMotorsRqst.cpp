#include <messages/RxDriveMotorsRqst.h>

void
RxDriveMotorsRqst::handleDriveMotorsRqst()
{
  uint16_t recSize = piXfer_.rxObj(leftDrivePct_);
  recSize = piXfer_.rxObj(rightDrivePct_, recSize);
  if (recSize != 2)
  {
    Log.errorln("Incorrect # of bytes received in RxDriveMotorsRqst: %d", recSize);
  }
  Log.infoln("received motors drive rqst: left %d right %d", leftDrivePct_, rightDrivePct_);
  mediator_->setDrive(leftDrivePct_, rightDrivePct_);
}

void
RxDriveMotorsRqst::setMediator(Mediator* mediator)
{
  mediator_ = mediator;
}

