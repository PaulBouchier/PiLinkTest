#include <ArduinoLog.h>
#include <PiLink.h>
#include <LogStream.h>

extern SerialTransfer piXfer_;
extern PiLink piLink;
extern TxLog txLog;
extern TxOdometry txOdometry;

// Prefix print function for logs from this object
static void printPrefix(Print* logOutput, int logLevel)
{
  switch(logLevel)
  {
    default:
    case 0: logOutput->print("S: link: "); break;
    case 1: logOutput->print("F: link: "); break;
    case 2: logOutput->print("E: link: "); break;
    case 3: logOutput->print("W: link: "); break;
    case 4: logOutput->print("I: link: "); break;
    case 5: logOutput->print("T: link: "); break;
    case 6: logOutput->print("V: link: "); break;
  }
}

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
PiLink::init(int logLevel, Stream* stream_p)
{
  bool isok = true;

  linkSerial_.begin(115200);

  // Start logger
  if (stream_p == NULL)
  {  
    // No logStream provided, use logStream
    LogStream* logStream_p = new LogStream();
    logStream_p->setMediator(mediator_);
    //linkLog_.setPrefix("PiLink: ");
    linkLog_.begin(logLevel, logStream_p);
  }
  else
  {
    linkLog_.begin(logLevel, stream_p);
  }
  linkLog_.setPrefix(printPrefix);
  linkLog_.setShowLevel(false);

  linkLog_.infoln("PiLink::init()");

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
    txOdometry.sendPosted();
    piXfer_.tick();

    vTaskDelay(10);
  }
}
