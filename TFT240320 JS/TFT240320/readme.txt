DIY Photo frame BL-TFT240320PLUS V2
www.circuitidea.com

HARDWARE
  AVR mega8,16,32
  BL-TFT240320PLUS. An interface can be 8/16 bit mode. TFT LCD arduino shield.
  SD card

File
APPLICATION
  main.c main program. scan SD card and display BMP file on lcd.
  readme.txt this text.
BMP DISPLAY
  sdbmp.c,
  sdbmp.h Read SD Card and plot to LCD.
SD card driver
  mmc.c,
  disio.h,
  pff.c,
  pff.h
  integer.h SD driver / Petit FatFs (C)ChaN, 2009 (http://elm-chan.org)
  mcc.h avr spi for sd card interface.
LCD driver
  SSD1289.c,
  SSD1289.h,
  graphic.h TFT LCD interface. LCD driver SSD1289.
  
Release 01
  first release
Release 02
  - (readme.txt) add comment
  - (sdbmp.c) Change reading sd card using stream. It give faster and smooter display
  - (ssd1289.c)Change Bar function to native code from call routine. So clear screen is too fast.
Release 03
  - change hardware to support arduino I2C and add ds1307 RTC (only arduino).