#include <Arduino.h>
#include <PiLink.h>
#include <ArduinoLog.h>

// Globals
PiLink piLink;

// Local object instantiations
static TaskHandle_t piLinkTaskHandle = NULL;

// @brief static function to call run() method
void static startPiLinkTask(void* params)
{
  piLink.run(params);
}

void setup()
{
  bool isok = true;

  Serial.begin(115200);
  delay(2000); // let serial start

  Log.begin(LOG_LEVEL_INFO, &Serial);
  Log.infoln("--- PiXfer Test ---");

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
}


void loop()
{
  delay(500);
}