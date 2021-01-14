#include QMK_KEYBOARD_H

#define RGB_STEPS 16
#define LED_INDEX_START 8

enum uno_keycode
{
  UNO = SAFE_RANGE
};

enum encoder_names {
	_ENCODER,
};

uint8_t ledIndex = LED_INDEX_START;
uint8_t spaceHeld = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        UNO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case UNO:
            if (record->event.pressed) {
            } else {
                /* this is a dumb hack for "temp unmute" in zoom */
                if (spaceHeld) {
                    unregister_code(KC_SPC);
                    spaceHeld = 0;
                } else {
                    register_code(KC_SPC);
                    spaceHeld = 1;
                }
            }
        break;
    }
    return false;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_sethsv_noeeprom((255/RGB_STEPS)*ledIndex, 255, 255);
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
