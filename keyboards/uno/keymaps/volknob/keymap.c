#include QMK_KEYBOARD_H

#define RGB_STEPS 32

enum uno_keycode
{
  UNO = SAFE_RANGE
};

enum encoder_names {
	_ENCODER,
};

uint8_t ledIndex = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F10
    )
};

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case UNO:
            if (record->event.pressed) {
                pressTimer = timer_read();
            } else {
                uint16_t timeElapsed = timer_elapsed(pressTimer);
                if (timeElapsed < CUSTOM_LONGPRESS) {
                    send_string(pasta[pastaIndex]);
                } else {
                    reset_keyboard();
                }
            }
        break;
    }
    return false;
}
*/

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 255, 255);
    rgblight_mode_noeeprom(1);
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) { /* First encoder */
        if (clockwise) {
            ledIndex++;
            ledIndex %= RGB_STEPS;
            // SEND_STRING(SS_TAP(X_VOLU));
            register_code(KC_VOLU);
            unregister_code(KC_VOLU);
        } else {
            ledIndex += RGB_STEPS;
            ledIndex--;
            ledIndex %= RGB_STEPS;
            // SEND_STRING(SS_TAP(X_VOLD));
            register_code(KC_VOLD);
            unregister_code(KC_VOLD);
        }
        // rgblight_sethsv_noeeprom((255/RGB_STEPS)*ledIndex, 255-(255/RGB_STEPS)*ledIndex, 255);
        rgblight_sethsv_noeeprom((255/RGB_STEPS)*ledIndex, 255, 255);
        rgblight_mode_noeeprom(1);
    }
}
