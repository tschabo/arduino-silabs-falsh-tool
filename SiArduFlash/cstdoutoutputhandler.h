#ifndef CSTDOUTOUTPUTHANDLER_H
#define CSTDOUTOUTPUTHANDLER_H

#include "cabstractoutputhandler.h"

class CStdOutOutputHandler : public CAbstractOutputHandler
{
public:
  CStdOutOutputHandler();
  ~CStdOutOutputHandler(){}
  bool handleOutput(const char *text);
};

#endif // CSTDOUTOUTPUTHANDLER_H
