/*
This is a keymap for doing some volume and scrolling stuff 
with the Uno v2. Started with the copypasta keymap
by u/Snipeye and got out of hand. :)

Copyright 2021 Dan Wright <dtwright@gmail.com>

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

#include QMK_KEYBOARD_H
#include "print.h"

#define RGB_STEPS 16
#define LED_INDEX_START 8
#define VOL_COLOR 128

uint8_t ledIndex = LED_INDEX_START;

enum uno_keycode
{
    MUTE = SAFE_RANGE
};

enum encoder_names {
    _ENCODER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MEDIA
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MEDIA:
        if (record->event.pressed) {
        } else {
            register_code(KC_MPLY);
            unregister_code(KC_MPLY);
        }
        break;
    }
    return false;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_sethsv_noeeprom(VOL_COLOR, 255, 255);

    // set to true to get hid console output from various print statements
    debug_enable = false;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) { /* First encoder */
        if (clockwise) {
            ledIndex++;
            ledIndex %= RGB_STEPS;
            register_code(KC_VOLU);
            unregister_code(KC_VOLU);
        } else {
            ledIndex += RGB_STEPS;
            ledIndex--;
            ledIndex %= RGB_STEPS;
            register_code(KC_VOLD);
            unregister_code(KC_VOLD);
        }
        // Uncomment the following 2 lines and the "ledIndex" lines above to 
        // change colors as the encoder turns.
        rgblight_sethsv_noeeprom((255/RGB_STEPS)*ledIndex, 255, 255);
        rgblight_mode_noeeprom(1);
    }
}
