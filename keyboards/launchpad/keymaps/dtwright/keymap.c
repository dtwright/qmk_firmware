// Below layout is based upon /u/That-Canadian's planck layout
#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _ZOOM 15

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

enum custom_keycodes {
    CONF_AUDIO_MUTE = SAFE_RANGE,
    CONF_VIDEO_MUTE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CONF_AUDIO_MUTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("a"));
                SEND_STRING(SS_LCTL("d"));
            } else {
                // when keycode QMKBEST is released
            }
            break;

        case CONF_VIDEO_MUTE:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("v"));
                SEND_STRING(SS_LCTL("e"));
            } else {
                // when keycode QMKBEST is released
            }
            break;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------.
 * |   1  |  2   |
 * |------+------|
 * |   3  |  4   |
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * | FUNC |  8   |
 * `-------------'
 */
[_QWERTY] = LAYOUT( \
    LCA(KC_P), MEH(KC_P), \
    G(KC_L),   TG(_ZOOM), \
    KC_MUTE,   LCAG(KC_S), \
    KC_VOLD,   KC_VOLU  \
),

/* Function
 * ,-------------.
 * |   Q  |CALDEL|
 * |------+------|
 * |   A  |TSKMGR|
 * |------+------|
 * |   Z  |  X   |
 * |------+------|
 * |      |  C   |
 * `-------------'
 */
[_ZOOM] = LAYOUT( \
    A(KC_Q), _______, \
    KC_NO,   TG(_ZOOM), \
    _______, _______, \
    CONF_AUDIO_MUTE, CONF_VIDEO_MUTE \
)

};

void matrix_init_user(void) {

}
