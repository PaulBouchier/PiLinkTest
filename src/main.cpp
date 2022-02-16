#include <Arduino.h>
#include <PiLink.h>
#include <ArduinoLog.h>
#include <LogStream.h>
#include <SerialTransfer.h>

// Define which serial port we'll use for PiLink
#define LINK_SERIAL Serial
// #define Link_SERIAL HardwareSerial(1)

// Globals
PiLink piLink= PiLink( LINK_SERIAL ) ;
LogStream logStream;

// global messages that callers use to send or receive Pi messages
RxPing rxPing = RxPing(piLink.piXfer_);
TxPong txPong = TxPong(piLink.piXfer_);
TxLog txLog = TxLog(piLink.piXfer_);

// Local object instantiations
static TaskHandle_t piLinkTaskHandle = NULL;
static int loopCnt = 0;

// @brief static function to call run() method
void static startPiLinkTask(void* params)
{
  piLink.run(params);
}

void setup()
{
  bool isok = true;

  if (Serial != LINK_SERIAL)
  {
    Serial.begin(115200);
  }
  delay(2000); // let serial start

  // initialize piLink
  isok = piLink.init();
  if (!isok)
  {
    while(true)   // hang here forever if initialization fails
    {
      Log.fatalln("piXfer init() failed");
      delay(10000);
    }
  }

  // create piLink task
  BaseType_t rv = xTaskCreate(
                    startPiLinkTask,
                    "PiLink Task",
                    2048,
                    NULL,
                    1,
                    &piLinkTaskHandle);
  if (rv != pdTRUE)
  {
    while(true)   // hang here forever if task creation failed
    {
      Log.fatalln("Failed to create piLink task");
      vTaskDelay(10000);   // periodically print the failed message
    }
  }

  Log.begin(LOG_LEVEL_INFO, &logStream);
  vTaskDelay(5000);
  Log.verboseln("Verbose test log");
  vTaskDelay(500);
  Log.traceln("Trace test log");
  vTaskDelay(500);
  Log.infoln("Info test log");
  vTaskDelay(500);
  Log.warningln("Warning test log");
  vTaskDelay(500);
  Log.errorln("Error test log");
  vTaskDelay(500);
  Log.fatalln("Fatal test log");
  vTaskDelay(500);
}


void loop()
{
  delay(5000);
  Log.infoln("In PiXferTest loop(), cycle %d", loopCnt++);
}