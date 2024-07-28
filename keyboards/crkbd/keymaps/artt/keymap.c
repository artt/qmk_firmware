/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include <stdio.h>

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,  // can always be here (4 bytes)
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD
};

enum custom_layers {
    _BASE,
    _NUM,
    _SYM,
    _ADJUST,
    _NAV
};

#define LO_ENT LT(_NUM, KC_ENT)
#define NAV_MIN LT(_NAV, KC_MINUS)
#define RA_SPC LT(_SYM, KC_SPC)
#define SHF_BSPC SFT_T(KC_BSPC)

#define GUI_LBRK LGUI(KC_LBRACKET)
#define GUI_RBRK LGUI(KC_RBRACKET)
#define LBRK KC_LBRACKET
#define RBRK KC_RBRACKET
// #define GUI_CAPS LGUI(KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_3x6_3(
    KC_ESC,   KC_Q   ,  KC_W   ,  KC_E   ,  KC_R   ,  KC_T   ,         KC_Y   ,  KC_U   ,  KC_I   ,  KC_O   ,  KC_P   ,  KC_CAPS,
    KC_TAB,   KC_A   ,  KC_S   ,  KC_D   ,  KC_F   ,  KC_G   ,         KC_H   ,  KC_J   ,  KC_K   ,  KC_L   ,  KC_SCLN,  KC_QUOT,
    KC_LALT,  KC_Z   ,  KC_X   ,  KC_C   ,  KC_V   ,  KC_B   ,         KC_N   ,  KC_M   ,  KC_COMM,  KC_DOT ,  KC_SLSH,  KC_LCTRL,
                                  KC_LGUI,  LO_ENT ,  SHF_BSPC,        SHF_BSPC, RA_SPC ,  NAV_MIN
),

[_NUM] = LAYOUT_split_3x6_3(
    _______,  GUI_LBRK, GUI_RBRK, LBRK,     RBRK,     XXXXXXX,         KC_PSLS,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PAST,  XXXXXXX,
    KC_DEL,   KC_LABK,  KC_RABK,  KC_LPRN,  KC_RPRN,  XXXXXXX,         KC_PMNS,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PPLS,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  KC_LCBR,  KC_RCBR,  KC_COMMA,        KC_PDOT,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_PEQL,  _______,
                                  _______,  _______,  _______,         _______,  _______,  KC_KP_0
),

[_SYM] = LAYOUT_split_3x6_3(
    KC_GRV,   KC_F1  ,  KC_F2  ,  KC_F3  ,  KC_F4  ,  XXXXXXX,         KC_VOLU,  KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,
    KC_DEL,   KC_AT,    KC_ASTR,  KC_DLR,   KC_CIRC,  XXXXXXX,         KC_MUTE,  KC_AMPR,  KC_HASH,  KC_EXLM,  KC_PERC,  KC_GRV,
    _______,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    XXXXXXX,         KC_VOLD,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_BSLS,  _______,
                                  _______,  _______,  _______,         _______,  _______,  _______
),

[_ADJUST] = LAYOUT_split_3x6_3(
    QK_BOOT,  XXXXXXX,  DM_REC1,  DM_REC2,  DM_RSTP,  XXXXXXX,         RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  DM_PLY1,  DM_PLY2,  XXXXXXX,  XXXXXXX,         RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         RGB_TOG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                  XXXXXXX,  XXXXXXX,  XXXXXXX,         XXXXXXX,  XXXXXXX,  XXXXXXX
),

[_NAV] = LAYOUT_split_3x6_3(
    XXXXXXX,  XXXXXXX,  KC_WH_L,  KC_MS_U,  KC_WH_R,  KC_WH_U,         XXXXXXX,  KC_HOME,  KC_UP,    KC_END,   KC_PGUP,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,         KC_ACL2,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_PGDN,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,         KC_ACL0,  KC_BTN1,  KC_BTN3,  KC_BTN2,  XXXXXXX,  _______,
                                  _______,  _______,  _______,         _______,  _______,  _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _SYM, _ADJUST);
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
        default:
            return true;  // Process all other keycodes normally
    }
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
//   if (!is_keyboard_master()) {
//     return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
//   }
//   return rotation;
}

void oled_render_layer_state(uint8_t layer) {
    static const char PROGMEM layer_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 
        0x30, 0x20, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x84, 0x84, 0xce, 0x4a, 0x1b, 0x11, 0x31, 0x20, 0x60, 0x40, 0xc0, 0x80, 0x80, 
        0x80, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x31, 0x11, 0x1b, 0x4a, 0xce, 0x84, 0x84, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x10, 0x10, 0x39, 0x29, 0x63, 0x42, 0xc6, 0x84, 0x8c, 0x08, 0x18, 0x10, 0x31, 
        0x31, 0x10, 0x18, 0x08, 0x8c, 0x84, 0xc6, 0x42, 0x63, 0x29, 0x39, 0x10, 0x10, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x02, 0x06, 
        0x06, 0x02, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    oled_write_raw(layer_logo, sizeof(layer_logo));
    oled_set_cursor(0, 5);
    oled_write_P(PSTR(" ADJ "), layer == _ADJUST);
    oled_write_P(PSTR(" NAV "), layer == _NAV);
    oled_write_P(PSTR(" SYM "), layer == _SYM);
    oled_write_P(PSTR(" NUM "), layer == _NUM);
}

void write_bar(char byte, uint16_t index) {
    int i;
    for (i = 0; i < 3; i ++) {
        oled_write_raw_byte(byte, index + i);
    }
}

void oled_render_adjustment_params(void) {
    static const char PROGMEM top[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x60, 
        0x60, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    static const char PROGMEM dial[] = {
        0x00, 0x00, 0xc0, 0xf0, 0x3c, 0x0e, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x07, 0x0e, 0x3c, 0xf0, 0xc0, 0x00, 0x00, 
        0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
        0x00, 0x00, 0x03, 0x0f, 0x3c, 0x70, 0xe0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0x70, 0x3c, 0x0f, 0x03, 0x00, 0x00};
    static const char PROGMEM mid[] = {
        0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc1, 0x01, 0x03, 0x03, 0xc6, 0x46, 0x46, 0x46, 
        0x46, 0x46, 0xc6, 0x06, 0x03, 0x03, 0xc1, 0x41, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x00, 0x00, 0x00};
    static const char PROGMEM bar[] = {
        0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00};
    static const char PROGMEM bottom[] = {
        0x00, 0x00, 0x03, 0x62, 0x92, 0x92, 0x92, 0x22, 0x03, 0x00, 0x00, 0x00, 0x03, 0xf2, 0x02, 0x02, 
        0x02, 0xf2, 0x03, 0x00, 0x00, 0x00, 0x03, 0x12, 0x32, 0x62, 0xc2, 0x82, 0x03, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x02, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 
        0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    oled_write("M:", false);
    if (rgblight_is_enabled()) {
        oled_write(get_u8_str(rgblight_get_mode(), ' '), false);
    }
    else {
        oled_write_P(PSTR("Off"), false);
    }    
    oled_write_raw(top, sizeof(top));
    oled_set_cursor(0, 2);
    oled_write_raw(dial, sizeof(dial));
    oled_set_cursor(0, 5);
    oled_write_raw(mid, sizeof(mid));

    int r, i;
    // loop over row
    uint8_t params[3] = {rgblight_get_sat(), rgblight_get_val(), rgblight_get_speed()};
    uint8_t offset[3] = {4, 14, 24};

    for (r = 0; r < 8; r ++) {
        oled_set_cursor(0, 13 - r);
        oled_write_raw(bar, sizeof(bar));
        for (i = 0; i < 3; i ++) {
            char x = 0x00;
            if (params[i] >= (r + 1) * 4 * 8) {
                x = 0xff;
            }
            else {
                params[i] %= 32;
                if (params[i] >= 31) {
                    x = 0xff;
                }
                else if (params[i] >= 23) {
                    x = 0xfc;
                }
                else if (params[i] >= 15) {
                    x = 0xf0;
                }
                else if (params[i] >= 7) {
                    x = 0xc0;
                }
                params[i] = 0;
            }
            write_bar(x, (13 - r)*32 + offset[i]);
        }
    }

    oled_set_cursor(0, 14);
    oled_write_raw(bottom, sizeof(bottom));
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

// void oled_render_logo(void) {
//     static const char PROGMEM crkbd_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//         0};
//     oled_write_P(crkbd_logo, false);
// }

bool oled_task_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    if (is_keyboard_master()) {
        if (layer != _BASE) {
            oled_render_layer_state(layer);
        }
        else {
            oled_clear();
        }
    } else {
        if (layer == _ADJUST) {
            oled_render_adjustment_params();
        }
        else {
            oled_clear();
        }
    }
    return false;
}

#endif // OLED_ENABLE


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer > 0) {
        // float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        HSV main_hsv = rgb_matrix_config.hsv;
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];
                if (index >= led_min && index <= led_max && index != NO_LED) {
                    uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
                    uint8_t h = 0;
                    uint8_t s = 0;
                    uint8_t v = 0;
                    if (kc == KC_LABK || kc == KC_RABK) {   // <, >
                        h = 157; s = 203; v = 255;
                    }
                    else if (kc == LBRK || kc == RBRK) {    // [, ]
                        h = 41; s = 255; v = 255;
                    }
                    else if (kc == KC_LPRN || kc == KC_RPRN) {    // (, )
                        h = 113; s = 236; v = 255;
                    }
                    else if (kc == KC_LCBR || kc == KC_RCBR) {    // {, }
                        h = 200; s = 191; v = 255;
                    }
                    else if (kc >= KC_P1 && kc <= KC_P0) {    // numpad numbers
                        h = 0; s = 0; v = 255;
                    }
                    else if (kc >= KC_NUM && kc <= KC_PEQL) {    // numpad symbols
                        h = 0; s = 0; v = 64;
                    }
                    else if (kc >= KC_F1 && kc <= KC_F12) {    // F1-F12
                        h = 0; s = 0; v = 64;
                    }
                    else if (kc == QK_BOOT) {
                        h = 0; s = 255; v = 255;
                    }
                    else if (kc == DM_REC1 || kc == DM_REC2) {  // macro record
                        h = 36; s = 214; v = 235;
                    }
                    else if (kc == DM_RSTP) {  // macro record stop
                        h = 0; s = 219; v = 204;
                    }
                    else if (kc == DM_PLY1 || kc == DM_PLY2) {  // macro play
                        h = 108; s = 228; v = 228;
                    }
                    else if (kc >= RGB_MOD && kc <= RGB_SPD) {  // rgb adjustments
                        if (kc % 2) {
                            h = 55; s = 219; v = 204;
                        }
                        else {
                            h = 205; s = 133; v = 255;
                        }
                    }
                    else if (kc >= KC_MS_U && kc <= KC_BTN8) {  // mouse movement & buttons
                        h = 138; s = 230; v = 237;
                    }
                    else if (kc >= KC_WH_U && kc <= KC_ACL2) {  // mouse controls
                        h = 220; s = 230; v = 237;
                    }
                    else if (kc >= KC_RGHT && kc <= KC_UP) {  // arrows
                        h = 74; s = 255; v = 255;
                    }
                    else if (kc >= KC_MUTE && kc <= KC_VOLD) {  // volume
                        h = 117; s = 255; v = 204;
                    }
                    else if (kc >= KC_MNXT && kc <= KC_EJCT) {  // media
                        h = 26; s = 255; v = 255;
                    }
                    else if (kc > KC_TRNS) {
                        h = 0; s = 0; v = 255;
                    }
                    s *= (float)main_hsv.s / UINT8_MAX;
                    v *= (float)main_hsv.v / UINT8_MAX;
                    HSV tmp = {h, s, v};
                    RGB rgb = hsv_to_rgb(tmp);
                    rgb_matrix_set_color( index, rgb.r, rgb.g, rgb.b );
                }
            }
        }
    }
}