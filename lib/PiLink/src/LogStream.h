#pragma once

#include <Arduino.h>


// @brief class that implements a stream-like class for use by Arduino logs
class LogStream : public Stream
{
public:
  LogStream();
  size_t write(uint8_t);            // implements pure virtual method from Print
  int available();                  // implements pure virtual method from Stream
  int read();                       // implements pure virtual method from Stream
  int peek();                       // implements pure virtual method from Stream
  void flush() {};                  // implements pure virtual method from Stream

private:
  char *buff_;                       // buffer for storing logs
  char *buffp_;                      // pointer to current write location
  int logLength_;                     // number of bytes in buffer
};