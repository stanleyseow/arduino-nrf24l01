/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.


MODIFIED BY RICH FEDOR, AUG2,2012
WORKS WITH NRF24L01 MODULE, SPI MODE0 

Added to github repository by Stanley Seow
for Nordic nRF24L01 wireless modules

Date : 10 Apr 2013
e-mail : stanleyseow@gmail.com
github : https://hithub.com/stanleyseow/attiny-nRF24L01
Desc   : This SPI 85 is for attiny85/x5 and attiny84/x4

Date : 24 July 2013
Desc : Changes the transfer using bitwise operator | instead of +

 */

#ifndef _SPI85_H_INCLUDED
#define _SPI85_H_INCLUDED

#include <stdio.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06
//#define SPI_CLOCK_DIV64 0x07

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

class SPI85Class {
public:
  inline static byte transfer(byte _data);

  // SPI Configuration methods

  static void begin(); // Default
  static void end();

   static void setDataMode(uint8_t);
  static void setClockDivider(uint8_t);
};

extern SPI85Class SPI85;

uint8_t SPI85Class::transfer(uint8_t _data) {
  USIDR = _data;
  USISR = _BV(USIOIF);
  
  while((USISR & _BV(USIOIF)) == 0){
    USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
  }
  return USIDR;
}
#endif
