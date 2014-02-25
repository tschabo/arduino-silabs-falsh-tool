/****************************************************************************
** Copyright (c) 2012 Sebastian Schmitt
** All right reserved.
** Web: http://code.google.com/p/esc-tool-for-blheli/
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#include <QString>
#include <QTextStream>
#include <QCoreApplication>
#include "cprogrammer.h"

#define SW_PATH_HEX_FILE  "-f"
#define SW_DEVICE_NAME    "-d"
#define SW_MODE_WRITE     "-w"
#define SW_MODE_VERIFY    "-v"
#define SW_HELP           "-h"
#define SW_MCU_ID         "-i"

enum IO_MODE
{
  io_mode_write,
  io_mode_verify,
  io_mode_undef
};

void printHelp(const char * progName)
{
  QTextStream(stdout) << QCoreApplication::tr("\n\nUsage:\n") << progName
                      << " [[" << SW_MODE_WRITE << " | " << SW_MODE_VERIFY << "] "
                      << "-i <mcu id> "
                      << SW_PATH_HEX_FILE << QCoreApplication::tr(" <path to hex file> ")
                      << SW_DEVICE_NAME << QCoreApplication::tr(" <serial device name> | ")
                      << SW_HELP << "]\n\n"
                      << SW_MODE_WRITE << QCoreApplication::tr(" Write flash\n")
                      << SW_MODE_VERIFY << QCoreApplication::tr(" Verify flash\n")
                      << SW_MCU_ID << QCoreApplication::tr(" Id of the mcu\n")
                      << SW_PATH_HEX_FILE << QCoreApplication::tr(" Path to the hexfile\n")
                      << SW_DEVICE_NAME << QCoreApplication::tr(" Device name to write to / verify from\n")
                      << SW_HELP << QCoreApplication::tr(" Print this help text\n\n");
}

bool getNextArg(int argc, char *argv[], int &index, QString &arg)
{
  if(++index < argc)
  {
    arg = QString::fromLocal8Bit(argv[index]);
    return true;
  }
  return false;
}

int main(int argc, char *argv[])
{
  QString pathHexFile;
  IO_MODE ioMode = io_mode_undef;
  QString device;
  QString mcuId;

  QString actualArg;

  for(int i = 1; i < argc; i++)
  {
    actualArg = QString::fromLocal8Bit(argv[i]);

    if(actualArg == SW_PATH_HEX_FILE)
    {
      if(!getNextArg(argc, argv, i, pathHexFile))
      {
        return 1;
      }
    }
    else if(actualArg == SW_DEVICE_NAME)
    {
      if(!getNextArg(argc, argv, i, device))
      {
        return 1;
      }
    }
    else if(actualArg == SW_MODE_WRITE)
    {
      ioMode = io_mode_write;
    }
    else if(actualArg == SW_MODE_VERIFY)
    {
      ioMode = io_mode_verify;
    }
    else if(actualArg == SW_MCU_ID)
    {
      if(!getNextArg(argc, argv, i, mcuId))
      {
        return 1;
      }
    }
    else if(actualArg == SW_HELP)
    {
      printHelp(argv[0]);
      return 0;
    }
    else
    {
      printHelp(argv[0]);
      return 2;
    }
  }

  if(pathHexFile.isEmpty() ||
     device.isEmpty() ||
     ioMode == io_mode_undef)
  {
    printHelp(argv[0]);
    return 2;
  }

  CProgrammer p(mcuId);
  p.setPortName(device);

  QTextStream(stdout) << QCoreApplication::tr("\n\nOptions:\n\n")
                      << QCoreApplication::tr("Hex file Path\t: ") << pathHexFile << "\n"
                      << QCoreApplication::tr("Device name\t: ") << device << "\n"
                      << QCoreApplication::tr("MCU id\t\t: ") << mcuId << "\n"
                      << QCoreApplication::tr("IO mode\t\t: ");
  if(ioMode == io_mode_write)
  {
    QTextStream(stdout) << QCoreApplication::tr("write\n");
  }
  else if(ioMode == io_mode_verify)
  {
    QTextStream(stdout) << QCoreApplication::tr("verify\n");
  }
  QTextStream(stdout) << QCoreApplication::tr("\n\n");

  if(ioMode == io_mode_write)
  {
    if(!p.writeProgramToDevice(pathHexFile))
    {
      return 1;
    }
  }
  if(ioMode == io_mode_verify)
  {
    if(!p.verifyProgramOnDevice(pathHexFile))
    {
      return 1;
    }
  }
  return 0;
}
