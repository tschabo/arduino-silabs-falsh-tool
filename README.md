arduino-silabs-falsh-tool
=========================

A tool to use an Arduino board for programming Silabs 8-bit 8051 MCU's.

The Software consists of to parts:
  1. The Firmware for the arduino, which talks to the D2 Interface of the Silabs MCU
  2. The Flash tool which writes the intel hex file to the Silabs MCU

#### Building the firmware

###### Dependencies

  * avr-libc 
  * binutils-avr 
  * gcc-avr 
  * avrdude

###### Linux

```bash
cd firmware
./build
```
then connect the arduino

edit 'flash' file ... replace '/dev/ttyACM0' with the serial port the ardunino is connected to replace the baud rate with the one which fits for your arduino

```bash
./flash
```

###### Windows

*TODO*

#### Building the flash tool

###### Dependencies
  * Arch Linux
   * base-devel
   * qt4
   * qt-creator (optional for development)
  * Debian + Ubuntu
   * build-essential
   * libqt4-dev
   * qt-creator (optional for development)
  * Windows
   * Qt SDK with MinGw (not tested)

###### Linux

```bash
cd SiArduFlash
qmake # use qmake-qt4 instead if other versions of qt are installed besides qt4
make
```

Alternative: use qtcreator

###### Windows

*TODO*

#### Connections on the Arduino

D2 interface | atmega328p | arduino
--- | --- | ---
C2D | PORTB4 | 12
C2CK | PORTB3 |11

#### Usage
```bash
./SiArduFlash -h
```
