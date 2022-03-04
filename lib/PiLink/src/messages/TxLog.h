#pragma once

#include <Arduino.h>
#include <SerialTransfer.h>
#include <messages/packetIds.h>
#include <ArduinoLog.h>
#include <CircularBuffer.h>

class TxLog
{
public:
  struct LogEntry {
    int index;                  // index into the array of buffers at which logMsg is stored
    int logLength;              // length of this log
    TickType_t timestamp;       // timestamp of log
    int seq;                    // sequence # of this logEntry
  };

  TxLog(SerialTransfer& piXfer, Logging& linkLog);

  // @brief Post a request to send a log message over the link
  // @param logMsg The message to send
  // @param logLength Size of logMsg
  void post(char* logMsg, int logLength);

  // @brief If a request to send a log has been posted, send it
  bool sendPosted();

private:
  LogEntry inbound_;                  // LogEntry data to be put into the circular buffer
  LogEntry outbound_;                 // LogEntry data for logs removed from the circular buffer

  SerialTransfer& piXfer_;
  int seq_ = 0;                       // log sequence number
  SemaphoreHandle_t mutex_;
  Logging& linkLog_;
};

