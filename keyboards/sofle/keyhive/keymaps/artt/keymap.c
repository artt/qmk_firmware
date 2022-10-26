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
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD
};

enum custom_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NAV
};

// Extra keys are added for rotary encoder support in VIA
#define LAYOUT_via( \
    LA1, LA2, LA3, LA4, LA5, LA6,             RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6, LB7,   RB7, RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6, LE1,   RE6, RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, LD7,   RD7, RD6, RD5, RD4, RD3, RD2, RD1, \
              LE2, LE3, LE4, LE5, LE6,   RE5, RE4, RE3, RE2, RE1 \
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


#include "sofle.h"

#define CS 18
#define RS 18
#define XC0 5
#define XC1 5
#define XC2 2
#define XC3 0
#define XC4 2
#define XC5 3
#define T1X 4
#define T1Y 4
#define T2X 15 // shift from T1
#define T2Y 6  // shift from T1
#define WD ((CS*5+T1X+T2X)*2+20)
#define USHF -5

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {      33,  32,  24,  23,  14,  13,  NO_LED },
        {      34,  31,  25,  22,  15,  12,  NO_LED },
        {      35,  30,  26,  21,  16,  11,  NO_LED },
        {      36,  29,  27,  20,  17,  10,  NO_LED },
        {  NO_LED,  28,  19,  18,   9,   8,  NO_LED },
        {      70,  69,  61,  60,  51,  50,  NO_LED},
        {      71,  68,  62,  59,  52,  49,  NO_LED},
        {      72,  67,  63,  58,  53,  48,  NO_LED},
        {      73,  66,  64,  57,  54,  47,  NO_LED},
        {      65,  56,  55,  46,  45,  NO_LED,  NO_LED }
    },
    {
        // left side underglow
        {CS*4, RS*1+XC4+USHF}, {CS*2, RS*1+XC2+USHF}, {CS*0, RS*1+XC0+USHF},
        {CS*0, RS*3+XC0+USHF}, {CS*2, RS*3+XC2+USHF}, {CS*4, RS*3+XC4+USHF},
        {CS*2-8, RS*4+XC2+4}, {CS*5+T2X+5, RS*4+XC5+T2Y-12},
        // left side matrix
        {CS*5 + T2X, RS*4+XC5 + T2Y}, 
        {CS*5 + T1X, RS*4+XC5 + T1Y}, {CS*5, RS*3+XC5}, {CS*5, RS*2+XC5}, {CS*5, RS*1+XC5}, {CS*5, RS*0+XC5},
                    {CS*4, RS*0+XC4}, {CS*4, RS*1+XC4}, {CS*4, RS*2+XC4}, {CS*4, RS*3+XC4}, {CS*4, RS*4+XC4},
                    {CS*3, RS*4+XC3}, {CS*3, RS*3+XC3}, {CS*3, RS*2+XC3}, {CS*3, RS*1+XC3}, {CS*3, RS*0+XC3},
                    {CS*2, RS*0+XC2}, {CS*2, RS*1+XC2}, {CS*2, RS*2+XC2}, {CS*2, RS*3+XC2}, {CS*2, RS*4+XC2},
                    {CS*1, RS*3+XC1}, {CS*1, RS*2+XC1}, {CS*1, RS*1+XC1}, {CS*1, RS*0+XC1},
                    {CS*0, RS*0+XC0}, {CS*0, RS*1+XC0}, {CS*0, RS*2+XC0}, {CS*0, RS*3+XC0},
        // right side underglow
        {WD-CS*4, RS*1+XC4+USHF}, {WD-CS*2, RS*1+XC2+USHF}, {WD-CS*0, RS*1+XC0+USHF},
        {WD-CS*0, RS*3+XC0+USHF}, {WD-CS*2, RS*3+XC2+USHF}, {WD-CS*4, RS*3+XC4+USHF},
        {WD-(CS*2-8), RS*4+XC2+4}, {WD-(CS*5+T2X+5), RS*4+XC5+T2Y-12},
        // right side matrix
        {WD-(CS*5 + T2X), RS*4+XC5 + T2Y}, 
        {WD-(CS*5 + T1X), RS*4+XC5 + T1Y}, {WD-CS*5, RS*3+XC5}, {WD-CS*5, RS*2+XC5}, {WD-CS*5, RS*1+XC5}, {WD-CS*5, RS*0+XC5},
                      {WD-CS*4, RS*0+XC4}, {WD-CS*4, RS*1+XC4}, {WD-CS*4, RS*2+XC4}, {WD-CS*4, RS*3+XC4}, {WD-CS*4, RS*4+XC4},
                      {WD-CS*3, RS*4+XC3}, {WD-CS*3, RS*3+XC3}, {WD-CS*3, RS*2+XC3}, {WD-CS*3, RS*1+XC3}, {WD-CS*3, RS*0+XC3},
                      {WD-CS*2, RS*0+XC2}, {WD-CS*2, RS*1+XC2}, {WD-CS*2, RS*2+XC2}, {WD-CS*2, RS*3+XC2}, {WD-CS*2, RS*4+XC2},
                      {WD-CS*1, RS*3+XC1}, {WD-CS*1, RS*2+XC1}, {WD-CS*1, RS*1+XC1}, {WD-CS*1, RS*0+XC1},
                      {WD-CS*0, RS*0+XC0}, {WD-CS*0, RS*1+XC0}, {WD-CS*0, RS*2+XC0}, {WD-CS*0, RS*3+XC0},
    },
    {
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif


#define LO_ENT LT(_LOWER, KC_ENT)
#define NAV_MIN LT(_NAV, KC_MINUS)
#define RA_SPC LT(_RAISE, KC_SPC)
#define SHF_BSPC SFT_T(KC_BSPC)

#define GUI_LBRK LGUI(KC_LBRACKET)
#define GUI_RBRK LGUI(KC_RBRACKET)
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
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  QK_GESC,  KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   ,  KC_PGDN,       KC_VOLD,  KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   ,  KC_BSPC,
  KC_TAB,   KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G   ,  KC_MPLY,       KC_MUTE,  KC_H   ,  KC_J   ,  KC_K   ,  KC_L   ,  KC_SCLN,  KC_QUOT,
  KC_LALT,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B   ,  KC_PGUP,       KC_VOLU,  KC_N   ,  KC_M   ,  KC_COMM,  KC_DOT ,  KC_SLSH,  KC_LCTRL,
                      XXXXXXX,  XXXXXXX,  KC_LGUI,  LO_ENT ,  SHF_BSPC,      NAV_MIN,  RA_SPC ,  SHF_BSPC, XXXXXXX,  XXXXXXX
),

[_LOWER] = LAYOUT_via(
  _______,  _______,  _______,  _______,  _______,  _______,                           _______,  _______,  _______,  _______,  _______,  _______,
  KC_GRV,   GUI_LBRK, GUI_RBRK, LBRK,     RBRK,     _______,  _______,       _______,  KC_PSLS,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PAST,  _______,
  KC_DEL,   KC_LABK,  KC_RABK,  KC_LPRN,  KC_RPRN,  _______,  _______,       _______,  KC_PMNS,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PPLS,  _______,
  _______,  _______,  _______,  KC_LCBR,  KC_RCBR,  _______,  _______,       _______,  KC_PDOT,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_EQL,   _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  KC_KP_0,  _______,  _______
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
  _______,  _______,  _______,  KC_MS_U,  _______,  _______,  _______,       _______,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,
  _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  _______,       _______,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,
  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,  KC_ACL0,  KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_ACL2,  _______,
                      _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,  _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MISSION_CONTROL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case QK_GESC:
            // Detect the activation of only Left Alt
            if ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT)) {
                if (record->event.pressed) {
                    del_mods(MOD_MASK_ALT);
                    register_code(KC_GRAVE);
                    register_code(KC_LALT);
                } else {
                    unregister_code(KC_GRAVE);
                }
                return false;
            }
            return true;
        default:
            return true;  // Process all other keycodes normally
    }
}

void matrix_init_user(void) {
    // turn off 
    set_bit_c_LED(LED_OFF);
}