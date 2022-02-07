#include <PiLink.h>
#include <ArduinoLog.h>

/////////////////////////////////////////////////////////////////// Callbacks
void ping_cb()
{
  Serial.println("In ping_cb");
}

void list_cb()
{
  Serial.println("In list_cb");
}

// supplied as a reference - persistent allocation required
const functionPtr callbackArr[] = { ping_cb, list_cb };

PiLink::PiLink() {
  rxPing_ = RxPing(piLink_);
}

bool
PiLink::init()
{
  bool isok = true;
  serial1.begin(115200);

  //////////////// SerialTransfer Config Parameters ///////////////
  configST myConfig;
  myConfig.debug        = true;
  myConfig.callbacks    = callbackArr;
  myConfig.callbacksLen = sizeof(callbackArr) / sizeof(functionPtr);

  piXfer.begin(serial1, myConfig);

  return isok;
}

void
PiLink::run(void* params)
{
  Log.infoln("Running PiLinkTask");

  while(true)
  {
    if (piXfer.tick())
    {
      Log.traceln("piXfer.tick() received a message");
    }
    vTaskDelay(10);
  }
}