/* -------------------------------------------------------------------------
@file alarm_clock.c

@date 04/09/17 23:37:48
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
/**< includes */
#include "alarm_clock.h"

static RTC_DS1307 RTC;
static LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3);

static bool button1_state;
static bool button2_state;
static int alarm_hour;
static int alarm_minutes;
static int alarm_seconds;
typedef enum{BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RISING} buttonState_t;


void (*clock_state)(void);

void PIN_BUTTON2_ISR() {
   button2_state++;
}

void PIN_BUTTON1_ISR() {
   if(button1_state)
      button1_state = false;
   else {
      button1_state = true;
   }
}

/**------------------------------------------------------------------------
 *                          Clock Finite State Machine
 -------------------------------------------------------------------------*/
void alarm_clock_FSM_init() {
   Wire.begin();
   RTC.begin();
   lcd.begin(16, 2); /**< initialize lcd */
   button1_state = false;
   button2_state = false;
   clock_state = alarm_clock_TIME;
   alarm_hour = 0;
   alarm_minutes = 0;
   alarm_seconds = 0;
}

void alarm_clock_FSM_update() {
   clock_state();
}

void alarm_clock_TIME() {
   if(button1_state) {
      clock_state = alarm_clock_SET_ALARM;
   }
   alarm_clock_show_time();
}

void alarm_clock_show_time() {

   DateTime now = RTC.now();
   /**< Clear the LCD */
   lcd.clear();
   /**< check if we need to add leading zero in hour*/
   if (now.hour() < 10) lcd.print("0");
   /**< output the current hour */
   lcd.print(now.hour(), DEC);
   lcd.print(":");
   /**< check if we need to add leading zero in minutes*/
   if (now.minute() < 10) lcd.print("0");
   /**< output the current minute */
   lcd.print(now.minute(), DEC);
   lcd.print(":");
   /**< check if we need to add leading zero in seconds */
   if (now.second() < 10) lcd.print("0");
   /**< output the current seconds */
   lcd.print(now.second(), DEC);
   delay(LCD_DELAY);
}

void alarm_clock_show_alarm() {

   /**< Clear the LCD */
   lcd.clear();
   /**< check if we need to add leading zero in hour*/
   if (alarm_hour > 10) {
      alarm_hour = 0;
   }
   /**< output the current hour */
   lcd.print(alarm_hour, DEC);
   lcd.print(":");
   /**< check if we need to add leading zero in minutes*/
   if (alarm_minutes > 10) {
      alarm_minutes = 0;
   }
   /**< output the current minute */
   lcd.print(alarm_minutes, DEC);
   lcd.print(":");
   if (alarm_seconds > 10) {
      alarm_seconds = 0;
   }
   /**< output the current seconds */
   lcd.print(alarm_seconds, DEC);
   delay(LCD_DELAY);
}

void alarm_clock_SET_ALARM() {

   alarm_clock_show_alarm();
   if(button2_state) {
      alarm_minutes++;
   }

   if(!button1_state) {
      clock_state = alarm_clock_TIME;
   }
}

void alarm_clock_ALARM() {

}

void alarm_clock_button_FSM_init(void){
   button_state = BUTTON_UP;
}

void alarm_clock_button_FSM_update(void){
   switch(button_state){
      case BUTTON_UP:{
         if(digitalRead(PIN_BUTTON3) == HIGH)
            buttonState = BUTTON_FALLING;
         break;
      }
      case BUTTON_FALLING:{
         delay(DEBOUNCE_DELAY);
         if(digitalRead(PIN_BUTTON3) == HIGH){
            buttonState = BUTTON_DOWN;
            /* Dispara el evento */
            alarm_clock_button_pressed();
         }
         else
            buttonState = BUTTON_UP;
         break;
      }
      case BUTTON_DOWN:{
         if(digitalRead(PIN_BUTTON3) == LOW)
            buttonState = BUTTON_RISING;
         break;
      }
      case BUTTON_RISING:{
         delay(DEBOUNCE_DELAY);
         if(digitalRead(digitalRead(PIN_BUTTON3) == LOW)){
            buttonState = BUTTON_UP;
            /* Dispara el evento */
            alarm_clock_button_release();
         }
         else
            buttonState = BUTTON_DOWN;
         break;
      }
      default:{
         buttonMefInit();
      }
   }
}

