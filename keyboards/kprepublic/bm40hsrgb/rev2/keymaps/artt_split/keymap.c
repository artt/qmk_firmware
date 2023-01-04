/* Copyright 2020 tominabox1
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

enum layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NAV
};

// enum planck_keycodes {
//   RGB_SLD = SAFE_RANGE,
// };

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define LO_ENT LT(_LOWER, KC_ENT)
#define NAV_MIN LT(_NAV, KC_MINUS)
#define RA_SPC LT(_RAISE, KC_SPC)
#define SHF_BSPC SFT_T(KC_BSPC)

#define GUI_LBRK LGUI(KC_LBRACKET)
#define GUI_RBRK LGUI(KC_RBRACKET)
#define LBRK KC_LBRACKET
#define RBRK KC_RBRACKET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x12_1x2uC(
    QK_GESC,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_CAPS,      
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,       
    KC_LALT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMMA, KC_DOT,   KC_SLSH,  KC_LCTRL, 
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LGUI,  LO_ENT,   SHF_BSPC,           RA_SPC,   NAV_MIN,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),


  [_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    KC_GRV,   GUI_LBRK, GUI_RBRK, LBRK,     RBRK,     _______,  KC_PSLS,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PAST,  _______, 
    KC_DEL,   KC_LABK,  KC_RABK,  KC_LPRN,  KC_RPRN,  _______,  KC_PMNS,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PPLS,  _______, 
    _______,  _______,  _______,  KC_LCBR,  KC_RCBR,  KC_PCMM,  KC_PDOT,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_EQL,   _______, 
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_KP_0,  _______,  _______,  _______
  ),

  [_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    _______,  KC_VOLU,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  
    KC_DEL,   KC_AT,    KC_ASTR,  KC_DLR,   KC_CIRC,  _______,  KC_MUTE,  KC_AMPR,  KC_HASH,  KC_EXLM,  KC_PERC,  _______,      
    _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,  KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_BSLS,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______
  ),

  [_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
    RESET,    _______,  DM_REC1,  DM_REC2,  DM_RSTP,  _______,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  _______,  
    _______,  _______,  DM_PLY1,  DM_PLY2,  _______,  _______,  RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______
  ),

  [_NAV] = LAYOUT_ortho_4x12_1x2uC(
    _______,  _______,  _______,  KC_MS_U,  _______,  _______,  _______,  KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  _______,  
    _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  KC_ACL2,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_PGDN,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,  KC_ACL0,  KC_BTN1,  KC_BTN3,  KC_BTN2,  _______,  _______,  
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______
  ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer > 0) {
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index <= led_max && index != NO_LED) {
                    uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    uint8_t r = 0;
                    uint8_t g = 0;
                    uint8_t b = 0;
                    if (kc == KC_LABK || kc == KC_RABK) {   // <, >
                        r = 52; g = 112; b = 255;
                    }
                    else if (kc == LBRK || kc == RBRK) {    // [, ]
                        r = 255; g = 245; b = 0;
                    }
                    else if (kc == KC_LPRN || kc == KC_RPRN) {    // (, )
                        r = 19; g = 255; b = 176;
                    }
                    else if (kc == KC_LCBR || kc == KC_RCBR) {    // {, }
                        r = 197; g = 64; b = 255;
                    }
                    else if (kc >= KC_P1 && kc <= KC_P0) {    // numpad numbers
                        r = 255; g = 255; b = 255;
                    }
                    else if (kc >= KC_NUM && kc <= KC_PEQL) {    // numpad symbols
                        r = 32; g = 32; b = 32;
                    }
                    else if (kc >= KC_F1 && kc <= KC_F12) {    // F1-F12
                        r = 32; g = 32; b = 32;
                    }
                    else if (kc == RESET) {
                        r = 255; g = 0; b = 0;
                    }
                    else if (kc == DM_REC1 || kc == DM_REC2) {  // macro record
                        r = 235; g = 204; b = 38;
                    }
                    else if (kc == DM_RSTP) {  // macro record stop
                        r = 204; g = 29; b = 29;
                    }
                    else if (kc == DM_PLY1 || kc == DM_PLY2) {  // macro play
                        r = 24; g = 228; b = 132;
                    }
                    else if (kc >= RGB_MOD && kc <= RGB_SPD) {  // rgb adjustments
                        if (kc % 2) {
                            r = 151; g = 204; b = 29;
                        }
                        else {
                            r = 230; g = 122; b = 255;
                        }
                    }
                    else if (kc >= KC_MS_U && kc <= KC_ACL2) {  // mouse controls
                        r = 23; g = 184; b = 237;
                    }
                    else if (kc >= KC_RGHT && kc <= KC_UP) {  // arrows
                        r = 66; g = 255; b = 0;
                    }
                    else if (kc >= KC_MUTE && kc <= KC_VOLD) {  // volume
                        r = 0; g = 204; b = 153;
                    }
                    else if (kc >= KC_MNXT && kc <= KC_EJCT) {  // media
                        r = 255; g = 153; b = 0;
                    }
                    else if (kc > KC_TRNS) {
                        r = 255; g = 255; b = 255;
                    }
                    rgb_matrix_set_color( index, f * r, f * g, f * b );
                }
            }
        }
    }
    else  if (layer == 0) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index <= led_max && index != NO_LED) {
                    uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (kc == XXXXXXX) {
                        rgb_matrix_set_color( index, 0, 0, 0 );
                    }
                }
            }
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    // case RGB_SLD:
    //   if (record->event.pressed) {
    //     rgblight_mode(1);
    //   }
    //   return false;
  }
  return true;
}
