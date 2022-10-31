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
    _______,  _______,  _______,  KC_LCBR,  KC_RCBR,  _______,  KC_PDOT,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_EQL,   _______, 
    _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_KP_0,  _______,  _______,  _______
  ),

  [_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    _______,  _______,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  
    KC_DEL,   KC_AT,    KC_ASTR,  KC_DLR,   KC_CIRC,  _______,  _______,  KC_AMPR,  KC_HASH,  KC_EXLM,  KC_PERC,  KC_BSLS,      
    _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  
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

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    // [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {159,203,255}, {159,203,255}, {201,191,255}, {201,191,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {114,236,255}, {114,236,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0} },
    [2] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
    [3] = { {0,255,255}, {0,0,0}, {36,213,235}, {36,213,235}, {0,218,204}, {0,0,0}, {56,218,204}, {56,218,204}, {56,218,204}, {56,218,204}, {56,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {139,230,246}, {139,230,246}, {0,0,0}, {0,0,0}, {206,132,255}, {206,132,255}, {206,132,255}, {206,132,255}, {206,132,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255} },
    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {139,230,237}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {139,230,237}, {139,230,237}, {139,230,237}, {0,0,0}, {139,230,237}, {74,255,255}, {74,255,255}, {74,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {139,230,237}, {139,230,237}, {139,230,237}, {139,230,237}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
//   if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    // case 0:
    //   set_layer_color(0);
    //   break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    default:
      if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
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
