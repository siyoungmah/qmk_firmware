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

// macOS shortcuts
#define CTRL_UP LCTL(KC_UP)
#define CMD_SPC LGUI(KC_SPC)

// num arrow/mod shortcuts
#define SFT_MIN RSFT_T(KC_PMNS)
#define GUI_UP RGUI_T(KC_UP)
#define ALT_DIV RALT_T(KC_PSLS)

// one shot keys
#define O_SHFT OSM(MOD_LSFT)
#define O_CTRL OSM(MOD_LCTL)
#define O_ALT OSM(MOD_LALT)
#define O_GUI OSM(MOD_LGUI)

// Tap-Hold Grave/ESC
#define ESC_GRV0 LT(0, KC_GRV)
#define ESC_GRV1 LT(1, KC_GRV)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // base, Colemak_DH
  [0] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ` ~ |           Q |           W |           F |           P |      B |                    |      J |           L |           U |           Y |         ' " |   BSPC |
      ESC_GRV0,         KC_Q,         KC_W,         KC_F,         KC_P,    KC_B,                         KC_J,         KC_L,         KC_U,         KC_Y,      KC_QUOT, KC_BSPC,       
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //| Mission |           A |           R |           S |           T |      G |                    |      M |           N |           E |           I |           O |    ; : |
  //| Command |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
       CTRL_UP, LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T),    KC_G,                         KC_M, RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O), KC_SCLN, 
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|  Spot-  |           Z |           X |           C |           D |      V |                    |      K |           H |         , < |         . > |         / ? |   KOR/ |
  //|   light |             |             |             |             |        |                    |        |             |             |             |             |    ENG |    
       CMD_SPC,         KC_Z,         KC_X,         KC_C,         KC_D,    KC_V,                         KC_K,         KC_H,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(1),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |             |       SPACE |           TAB |     |          ENTER |        BSPC |         DEL |        
  //                                      |         NUM |         NAV |       SYMBOLS |     |           FUNC |             |             |        
                                                  TG(3), LT(5,KC_SPC),   LT(4,KC_TAB),          LT(2,KC_ENT),       KC_BSPC,       KC_DEL
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),
  
  //base_2, QWERTY for Korean
  [1] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ` ~ |           Q |           W |           E |           R |      T |                    |      Y |           U |           I |           O |         ' " |   BSPC |
      ESC_GRV1,         KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,                         KC_Y,         KC_U,         KC_I,         KC_O,      KC_QUOT, KC_BSPC,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //| Mission |           A |           S |           D |           F |      G |                    |      H |           J |           K |           L |             |    ; : |
  //| Command |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
       CTRL_UP, LCTL_T(KC_A), LALT_T(KC_S),   LGUI(KC_D), LSFT_T(KC_F),    KC_G,                         KC_H,  RSFT_T(KC_J), RGUI_T(KC_K),RALT_T(KC_L),      KC_RCTL, KC_SCLN,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //|  Spot-  |           Z |           X |           C |           V |      B |                    |      N |           M |         , < |         . > |         / ? |   KOR/ |
  //|   light |             |             |             |             |        |                    |        |             |             |             |             |    ENG |
       CMD_SPC,         KC_Z,         KC_X,         KC_C,         KC_V,    KC_B,                         KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(0),
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|                                         KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
                                        //|             |       SPACE |           TAB |     |          ENTER |        BSPC |         DEL |        
  //                                      |         NUM |         NAV |       SYMBOLS |     |           FUNC |             |             |        
                                                   TG(3), LT(5,KC_SPC),   LT(4,KC_TAB),          LT(2,KC_ENT),      KC_BSPC,       KC_DEL
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),

  // FUNC
  [2] = LAYOUT_split_3x6_3(
  //,-------------------------------------------------------.                    ,------------------------------------------------------.
  //|          |    F12 |     F7 |     F8 |     F9 |        |                    |        |        |        |         |        |        |
          KC_NO,  KC_F12,   KC_F7,   KC_F8,   KC_F9,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO,
  //|----------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //| CMD/CTRL |    F11 |     F4 |     F5 |     F6 |        |                    |        |  SHIFT |    CMD | OPT/ALT |   CTRL |        |
        CG_SWAP,  KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_NO,                        KC_NO,  O_SHFT,   O_GUI,    O_ALT,  O_CTRL,   KC_NO, 
  //|----------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //| CMD/CTRL |    F10 |     F1 |     F2 |     F3 |        |                    |        |        |        |         |        |        |
        CG_NORM,  KC_F10,   KC_F1,   KC_F2,   KC_F3,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO, 
  //|----------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------+--------|
                                        //|        |    SPC |    TAB |  |        |   BSPC |    DEL |
                                              KC_NO,  KC_SPC,  KC_TAB,    KC_TRNS, KC_BSPC,  KC_DEL
                                        //`--------------------------'  `--------------------------'
  ),

  // NUM
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,------------------------------------------------------.
  //|        |        |      7 |      8 |      9 |      0 |                    |        |      + |        |       * |        |        |
  //|        |        |   Home |      ↑ |   PGUP |    INS |                    |        |        |        |         |        |        |
        KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_P0,                        KC_NO, KC_PPLS,   KC_NO,  KC_PAST,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|      { |      } |      4 |      5 |      6 |      : |                    |        |      - |      ↑ |       / |   CTRL |        |
  //|      [ |      ] |      ← |        |      → |      ; |                    |        |  SHIFT |    CMD | OPT/ALT |   CTRL |        |
      KC_LBRC, KC_RBRC,   KC_P4,   KC_P5,   KC_P6, KC_COLN,                        KC_NO, SFT_MIN,  GUI_UP,  ALT_DIV, KC_RCTL,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|      < |      > |      1 |      2 |      3 |      = |                    |        |      ← |      ↓ |       → |        |        |
  //|      , |      . |    END |      ↓ |   PGDN |        |                    |        |        |        |         |        |        |
      KC_COMM,  KC_DOT,   KC_P1,   KC_P2,   KC_P3,  KC_EQL,                        KC_NO, KC_LEFT, KC_DOWN,  KC_RGHT,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------+--------|
                                      //|        |    SPC |    TAB |  |    ENT |        |    DEL |
                                            TG(3),  KC_SPC,  KC_TAB,     KC_ENT,   KC_NO,  KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols
  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|      ! |      @ |      # |      $ |      % |      ^ |                    |      & |      * |      ( |      ) |    - _ |  BSPC  |
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC,                      KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |   CTRL | OPT/ALT|    CMD |  SHIFT |        |                    |        |        |    [ { |    ] } |    = + |   ; :  |
        KC_NO,  O_CTRL,   O_ALT,   O_GUI,  O_SHFT,   KC_NO,                        KC_NO,   KC_NO, KC_LBRC, KC_RBRC,  KC_EQL, KC_SCLN, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |        |        |        |        |        |                    |        |        |    , < |    . > |    / ? |   \ |  |
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |    SPC |        |  |    ENT |   BSPC |    DEL |
                                            KC_NO,  KC_SPC, KC_TRNS,     KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

  // Nav
  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|        |        |        |        |        |        |                    |        |        |        |        |        |  BSPC  |
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_BSPC, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |   CTRL | OPT/ALT|    CMD |  SHIFT |        |                    |        |   HOME |      ↑ |    END | Wheel↑ |   PGUP |
        KC_NO,  O_CTRL,   O_ALT,   O_GUI,  O_SHFT,   KC_NO,                        KC_NO, KC_HOME,   KC_UP,  KC_END, KC_WH_U, KC_PGUP, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |        |        |        |        |        |                    |        |      ← |      ↓ |      → | Wheel↓ |   PGDN |
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, KC_PGDN, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|    ESC |        |    TAB |  | Wheel← | Wheel→ |MouseBtn|
                                           KC_ESC, KC_TRNS,  KC_TAB,    KC_WH_L, KC_WH_R, KC_BTN1
                                      //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    case LT(0, KC_GRV): // add hold functionality to Grave key (ESC)
        if(!record->tap.count && record->event.pressed) {
            tap_code(KC_ESC); // Intercept the hold function to send ESC
            return false;
        }
        return true;
    case LT(1, KC_GRV): // add hold functionality to Grave key (ESC)
        if(!record->tap.count && record->event.pressed) {
            tap_code(KC_ESC); // Intercept the hold function to send ESC
            return false;
        }
        return true;
    case DF(1): // this runs when switching defaults from Colemak layer to QWERTY layer
        if (record->event.pressed) {
            tap_code(KC_CAPS); // change languages on mac
        }
        break;
    case DF(0): // this runs when switching defaults from QWERTY layer to Colemak layer
        if (record->event.pressed) {
            tap_code(KC_CAPS); // change languages on mac
        }
        break;
  }
  return true;
}
