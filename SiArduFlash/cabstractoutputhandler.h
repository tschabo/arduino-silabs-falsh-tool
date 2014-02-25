#ifndef CABSTRACTOUTPUTHANDLER_H
#define CABSTRACTOUTPUTHANDLER_H

class CAbstractOutputHandler
{
public:
  CAbstractOutputHandler();
  virtual ~CAbstractOutputHandler(){}
  virtual bool handleOutput(const char * text) = 0;
};

#endif // CABSTRACTOUTPUTHANDLER_H
