/*
Copyright 2021 CapsUnlocked

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4355
#define PRODUCT_ID      0x0007
#define DEVICE_VER      0x0001
#define MANUFACTURER    CapsUnlocked
#define PRODUCT         CU7

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

#define ENCODER_RESOLUTION 1

#define ENCODERS_PAD_A { D6 }
#define ENCODERS_PAD_B { D4 }

#define MATRIX_ROW_PINS { D7, F0, F6 }
#define MATRIX_COL_PINS { F5, F7, F4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 2

#define TAPPING_TERM 295

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN F1
#ifdef RGB_DI_PIN
#define RGBLED_NUM 6
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP
// #define RGBLIGHT_ANIMATIONS
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_HUE_STEP 4 // Edited from 10 on 2/22/2022
// #define RGBLIGHT_SAT_STEP 8 // Edited from 17 on 2/22/2022
// #define RGBLIGHT_VAL_STEP 8 // Edited from 17 on 2/22/2022
#define RGBLIGHT_LIMIT_VAL 255 // Edited from 50 on 2/22/2022
#endif