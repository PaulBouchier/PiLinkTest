#include <ArduinoLog.h>
#include <PiLink.h>

extern SerialTransfer piXfer_;
extern PiLink piLink;
extern TxLog txLog;

// Callback Handlers
extern RxPing rxPing;
extern RxDriveMotorsRqst rxDriveMotorsRqst;

void ping_cb() { rxPing.handlePing(); }
void driveMotors_cb() { rxDriveMotorsRqst.handleDriveMotorsRqst(); }

const functionPtr callbackArr[] = { ping_cb, driveMotors_cb };

// PiLink implementation
PiLink::PiLink(HardwareSerial& linkSerial) 
  : linkSerial_(linkSerial)
{
}

bool
PiLink::init()
{
  bool isok = true;
  linkSerial_.begin(115200);

  //////////////// SerialTransfer Config Parameters ///////////////
  configST myConfig;
  myConfig.debug        = true;
  myConfig.callbacks    = callbackArr;
  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);

  piXfer_.begin(linkSerial_, myConfig);

  return isok;
}

void
PiLink::run(void* params)
{
  // Loop forever checking for received messages and messages posted for sending
  while(true)
  {
    txPong.sendPosted();
    piXfer_.tick();
    txLog.sendPosted();
    piXfer_.tick();

    vTaskDelay(10);
  }
}
