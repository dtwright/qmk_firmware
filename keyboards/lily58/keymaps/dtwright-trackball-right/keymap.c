#include QMK_KEYBOARD_H
#ifdef POINTING_DEVICE_ENABLE
#include "pointing_device.h"
#endif

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pimoroni_trackball.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
  _ARROWS
};

enum {
    TD_CMD_ALT = 0,
    TD_ALT_CMD,
    TD_CMD_CTL
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CMD_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_RGUI, KC_RALT),
    [TD_ALT_CMD] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    [TD_CMD_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_LCMD, KC_LCTL),
};

enum combos {
    QA_1 = 0,
    WS_2,
    ED_3,
    RF_4,
    TG_5,
    YH_6,
    UJ_7,
    IK_8,
    OL_9,
    PSCLN_0
};

const uint16_t PROGMEM combo_1[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM combo_2[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM combo_3[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM combo_4[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM combo_5[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_6[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM combo_7[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM combo_8[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM combo_9[] = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM combo_0[] = {KC_P, KC_SCLN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [QA_1] = COMBO(combo_1, KC_1),
    [WS_2] = COMBO(combo_2, KC_2),
    [ED_3] = COMBO(combo_3, KC_3),
    [RF_4] = COMBO(combo_4, KC_4),
    [TG_5] = COMBO(combo_5, KC_5),
    [YH_6] = COMBO(combo_6, KC_6),
    [UJ_7] = COMBO(combo_7, KC_7),
    [IK_8] = COMBO(combo_8, KC_8),
    [OL_9] = COMBO(combo_9, KC_9),
    [PSCLN_0] = COMBO(combo_0, KC_0),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT, \
  KC_GRV,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RCTL, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                    KC_LALT, TD(TD_CMD_CTL), MO(_LOWER), LT(_ARROWS, KC_ENT), LT(_MOUSE, KC_SPC), MO(_RAISE), TD(TD_CMD_CTL), KC_RALT \
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,\
  XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, KC_F6,                     KC_BTN3, KC_BTN2, _______, _______, _______, _______, \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_CIRC, KC_UNDS, KC_PLUS, KC_LPRN, KC_RPRN, _______, \
  KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, XXXXXXX, _______, _______, KC_HOME, KC_END,  _______, \
                             _______, _______, _______, _______, KC_BTN1,  _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX, \
  KC_CAPS, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_F12,  XXXXXXX, XXXXXXX, KC_PGDN, KC_PGUP, KC_BSLS, \
                             _______, LGUI(KC_4), _______,  _______, _______,  _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),

  /* Mouse
   */
  [_MOUSE] = LAYOUT( \
  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  XXXXXXX, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_U, XXXXXXX,                   KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, _______, \
  _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_R, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,\
                             _______, _______, _______, KC_BSPC, _______,  _______, _______, _______ \
  ),

  /* Arrows
   */
  [_ARROWS] = LAYOUT( \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX, _______, \
  _______, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, XXXXXXX,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,XXXXXXX, _______, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, _______,\
                             _______, _______, _______, _______, KC_SPC,  _______, _______, _______ \
  )
           
};


// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  oled_write(read_logo(), false);
  return;
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

#ifdef PIMORONI_TRACKBALL_ENABLE
void pointing_device_task() {
    report_mouse_t mouse_report = pointing_device_get_report();

    if (is_keyboard_master()) {
        process_mouse(&mouse_report);
    }

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            trackball_set_rgbw(0,0,0,120);
            break;
        case _LOWER:
            trackball_set_rgbw(0,153,95,0);
            break;
        case _RAISE:
            trackball_set_rgbw(153,113,0,0);
            break;
        case _MOUSE:
            trackball_set_rgbw(20,200,0,0);
            break;
        case _ARROWS:
            trackball_set_rgbw(200,50,100,0);
            break;
        default:
            trackball_set_rgbw(0,0,0,0);
    }


    if (layer_state_is(_ARROWS)) {
        trackball_set_scrolling(true);
    } else {
        trackball_set_scrolling(false);
    }

    pointing_device_set_report(mouse_report);
    pointing_device_send();
}
#endif


