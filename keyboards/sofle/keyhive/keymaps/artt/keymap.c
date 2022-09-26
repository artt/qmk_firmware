 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H

#include "encoder.c"
#include "bit-c_led.h"

// Base layer is the number of layers CYCLE selects from.
// #define BASE_LAYERS 1

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here (4 bytes)
    // CYCLE                      // cycle through first BASE_LAYERS (62 bytes)
};

enum custom_layers {
    _QWERTY,
    // _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NAV
};

// Extra keys are added for rotary encoder support in VIA
#define LAYOUT_via( \
    LA1, LA2, LA3, LA4, LA5, LA6,           RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6, LB7, RB7, RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6, LE1, RE6, RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, LD7, RD7, RD6, RD5, RD4, RD3, RD2, RD1, \
              LE2, LE3, LE4, LE5, LE6, RE5, RE4, RE3, RE2, RE1 \
    ) \
    { \
        { LA1, LA2, LA3, LA4, LA5, LA6, KC_NO }, \
        { LB1, LB2, LB3, LB4, LB5, LB6, LB7   }, \
        { LC1, LC2, LC3, LC4, LC5, LC6, KC_NO }, \
        { LD1, LD2, LD3, LD4, LD5, LD6, LD7   }, \
        { LE1, LE2, LE3, LE4, LE5, LE6, KC_NO }, \
        { RA1, RA2, RA3, RA4, RA5, RA6, KC_NO }, \
        { RB1, RB2, RB3, RB4, RB5, RB6, RB7   }, \
        { RC1, RC2, RC3, RC4, RC5, RC6, KC_NO }, \
        { RD1, RD2, RD3, RD4, RD5, RD6, RD7   }, \
        { RE1, RE2, RE3, RE4, RE5, RE6, KC_NO } \
    }

#define LO_ENT LT(_LOWER, KC_ENT)
// #define RA_MIN LT(_RAISE, KC_MINUS)
// #define NAV_SPC LT(_NAV, KC_SPC)
#define NAV_MIN LT(_NAV, KC_MINUS)
#define RA_SPC LT(_RAISE, KC_SPC)

#define GUI_ENT GUI_T(KC_ENT)
#define SHF_SPC SFT_T(KC_SPC)
#define CTLLBRK LGUI(KC_LBRACKET)
#define CTLRBRK LGUI(KC_RBRACKET)
#define LBRK KC_LBRACKET
#define RBRK KC_RBRACKET

//Default keymap. This can be changed in Via. Use oled.c to change beavior that Via cannot change.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------| VolUp |< N >| Pg Up |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |-------.  C  ,-------|   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.  D  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| VolDn |< E >| Pg Dn |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */

[_QWERTY] = LAYOUT_via(
  SHF_SPC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  QK_GESC,  KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   ,  KC_VOLU,       KC_PGUP,  KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   ,  KC_BSPC,
  KC_TAB,   KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G   ,  KC_MUTE,       KC_MPLY,  KC_H   ,  KC_J   ,  KC_K   ,  KC_L   ,  KC_SCLN,  KC_QUOT,
  KC_LSFT,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B   ,  KC_VOLD,       KC_PGDN,  KC_N   ,  KC_M   ,  KC_COMM,  KC_DOT ,  KC_SLSH,  KC_RSFT,
                      KC_LCTRL, KC_LALT,  KC_LGUI,  LO_ENT ,  KC_BSPC,       NAV_MIN,  RA_SPC ,  KC_LSFT,  XXXXXXX,  XXXXXXX
),

// still need to do cmd+bkspace on thumb

[_LOWER] = LAYOUT_via(
  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
  KC_GRV,   CTLLBRK,  CTLRBRK,  LBRK,     RBRK,     _______,  _______,       _______,  _______,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PAST,  KC_PSLS,
  KC_DEL,   KC_LABK,  KC_RABK,  KC_LCBR,  KC_RCBR,  _______,  _______,       _______,  _______,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PPLS,  KC_PMNS,
  _______,  _______,  _______,  KC_LPRN,  KC_RPRN,  _______,  _______,       _______,  _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_EQL,   _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  KC_KP_0,  KC_PCMM,  KC_PDOT
),

[_RAISE] = LAYOUT_via(
  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
  KC_TILD,  KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  _______,  _______,       _______,  _______,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,
  KC_DEL,   KC_AT,    KC_ASTR,  KC_DLR,   KC_CIRC,  _______,  _______,       _______,  KC_CIRC,  KC_AMPR,  KC_HASH,  KC_EXLM,  KC_PERC,  KC_BSLS,
  _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,  _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______
),

[_ADJUST] = LAYOUT_via(
  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
  RESET,    _______,  DM_REC1,  DM_REC2,  DM_RSTP,  _______,  _______,       _______,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  _______,
  _______,  _______,  DM_PLY1,  DM_PLY2,  _______,  _______,  _______,       _______,  RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______
),

[_NAV] = LAYOUT_via(
  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
  _______,  _______,  _______,  KC_MS_U,  _______,  _______,  _______,       _______,  _______,  KC_PGUP,  KC_UP,    KC_PGDN,  _______,  _______,
  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,       _______,  KC_ACL2,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  KC_ACL0,  KC_BTN1,  KC_BTN3,  KC_BTN2,  _______,  _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


// Custom keycode handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // handling this once instead of in each keycode uses less program memory.
    if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
        return false;
    }

    // switch (keycode) {
    //     case CYCLE:
    //         set_single_persistent_default_layer(0);
    //         // set_single_persistent_default_layer((1+get_highest_layer(default_layer_state)) % BASE_LAYERS);
    //         break;
    // }

    // this uses less memory than returning in each case.
    return keycode < SAFE_RANGE;
};

void matrix_init_user(void) {
    set_bit_c_LED(LED_OFF);
}