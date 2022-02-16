#include <LogStream.h>
#include <messages/TxLog.h>

extern TxLog txLog;

LogStream::LogStream()
{
  buff_ = new char[128];
  buffp_ = buff_;
}

size_t
LogStream::write(uint8_t c)
{
  *buffp_ = c;
  if ('\n' == c)
  {
    txLog.post(buff_, logLength_);
    buffp_ = buff_;
    logLength_ = 0;
  }
  else
  {
    buffp_++;
    logLength_++;
  }
  return 1;
}

int
LogStream::available()
{
  return 0;
}

int
LogStream::read()
{
  return 0;
}

int
LogStream::peek()
{
  return 0;
}
