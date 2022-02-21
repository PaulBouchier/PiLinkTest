#include <ArduinoLog.h>
#include <PiLink.h>

extern SerialTransfer piXfer_;
extern PiLink piLink;
extern TxLog txLog;

// static function to call run() method to start PiLink task
void static startPiLinkTask(void* params) { piLink.run(params); }

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
PiLink::init(Stream* logStream, int logLevel)
{
  bool isok = true;
  linkLog_.begin(logLevel, logStream);
  linkLog_.infoln("PiLink::init()");

  linkSerial_.begin(115200);

  // SerialTransfer Config Parameters
  configST myConfig;
  myConfig.debug        = true;
  myConfig.callbacks    = callbackArr;
  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);

  piXfer_.begin(linkSerial_, myConfig);

  // create piLink task
  BaseType_t rv = xTaskCreate(
                              startPiLinkTask,
                              "PiLink Task",
                              2048,
                              NULL,
                              1,
                              &piLinkTaskHandle_);
  while (rv != pdTRUE)
  {
    linkLog_.fatalln("Failed to create piLink task; stopped");
    Serial.println("Failed to create piLink task; stopped");
    delay(2000);
  }

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
