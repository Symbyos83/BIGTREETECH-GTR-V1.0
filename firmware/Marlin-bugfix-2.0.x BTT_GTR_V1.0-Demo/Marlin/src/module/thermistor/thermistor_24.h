/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#define REVERSE_TEMP_SENSOR_RANGE

// Marlin temperature sensor type 24
//
// This was created to allow use of the E3D PT100 amplifier on the BigTreeTech and similar boards 
// without requiring any hardware mods (cutting resistors, etc.).
// The BigTreeTech boards have a 3.3V ADC reference and a 4.7K pullup resistor 
// connected to the Thermistor inputs so we can't use the standard Marlin temp sensor types.
//
// HARDWARE INSTALL:
//
// Since the BigTreeTech board is not 5V tolerant you need to operate the 
// E3D PT100 at 3.3V. Yes this board will operate at 3.3V but it won't report
// temperatures beyond approx 360C.
// 3.3V can be found on some BTT connectors (WIFI connector on the SKR 1.4)
// Connect the output of the PT100 amp to the standard thermistor input on the BTT board.
//
// SOFTWARE INSTALL:
//
// This table must be compiled into the Marlin 2.0.x firmware. Locate and open the 
// thermistors.h file and add the following text:
//
// #if ANY_THERMISTOR_IS(24) // Pt100 with E3D amp @ 3.3v w/4.7K pullup (BigTreeTech GTR v1.0) New
//   #include "thermistor_24.h"
// #endif
//
// In configuration.h:
//      #define TEMP_SENSOR_0 24       // use 0 or 1
//      #define HEATER_0_MAXTEMP 310   // set max temperature to less than 360
//
// CALCULATIONS:
//
// Array values below were derived from PT100 resistance vs temperature tables.
//
// Constants:
//    Vref = 3.30V
//    Rb = 4400 (resistance of two bridge resistors in the INA826 circuit)
//    Rpu = 4700 (pullup resistor on thermistor input)
//    Ramp = 100 (INA826 amp output resistor)
//    RTD = Resistance @ temperature. Example 111 ohms at 25C.
//      
// Calculate Vo : output of the INA826 amplifier in the E3D PCB
//    Vo = ((Vref / (RTD + Rb)) * RTD) * 10
// Next calculate Vadc : output voltage with a 4.7K pullup on the thermistor input.
//    Vadc = (((Vref - Vo) / Rpu) * Ramp) + Vo
// Lastly calculate ADC digital value for each point in the array below (10 bit ADC, 0 - 1023).
//    ADC = (Vadc / Vref) * 1024
//
// Abby@Abbycus 2020
//
const short temptable_24[][2] PROGMEM = {
  { OV(  0),    0 },
  { OV(245),    1 },
  { OV(261),   10 },
  { OV(269),   20 },
  { OV(277),   30 },
  { OV(286),   40 },
  { OV(294),   50 },
  { OV(302),   60 },
  { OV(311),   70 },
  { OV(319),   80 },
  { OV(327),   90 },
  { OV(335),  100 },
  { OV(343),  110 },
  { OV(351),  120 },
  { OV(359),  130 },
  { OV(367),  140 },
  { OV(375),  150 },
  { OV(383),  160 },
  { OV(391),  170 },
  { OV(398),  180 },
  { OV(406),  190 },
  { OV(414),  200 },
  { OV(422),  210 },
  { OV(429),  220 },
  { OV(437),  230 },
  { OV(444),  240 },
  { OV(452),  250 },
  { OV(459),  260 },
  { OV(467),  270 },
  { OV(474),  280 },
  { OV(482),  290 },
  { OV(489),  300 },
  { OV(497),  310 },
  { OV(504),  320 },
  { OV(511),  330 },
  { OV(518),  340 },
  { OV(525),  350 },
  { OV(533),  360 },
  { OV(540),  370 },
  { OV(547),  380 },
  { OV(554),  390 },
  { OV(561),  400 },
  { OV(629),  500 },
  { OV(694),  600 },
  { OV(755),  700 },
  { OV(815),  800 },
  { OV(854),  900 },
  { OV(914), 1000 },
  { OV(964), 1100 }
};
