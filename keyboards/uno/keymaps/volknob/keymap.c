#include QMK_KEYBOARD_H

#define RGB_STEPS 16
#define LED_INDEX_START 8
#define SCROLL_HOLD_TIME 1000

enum uno_keycode
{
  UNO = SAFE_RANGE
};

enum encoder_names {
	_ENCODER,
};

uint16_t scrollTimer = 0;
uint8_t scrollClicks = 0;
// uint16_t scrollKeyCode = 0;
bool scrollMode = false;
bool scrollHoriz = false;

uint8_t ledIndex = LED_INDEX_START;

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
                if(scrollMode) {
                    scrollClicks++;
                    if(scrollTimer == 0) scrollTimer = timer_read();
                    if(timer_elapsed(scrollTimer) < SCROLL_HOLD_TIME && scrollClicks > 1) {
                        if(scrollHoriz) {
                            scrollHoriz = false;
                        } else {
                            scrollHoriz = true;
                        }
                        scrollClicks = 0;
                    } else if(timer_elapsed(scrollTimer) > SCROLL_HOLD_TIME) {
                        scrollMode = 0;
                    }
                    scrollTimer = timer_read();
                } else {
                    scrollMode = 1;
                    scrollClicks = 0;
                    scrollTimer = 0;
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
            if(!scrollMode) {
                register_code(KC_VOLU);
                unregister_code(KC_VOLU);
            } else {
                if(scrollHoriz) {
                    register_code(KC_WH_R);
                    unregister_code(KC_WH_R);
                } else {
                    register_code(KC_WH_D);
                    unregister_code(KC_WH_D);
                }
            }
        } else {
            ledIndex += RGB_STEPS;
            ledIndex--;
            ledIndex %= RGB_STEPS;
            if(!scrollMode) {
                register_code(KC_VOLD);
                unregister_code(KC_VOLD);
            } else {
                if(scrollHoriz) {
                    register_code(KC_WH_L);
                    unregister_code(KC_WH_L);
                } else {
                    register_code(KC_WH_U);
                    unregister_code(KC_WH_U);
                }
            }
        }
        rgblight_sethsv_noeeprom((255/RGB_STEPS)*ledIndex, 255, 255);
        rgblight_mode_noeeprom(1);
    }
}

/*
void matrix_scan_user(void) {
    if(scrollMode && isScrolling) {
        if(timer_elapsed(scrollTimer) > SCROLL_HOLD_TIME) {
            unregister_code(scrollKeyCode);
            isScrolling = false;
        }
    }
}
*/
