#include "cstdoutoutputhandler.h"

#include <QTextStream>

CStdOutOutputHandler::CStdOutOutputHandler()
{
}


bool CStdOutOutputHandler::handleOutput(const char *text)
{
  QTextStream(stdout) << text;
  return true;
}
