/*
Copyright 2022 Azu

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

#include "keymap_german.h"

//Layer renaming
#define _DL  0                     //default
#define _FUN1 1                     //function layer #1
#define _FUN2 2                     //function layer #2
#define _RESET 3                     //Reset layer

//Keymapping renaming
#define ______  KC_NO            //renaming KC_TRNS for readability in keymaps
#define RGB_MI  RGB_MODE_FORWARD   //increase RGB mode
#define RGB_MD  RGB_MODE_REVERSE   //decrease RGB mode

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DL] = LAYOUT(
      KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,      KC_5,    KC_6,    KC_7,   KC_8,    KC_9, KC_0,   DE_SS,   DE_ACUT, ______, KC_BSPC,   \
      KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,      KC_T,    KC_Y,    KC_U,   KC_I,    KC_O, KC_P,   DE_UDIA, DE_PLUS,          ______,   \
      KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,      KC_G,    KC_H,    KC_J,   KC_K,    KC_L, DE_ODIA,DE_ADIA, DE_HASH,          KC_ENT,   \
      KC_LSFT, DE_LABK, KC_Z,    KC_X,   KC_C,      KC_V,    KC_B,    KC_N,   KC_M, KC_COMM, KC_DOT, DE_MINS, KC_RSFT, DF(_FUN1),   \
      KC_LCTL, KC_LGUI, KC_LALT,                             KC_SPC                        , ______, KC_ALGR, MO(_RESET),         KC_RCTL   ),

    [_FUN1] = LAYOUT(
      KC_ESC, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,  KC_F12, ______,  KC_BSPC,   \
      ______, ______, KC_UP,  ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,         ______,   \
      ______, KC_LEFT, KC_DOWN, KC_RIGHT, ______, ______,  ______,  ______, ______, ______, ______, ______, ______,         KC_ENT,   \
      ______, ______,  ______, ______, ______,  ______,  ______,  ______, ______, ______, ______, ______,           DF(_FUN2), DF(_DL),   \
      ______, ______, ______,                              ______                         , ______, ______, ______,        ______),

    [_FUN2] = LAYOUT(
      KC_ESC, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11,  KC_F12, ______,  KC_BSPC,   \
      ______, RGB_TOG, RGB_MI,  RGB_MD,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,         ______,   \
      ______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, ______,  ______,  ______, ______, ______, ______, ______, ______,         KC_ENT,   \
      ______, ______,  RGB_VAI, RGB_VAD, ______,  ______,  ______,  ______, ______, ______, ______, ______,           ______, DF(_DL),   \
      ______, ______, ______,                              ______                         , ______, ______, ______,        ______),

    [_RESET] = LAYOUT(
      ______, ______,   ______,   ______,    ______,   ______,   ______,  ______,  ______,  ______, ______, ______,  ______, ______,  RESET,   \
      ______, ______, ______,  ______,  ______,  ______,  ______,  ______, ______, ______, ______, ______, ______,         ______,   \
      ______, ______, ______, ______, ______, ______,  ______,  ______, ______, ______, ______, ______, ______,         ______,   \
      ______, ______,  ______, ______, ______,  ______,  ______,  ______, ______, ______, ______, ______,           ______, ______,   \
      ______, ______, ______,                              ______                         , ______, ______, ______,        ______),
};


const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 32, HSV_RED}
);

const rgblight_segment_t PROGMEM function1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_RED},
    {8, 8, HSV_GREEN},
    {16, 8, HSV_BLUE},
    {24, 8, HSV_CYAN}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    capslock_layer,
    function1_layer
);


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, _FUN1)) {
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 255);
    } else {
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 150);
    }
    return state;
}
