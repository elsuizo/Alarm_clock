/* -------------------------------------------------------------------------
@file Alarm_clock.ino

@date 04/09/17 23:16:22
@author Martin Noblia
@email martin.noblia@openmailbox.org

@brief
Clock alarm with arduino
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
#include "alarm_clock.h"

void setup() {
   Serial.begin(SERIAL_SPEED);
   pinMode(PIN_BUZZER, OUTPUT);
   pinMode(PIN_LED_DEBUG, OUTPUT);
   pinMode(PIN_BUTTON1, INPUT);
   pinMode(PIN_BUTTON2, INPUT);
   pinMode(PIN_BUTTON3, INPUT);
   alarm_clock_FSM_init();
   attachInterrupt(digitalPinToInterrupt(3), PIN_BUTTON1_ISR, FALLING);
   attachInterrupt(digitalPinToInterrupt(2), PIN_BUTTON2_ISR, FALLING);
}

void loop() {
   alarm_clock_FSM_update();
}
