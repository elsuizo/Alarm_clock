/* -------------------------------------------------------------------------
@file alarm_clock.h

@date 04/09/17 23:19:25
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief

@detail

Licence:
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
---------------------------------------------------------------------------*/
#ifndef ALARM_CLOCK_H
#define ALARM_CLOCK_H
/**------------------------------------------------------------------------
 *                           includes
 -------------------------------------------------------------------------*/
/* mannage the old version of Arduino IDE */
#if (ARDUINO > 100)
   #include "Arduino.h"
#else
   #include "WProgram.h"
#endif
#include "RTClib.h"
#include <LiquidCrystal.h>
#include <Wire.h>

/**------------------------------------------------------------------------
 *                           defines
 -------------------------------------------------------------------------*/
#define  SERIAL_SPEED    9600
#define  DEBOUNCE_DELAY  40
#define  LCD_DELAY       10
#define  PIN_LED_DEBUG   13    /**<  Arduino  led pin */
#define  PIN_BUZZER      6     /**<  buzzer   pin  */
#define  PIN_BUTTON1     3
#define  PIN_BUTTON2     2
#define  PIN_BUTTON3     5
/**< LCD PINS */
#define  LCD_RS      7
#define  LCD_ENABLE  8
#define  LCD_D0      9
#define  LCD_D1      10
#define  LCD_D2      11
#define  LCD_D3      12

typedef enum{BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING} buttonState_t;
 /**------------------------------------------------------------------------
  *                           prototypes
  -------------------------------------------------------------------------*/
void alarm_clock_button_FSM_init(int pin);
void alarm_clock_button_FSM_update(int pin);
// static void alarm_clock_button_UP(int pin);
// static void alarm_clock_button_FALLING(int pin);
// static void alarm_clock_button_RISING(int pin);
// static void alarm_clock_button_DOWN(int pin);
/**< states clock functions */
void alarm_clock_FSM_init();
void alarm_clock_FSM_update();
void alarm_clock_TIME();
void alarm_clock_ALARM();
void alarm_clock_SET_ALARM();
void alarm_clock_show_time();
void alarm_clock_show_alarm();
void PIN_BUTTON1_ISR();
void PIN_BUTTON2_ISR();
void alarm_clock_button_pressed();
void alarm_clock_button_release();
/**------------------------------------------------------------------------
 *                           custom data types
 -------------------------------------------------------------------------*/
#endif
