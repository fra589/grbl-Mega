/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2017-2018 Gauthier Briere
  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl supports only the
   Arduino Mega2560. */

#ifndef cpu_map_h
#define cpu_map_h


#ifdef CPU_MAP_2560_INITIAL // (Arduino Mega 2560) Working @EliteEng

  // Serial port interrupt vectors
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_DDR      DDRA
  #define STEP_PORT     PORTA
  #define STEP_PIN      PINA
  #define X_STEP_BIT    2 // MEGA2560 Digital Pin 24
  #define Y_STEP_BIT    3 // MEGA2560 Digital Pin 25
  #define Z_STEP_BIT    4 // MEGA2560 Digital Pin 26
  #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR     DDRC
  #define DIRECTION_PORT    PORTC
  #define DIRECTION_PIN     PINC
  #define X_DIRECTION_BIT   7 // MEGA2560 Digital Pin 30
  #define Y_DIRECTION_BIT   6 // MEGA2560 Digital Pin 31
  #define Z_DIRECTION_BIT   5 // MEGA2560 Digital Pin 32
  #define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR   DDRB
  #define STEPPERS_DISABLE_PORT  PORTB
  #define STEPPERS_DISABLE_BIT   7 // MEGA2560 Digital Pin 13
  #define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // NOTE: All limit bit pins must be on the same port
  #define LIMIT_DDR       DDRB
  #define LIMIT_PORT      PORTB
  #define LIMIT_PIN       PINB
  #define X_LIMIT_BIT     4 // MEGA2560 Digital Pin 10
  #define Y_LIMIT_BIT     5 // MEGA2560 Digital Pin 11
  #define Z_LIMIT_BIT     6 // MEGA2560 Digital Pin 12
  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect  PCINT0_vect
  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_DDR      DDRH
  #define SPINDLE_ENABLE_PORT     PORTH
  #define SPINDLE_ENABLE_BIT      3 // MEGA2560 Digital Pin 6
  #define SPINDLE_DIRECTION_DDR   DDRE
  #define SPINDLE_DIRECTION_PORT  PORTE
  #define SPINDLE_DIRECTION_BIT   3 // MEGA2560 Digital Pin 5

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_DDR   DDRH
  #define COOLANT_FLOOD_PORT  PORTH
  #define COOLANT_FLOOD_BIT   5 // MEGA2560 Digital Pin 8
  #define COOLANT_MIST_DDR    DDRH
  #define COOLANT_MIST_PORT   PORTH
  #define COOLANT_MIST_BIT    6 // MEGA2560 Digital Pin 9

  // Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       DDRK
  #define CONTROL_PIN       PINK
  #define CONTROL_PORT      PORTK
  #define CONTROL_RESET_BIT         0  // MEGA2560 Analog Pin 8
  #define CONTROL_FEED_HOLD_BIT     1  // MEGA2560 Analog Pin 9
  #define CONTROL_CYCLE_START_BIT   2  // MEGA2560 Analog Pin 10
  #define CONTROL_SAFETY_DOOR_BIT   3  // MEGA2560 Analog Pin 11
  #define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT2_vect
  #define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
  #define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
  #define PROBE_DDR       DDRK
  #define PROBE_PIN       PINK
  #define PROBE_PORT      PORTK
  #define PROBE_BIT       7  // MEGA2560 Analog Pin 15
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 7
  #define SPINDLE_PWM_MAX_VALUE     1024.0 // Translates to about 1.9 kHz PWM frequency at 1/8 prescaler
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
  #define SPINDLE_TCCRA_REGISTER    TCCR4A
  #define SPINDLE_TCCRB_REGISTER    TCCR4B
  #define SPINDLE_OCR_REGISTER      OCR4B
  #define SPINDLE_COMB_BIT          COM4B1

  // 1/8 Prescaler, 16-bit Fast PWM mode
  #define SPINDLE_TCCRA_INIT_MASK ((1<<WGM40) | (1<<WGM41))
  #define SPINDLE_TCCRB_INIT_MASK ((1<<WGM42) | (1<<WGM43) | (1<<CS41))
  #define SPINDLE_OCRA_REGISTER   OCR4A // 16-bit Fast PWM mode requires top reset value stored here.
  #define SPINDLE_OCRA_TOP_VALUE  0x0400 // PWM counter reset value. Should be the same as PWM_MAX_VALUE in hex.

  // Define spindle output pins.
  #define SPINDLE_PWM_DDR   DDRH
  #define SPINDLE_PWM_PORT  PORTH
  #define SPINDLE_PWM_BIT   4 // MEGA2560 Digital Pin 7

#endif

#ifdef CPU_MAP_2560_YK // (Arduino Mega 2560)

  // Serial port interrupt vectors
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_DDR      DDRF
  #define STEP_PORT     PORTF
  #define STEP_PIN      PINF
  #define X_STEP_BIT    0 // MEGA2560 Analog Pin 0
  #define Y_STEP_BIT    1 // MEGA2560 Analog Pin 1
  #define Z_STEP_BIT    2 // MEGA2560 Analog Pin 2
  #define A_STEP_BIT    3 // MEGA2560 Analog Pin 3
  #define B_STEP_BIT    4 // MEGA2560 Analog Pin 4
  #define C_STEP_BIT    5 // MEGA2560 Analog Pin 5
  #define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)|(1<<B_STEP_BIT)|(1<<C_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR     DDRK
  #define DIRECTION_PORT    PORTK
  #define DIRECTION_PIN     PINK
  #define X_DIRECTION_BIT   0 // MEGA2560 Analog Pin 8
  #define Y_DIRECTION_BIT   1 // MEGA2560 Analog Pin 9
  #define Z_DIRECTION_BIT   2 // MEGA2560 Analog Pin 10
  #define A_DIRECTION_BIT   3 // MEGA2560 Analog Pin 11
  #define B_DIRECTION_BIT   4 // MEGA2560 Analog Pin 12
  #define C_DIRECTION_BIT   5 // MEGA2560 Analog Pin 13
  #define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)|(1<<B_DIRECTION_BIT)|(1<<C_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR   DDRF
  #define STEPPERS_DISABLE_PORT  PORTF
  #define STEPPERS_DISABLE_BIT   6 // MEGA2560 Analog Pin 6
  #define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // NOTE: All limit bit pins must be on the same port
  #define LIMIT_DDR       DDRB
  #define LIMIT_PORT      PORTB
  #define LIMIT_PIN       PINB
  #define X_LIMIT_BIT     4 // MEGA2560 Digital Pin 10
  #define Y_LIMIT_BIT     5 // MEGA2560 Digital Pin 11
  #define Z_LIMIT_BIT     6 // MEGA2560 Digital Pin 12
  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect  PCINT0_vect
  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_DDR      DDRF
  #define SPINDLE_ENABLE_PORT     PORTF
  #define SPINDLE_ENABLE_BIT      7 // MEGA2560 Analog Pin 7
  #define SPINDLE_DIRECTION_DDR   DDRK
  #define SPINDLE_DIRECTION_PORT  PORTK
  #define SPINDLE_DIRECTION_BIT   6 // MEGA2560 Analog Pin 14 

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_DDR   DDRH
  #define COOLANT_FLOOD_PORT  PORTH
  #define COOLANT_FLOOD_BIT   0 // MEGA2560 Digital Pin 17
  #define COOLANT_MIST_DDR    DDRH
  #define COOLANT_MIST_PORT   PORTH
  #define COOLANT_MIST_BIT    1 // MEGA2560 Digital Pin 16

  // Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       DDRD
  #define CONTROL_PIN       PIND
  #define CONTROL_PORT      PORTD
  #define CONTROL_RESET_BIT         3  // MEGA2560 Digital Pin 18
  #define CONTROL_FEED_HOLD_BIT     2  // MEGA2560 Digital Pin 19
  #define CONTROL_CYCLE_START_BIT   1  // MEGA2560 Digital Pin 20
  #define CONTROL_SAFETY_DOOR_BIT   0  // MEGA2560 Digital Pin 21
  #define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT2_vect
  #define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
  #define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
  #define PROBE_DDR       DDRK
  #define PROBE_PIN       PINK
  #define PROBE_PORT      PORTK
  #define PROBE_BIT       7  // MEGA2560 Analog Pin 15
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 8 - Ramps 1.4 12v output with heat sink
  #define SPINDLE_PWM_MAX_VALUE     1024.0 // Translates to about 1.9 kHz PWM frequency at 1/8 prescaler
  #ifndef SPINDLE_PWM_MIN_VALUE
  #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

  //Control Digital Pin 6 which is Servo 2 signal pin on Ramps 1.4 board
  #define SPINDLE_TCCRA_REGISTER    TCCR4A
  #define SPINDLE_TCCRB_REGISTER    TCCR4B
  #define SPINDLE_OCR_REGISTER      OCR4C
  #define SPINDLE_COMB_BIT          COM4C1

  // 1/8 Prescaler, 16-bit Fast PWM mode
  #define SPINDLE_TCCRA_INIT_MASK ((1<<WGM40) | (1<<WGM41))
  #define SPINDLE_TCCRB_INIT_MASK ((1<<WGM42) | (1<<WGM43) | (1<<CS41))
  #define SPINDLE_OCRA_REGISTER   OCR4A // 16-bit Fast PWM mode requires top reset value stored here.
  #define SPINDLE_OCRA_TOP_VALUE  0x0400 // PWM counter reset value. Should be the same as PWM_MAX_VALUE in hex.

  // Define spindle output pins.
  #define SPINDLE_PWM_DDR   DDRH
  #define SPINDLE_PWM_PORT  PORTH
  #define SPINDLE_PWM_BIT   5 // MEGA2560 Digital Pin 8
  
  
#endif //CPU_MAP_2560_YK


#ifdef CPU_MAP_2560_RAMPS_BOARD // (Arduino Mega 2560) with Ramps 1.4 Board
  #include "nuts_bolts.h"

  // Serial port interrupt vectors
  #define SERIAL_RX USART0_RX_vect
  #define SERIAL_UDRE USART0_UDRE_vect

  // Define ports and pins
  #define DDR(port) DDR##port
  #define _DDR(port) DDR(port)
  #define PORT(port) PORT##port
  #define _PORT(port) PORT(port)
  #define PIN(pin) PIN##pin
  #define _PIN(pin) PIN(pin)

  // Define step pulse output pins.

  #define STEP_PORT_0 F
  #define STEP_PORT_1 F
  #define STEP_PORT_2 L
  #if N_AXIS > 3
    #define STEP_PORT_3 A // Axis number 4 (Ramps E0)
  #endif
  #if N_AXIS > 4
    #define STEP_PORT_4 C // Axis number 5 (Ramps E1)
  #endif
  #if N_AXIS > 5
    #define STEP_PORT_5 L // Axis number 6 (Ramps Aux-3 D49)
  #endif
  #define STEP_BIT_0 0  // X Step - Pin A0
  #define STEP_BIT_1 6  // Y Step - Pin A6
  #define STEP_BIT_2 3  // Z Step - Pin D46
  #if N_AXIS > 3
    #define STEP_BIT_3 4 // Axis number 4 Step - Pin D26
  #endif
  #if N_AXIS > 4
    #define STEP_BIT_4 1 // Axis number 5 Step - Pin D36
  #endif
  #if N_AXIS > 5
    #define STEP_BIT_5 0 // Axis number 6 Step - Pin D49
  #endif
  #define _STEP_BIT(i) STEP_BIT_##i
  #define STEP_BIT(i) _STEP_BIT(i)
  #define STEP_DDR(i) _DDR(STEP_PORT_##i)
  #define _STEP_PORT(i) _PORT(STEP_PORT_##i)
  #define STEP_PORT(i) _STEP_PORT(i)
  #define STEP_PIN(i) _PIN(STEP_PORT_##i)

  // Define step direction output pins.
  #define DIRECTION_PORT_0 F
  #define DIRECTION_PORT_1 F
  #define DIRECTION_PORT_2 L
  #if N_AXIS > 3
    #define DIRECTION_PORT_3 A // Axis number 4 (Ramps E0)
  #endif
  #if N_AXIS > 4
    #define DIRECTION_PORT_4 C // Axis number 5 (Ramps E1)
  #endif
  #if N_AXIS > 5
    #define DIRECTION_PORT_5 B // Axis number 6 (Ramps Aux-3 D51)
  #endif
  #define DIRECTION_BIT_0 1 // X Dir - Pin A1
  #define DIRECTION_BIT_1 7 // Y Dir - Pin A7
  #define DIRECTION_BIT_2 1 // Z Dir - Pin D48
  #if N_AXIS > 3
    #define DIRECTION_BIT_3 6 // Axis number 4 Step - Pin D28
  #endif
  #if N_AXIS > 4
    #define DIRECTION_BIT_4 3 // Axis number 5 Step - Pin D34
  #endif
  #if N_AXIS > 5
    #define DIRECTION_BIT_5 2 // Axis number 6 Step - Pin D51
  #endif
  #define _DIRECTION_BIT(i) DIRECTION_BIT_##i
  #define DIRECTION_BIT(i) _DIRECTION_BIT(i)
  #define DIRECTION_DDR(i) _DDR(DIRECTION_PORT_##i)
  #define _DIRECTION_PORT(i) _PORT(DIRECTION_PORT_##i)
  #define DIRECTION_PORT(i) _DIRECTION_PORT(i)
  #define DIRECTION_PIN(i) _PIN(DIRECTION_PORT_##i)

  // Define stepper driver enable/disable output pin.
  #define STEPPER_DISABLE_PORT_0 D
  #define STEPPER_DISABLE_PORT_1 F
  #define STEPPER_DISABLE_PORT_2 K
  #if N_AXIS > 3
    #define STEPPER_DISABLE_PORT_3 A // Axis number 4 (Ramps E0)
  #endif
  #if N_AXIS > 4
    #define STEPPER_DISABLE_PORT_4 C // Axis number 5 (Ramps E1)
  #endif
  #if N_AXIS > 5
    #define STEPPER_DISABLE_PORT_5 B // Axis number 5 (Ramps Aux-3 D53)
  #endif
  #define STEPPER_DISABLE_BIT_0 7 // X Enable - Pin D38
  #define STEPPER_DISABLE_BIT_1 2 // Y Enable - Pin A2
  #define STEPPER_DISABLE_BIT_2 0 // Z Enable - Pin A8
  #if N_AXIS > 3
    #define STEPPER_DISABLE_BIT_3 2 // Axis number 4 Step - Pin D24
  #endif
  #if N_AXIS > 4
    #define STEPPER_DISABLE_BIT_4 7 // Axis number 5 Step - Pin D30
  #endif
  #if N_AXIS > 5
    #define STEPPER_DISABLE_BIT_5 0 // Axis number 5 Step - Pin D53
  #endif
  #define STEPPER_DISABLE_BIT(i) STEPPER_DISABLE_BIT_##i
  #define STEPPER_DISABLE_DDR(i) _DDR(STEPPER_DISABLE_PORT_##i)
  #define STEPPER_DISABLE_PORT(i) _PORT(STEPPER_DISABLE_PORT_##i)
  #define STEPPER_DISABLE_PIN(i) _PIN(STEPPER_DISABLE_PORT_##i)

  // Define homing/hard limit switch input pins and limit interrupt vectors.
  #define MIN_LIMIT_PORT_0 E
  #define MIN_LIMIT_PORT_1 J
  #define MIN_LIMIT_PORT_2 D
  #if N_AXIS > 3
    #define MIN_LIMIT_PORT_3 L
  #endif
  #if N_AXIS > 4
    #define MIN_LIMIT_PORT_4 L
  #endif
  #if N_AXIS > 5
    #define MIN_LIMIT_PORT_5 F // (Ramps Aux-1 D57)
  #endif
  #define MIN_LIMIT_BIT_0 5 // X Limit Min - Pin D3
  #define MIN_LIMIT_BIT_1 1 // Y Limit Min - Pin D14
  #define MIN_LIMIT_BIT_2 3 // Z Limit Min - Pin D18
  #if N_AXIS > 3
    #define MIN_LIMIT_BIT_3 7 // Axis number 4 : RAMPS AUX2 pin D42
  #endif
  #if N_AXIS > 4
    #define MIN_LIMIT_BIT_4 5 // Axis number 5 : RAMPS AUX2 pin D44
  #endif
  #if N_AXIS > 5
    #define MIN_LIMIT_BIT_5 3 // Axis number 6 : RAMPS AUX2 pin D57
  #endif
  #define _MIN_LIMIT_BIT(i) MIN_LIMIT_BIT_##i
  #define MIN_LIMIT_BIT(i) _MIN_LIMIT_BIT(i)
  #define MIN_LIMIT_DDR(i) _DDR(MIN_LIMIT_PORT_##i)
  #define MIN_LIMIT_PORT(i) _PORT(MIN_LIMIT_PORT_##i)
  #define MIN_LIMIT_PIN(i) _PIN(MIN_LIMIT_PORT_##i)

  #define MAX_LIMIT_PORT_0 E
  #define MAX_LIMIT_PORT_1 J
  #define MAX_LIMIT_PORT_2 D
  #if N_AXIS > 3
    #define MAX_LIMIT_PORT_3 G
  #endif
  #if N_AXIS > 4
    #define MAX_LIMIT_PORT_4 F
  #endif
  #if N_AXIS > 5
    #define MAX_LIMIT_PORT_5 F // (Ramps Aux-3 D58)
  #endif
  #define MAX_LIMIT_BIT_0 4 // X Limit Max - Pin D2
  #define MAX_LIMIT_BIT_1 0 // Y Limit Max - Pin D15
  #define MAX_LIMIT_BIT_2 2 // Z Limit Max - Pin D19
  #if N_AXIS > 3
    #define MAX_LIMIT_BIT_3 1 // Axis number 4 : RAMPS AUX2 pin D40
  #endif
  #if N_AXIS > 4
    #define MAX_LIMIT_BIT_4 5 // Axis number 5 : RAMPS AUX2 pin D59
  #endif
  #if N_AXIS > 5
    #define MAX_LIMIT_BIT_5 4 // Axis number 6 : RAMPS AUX2 pin D58
  #endif
  #define _MAX_LIMIT_BIT(i) MAX_LIMIT_BIT_##i
  #define MAX_LIMIT_BIT(i) _MAX_LIMIT_BIT(i)
  #define MAX_LIMIT_DDR(i) _DDR(MAX_LIMIT_PORT_##i)
  #define MAX_LIMIT_PORT(i) _PORT(MAX_LIMIT_PORT_##i)
  #define MAX_LIMIT_PIN(i) _PIN(MAX_LIMIT_PORT_##i)

  //  #define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
  //  #define LIMIT_INT_vect  PCINT0_vect
  //  #define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
  //  #define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
  #define DISABLE_HW_LIMITS

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_DDR      DDRG
  #define SPINDLE_ENABLE_PORT     PORTG
  #define SPINDLE_ENABLE_BIT      5 // MEGA2560 Digital Pin 4 - Ramps 1.4 Servo 4 Signal pin (D4)
  #define SPINDLE_DIRECTION_DDR   DDRE
  #define SPINDLE_DIRECTION_PORT  PORTE
  #define SPINDLE_DIRECTION_BIT   3 // MEGA2560 Digital Pin 5 - Ramps 1.4 Servo 3 Signal pin (D5)

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_DDR   DDRB
  #define COOLANT_FLOOD_PORT  PORTB
  #define COOLANT_FLOOD_BIT   4 // MEGA2560 Digital Pin 10 - Ramps 1.4 12v output
  #define COOLANT_MIST_DDR    DDRH
  #define COOLANT_MIST_PORT   PORTH
  #define COOLANT_MIST_BIT    6 // MEGA2560 Digital Pin 9 - Ramps 1.4 12v output

  // Define user-control CONTROLs (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       DDRK
  #define CONTROL_PIN       PINK
  #define CONTROL_PORT      PORTK
  #define CONTROL_RESET_BIT         1  // Pin A9 - RAMPS Aux 2 Port
  #define CONTROL_FEED_HOLD_BIT     2  // Pin A10 - RAMPS Aux 2 Port
  #define CONTROL_CYCLE_START_BIT   3  // Pin A11 - RAMPS Aux 2 Port
  #define CONTROL_SAFETY_DOOR_BIT   4  // Pin A12 - RAMPS Aux 2 Port
  #define CONTROL_INT       PCIE2  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT2_vect
  #define CONTROL_PCMSK     PCMSK2 // Pin change interrupt register
  #define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
  #define PROBE_DDR       DDRK
  #define PROBE_PIN       PINK
  #define PROBE_PORT      PORTK
  #define PROBE_BIT       7  // MEGA2560 Analog Pin 15
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Advanced Configuration Below You should not need to touch these variables
  // Set Timer up to use TIMER4B which is attached to Digital Pin 8 - Ramps 1.4 12v output with heat sink
  #define SPINDLE_PWM_MAX_VALUE     1024.0 // Translates to about 1.9 kHz PWM frequency at 1/8 prescaler
  #ifndef SPINDLE_PWM_MIN_VALUE
  #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

  //Control Digital Pin 6 which is Servo 2 signal pin on Ramps 1.4 board
  #define SPINDLE_TCCRA_REGISTER    TCCR4A
  #define SPINDLE_TCCRB_REGISTER    TCCR4B
  #define SPINDLE_OCR_REGISTER      OCR4C
  #define SPINDLE_COMB_BIT          COM4C1

  // 1/8 Prescaler, 16-bit Fast PWM mode
  #define SPINDLE_TCCRA_INIT_MASK ((1<<WGM40) | (1<<WGM41))
  #define SPINDLE_TCCRB_INIT_MASK ((1<<WGM42) | (1<<WGM43) | (1<<CS41))
  #define SPINDLE_OCRA_REGISTER   OCR4A // 16-bit Fast PWM mode requires top reset value stored here.
  #define SPINDLE_OCRA_TOP_VALUE  0x0400 // PWM counter reset value. Should be the same as PWM_MAX_VALUE in hex.

  // Define spindle output pins.
  #define SPINDLE_PWM_DDR   DDRH
  #define SPINDLE_PWM_PORT  PORTH
  #define SPINDLE_PWM_BIT   5 // MEGA2560 Digital Pin 8

#endif
/*
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
