#include <Arduino.h>
#include <PiLink.h>
#include <ArduinoLog.h>
#include <LogStream.h>
#include <SerialTransfer.h>

// Define which serial port we'll use for PiLink
#define LINK_SERIAL Serial
//HardwareSerial hardwareSerial1 = HardwareSerial(1);
//#define LINK_SERIAL hardwareSerial1

// Globals
PiLink piLink= PiLink( LINK_SERIAL ) ;
LogStream logStream;

QueueHandle_t encoderMsgQ;  // global - used by ISRs in MobotOdometry

// Local object instantiations
static MowbotOdometry mowbotOdometry(encoderMsgQ);
static TaskHandle_t mowbotOdometryTaskHandle = NULL;

RL500CommsTask rl500CommsTask = RL500CommsTask(mowbotOdometry);
static TaskHandle_t rl500CommsTaskMsgHandler = NULL;

// global messages that callers use to send or receive Pi messages
RxPing rxPing = RxPing(piLink.piXfer_);
TxPong txPong = TxPong(piLink.piXfer_);
TxLog txLog = TxLog(piLink.piXfer_);
RxDriveMotorsRqst rxDriveMotorsRqst = RxDriveMotorsRqst(piLink.piXfer_);

// Local object instantiations
static TaskHandle_t piLinkTaskHandle = NULL;
static int loopCnt = 0;

// static functions to call run() method to start tasks in objects
void static startPiLinkTask(void* params) { piLink.run(params); }
void static startRunTask(void* params) { rl500CommsTask.run(params); }
void static startOdometryTask(void* params) { mowbotOdometry.run(params); }

// Curl up in a ball and die, printing epitaph occasionally
void fatalStop(std::string stopMsg)
{
  while(true)   // hang here forever if initialization failed
  {
    Log.fatalln(stopMsg.c_str());
    vTaskDelay(10000);   // periodically print the failure message
  }
}

void setup()
{
  bool isok = true;
  BaseType_t rv;

  if (Serial != LINK_SERIAL)
  {
    Serial.begin(115200);
  }
  delay(2000); // let serial start

  // initialize piLink
  isok = piLink.init();
  if (!isok)
  {
    fatalStop("piXfer init() failed");
  }

  // create piLink task
  rv = xTaskCreate(
         startPiLinkTask,
         "PiLink Task",
         2048,
         NULL,
         1,
         &piLinkTaskHandle);
  if (rv != pdTRUE)
  {
    fatalStop("Failed to create piLink task");
  }

  vTaskDelay(1000);  // let comms task message handler get started
  Log.begin(LOG_LEVEL_INFO, &logStream);

  // Send some test log messages
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

  // Initialize RL500CommsTask object & create thread
  Log.infoln("--- RL500 startup ---");
  isok = rl500CommsTask.init();
  if (!isok)
  {
    fatalStop("Error: RL500CommsTask.init() failed to initialize; stopped");
  }

  // create RL500 comms task
  rv = xTaskCreate(
         startRunTask,
         "RL500 Comms Task Message Handler",
         2048,
         NULL,
         1,
         &rl500CommsTaskMsgHandler);
  if (rv != pdTRUE)
  {
    fatalStop("Error: failed to create RL500CommsTaskMsgHandler task");
  }

  // Start Odometry
  Log.infoln("--- Odometry Startup ---");
  isok = mowbotOdometry.init();
  if (!isok)
  {
    fatalStop("MowbotOdometry init() failed");
  }

  // create MowbotOdometry task
  rv = xTaskCreate(
         startOdometryTask,
         "MowbotOdometry Task",
         2048,
         NULL,
         1,
         &mowbotOdometryTaskHandle);
  if (rv != pdTRUE)
  {
    fatalStop("Failed to create MowbotOdometry task");
  }

  vTaskDelay(5000);
}


void loop()
{
  delay(5000);
  Log.infoln("In PiXferTest loop(), cycle %d", loopCnt++);
}