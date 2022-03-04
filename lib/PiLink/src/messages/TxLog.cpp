#include <messages/TxLog.h>

const static int numLogBuffs = 10;        // number of log buffers
const static int logBuffSize = 128;       // size of each log buffer

static char* buffArray[numLogBuffs];      // array of pointers to the log buffers
static TxLog::LogEntry logsArray[numLogBuffs];   // array of LogEntries for log metadata
static CircularBuffer_<TxLog::LogEntry> logsQ(logsArray, numLogBuffs); // the ringbuffer containing LogEntry structs
static int nextIndex = 0;                 // next index into logsQ & buffArray_ to use for LogEntry & data storage

TxLog::TxLog(SerialTransfer& piXfer, Logging& linklog)
  : piXfer_(piXfer)
  , linkLog_(linklog)
{
  mutex_ = xSemaphoreCreateMutex();
  for (int i=0; i<numLogBuffs; i++)
  {
    buffArray[i] = (char*)malloc(logBuffSize);
  }
}

void
TxLog::post(char* logMsg, int logLength)
{
  xSemaphoreTake(mutex_, 5);

  if (logLength > logBuffSize)
  {
    logLength = logBuffSize;
  }

  if (logsQ.full())
  {
    seq_++;       // enable detection of dropped log
    return;       // nothing to do but bail
  }

  // store the incoming log and LogEntry data for later transmission
  inbound_.timestamp = xTaskGetTickCount();
  inbound_.logLength = logLength;
  inbound_.index = nextIndex;
  inbound_.seq = seq_;
  logsQ.put(inbound_);
  memcpy((char*)buffArray[nextIndex], (char*)logMsg, logLength);    // save the log msg in the next buffer

  nextIndex = (nextIndex + 1) % numLogBuffs;
  seq_++;

  xSemaphoreGive(mutex_);
}

bool
TxLog::sendPosted()
{
  bool isok = true;

  xSemaphoreTake(mutex_, 5);
  if (logsQ.empty())
  {
    xSemaphoreGive(mutex_);
    return true;
  }

  logsQ.get(outbound_);
  uint16_t sendSize = 0;
  sendSize = piXfer_.txObj(outbound_.seq, sendSize);
  sendSize = piXfer_.txObj(outbound_.timestamp, sendSize);
  sendSize = piXfer_.txObj(*buffArray[outbound_.index], sendSize, outbound_.logLength);
  uint8_t sentSize = piXfer_.sendData(sendSize, pktIdLog);
  if (sentSize != sendSize)
  {
    linkLog_.errorln("Failed to send correct # of bytes in TxLog");
    isok = false;
  }
  xSemaphoreGive(mutex_);
  return isok;
}
