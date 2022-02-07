#include <PiLink.h>

/////////////////////////////////////////////////////////////////// Callbacks
void echo_cb()
{
  Serial.println("In echo_cb");
}

void list_cb()
{
  Serial.println("In list_cb");
}

// supplied as a reference - persistent allocation required
const functionPtr callbackArr[] = { echo_cb, list_cb };

PiLink::PiLink() {}

bool
PiLink::init()
{
  bool isok = True;
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
PiLink::run()
{

}