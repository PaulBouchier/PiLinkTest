#include <Arduino.h>
#include <PiLink.h>
#include <ArduinoLog.h>
#include <LogStream.h>
#include <SerialTransfer.h>
#include <PiLinkMediator.h>

// Define which serial port we'll use for PiLink
//#define LINK_SERIAL Serial
#define LINK_SERIAL hardwareSerial1
HardwareSerial hardwareSerial1 = HardwareSerial(1);
PiLink piLink= PiLink( LINK_SERIAL ) ;

// Globals
// global messages that callers use to send or receive Pi messages
TxPong txPong = TxPong(piLink.piXfer_);
TxLog txLog = TxLog(piLink.piXfer_, piLink.linkLog_);
TxOdometry txOdometry = TxOdometry(piLink.piXfer_, piLink.linkLog_);

RxDriveMotorsRqst rxDriveMotorsRqst = RxDriveMotorsRqst(piLink.piXfer_);
RxLogLevel rxLogLevel = RxLogLevel(piLink.piXfer_, piLink.linkLog_);
RxPing rxPing = RxPing(piLink.piXfer_);
RxReboot rxReboot = RxReboot(piLink.piXfer_, piLink.linkLog_);

// Instantiate the mediator
PiLinkMediator piLinkMediator(
                            piLink,
                            txLog,
                            txOdometry,
                            rxDriveMotorsRqst
                            );

// Local object instantiations
static int loopCnt = 0;

void setup()
{
  bool isok = true;

  //Serial.begin(115200);
  delay(3000); // let serial start

  // initialize piLink
  isok = piLink.init(LOG_LEVEL_VERBOSE);
  
  if (!isok)
  {
    Serial.println("piXfer init() failed");
  }

  vTaskDelay(1000);  // let comms task message handler get started

}


void loop()
{
  piLink.linkLog_.infoln("In PiXferTest loop(), cycle %d", loopCnt++);
  delay(5000);
  // Send some test log messages
  piLink.linkLog_.verboseln("Verbose test log");
  vTaskDelay(500);
  piLink.linkLog_.traceln("Trace test log");
  vTaskDelay(500);
  piLink.linkLog_.infoln("Info test log");
  vTaskDelay(500);
  piLink.linkLog_.warningln("Warning test log");
  vTaskDelay(500);
  piLink.linkLog_.errorln("Error test log");
  vTaskDelay(500);
  piLink.linkLog_.fatalln("Fatal test log");
  delay(5000);
}