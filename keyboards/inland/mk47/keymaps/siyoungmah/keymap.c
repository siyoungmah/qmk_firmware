// TO COMPILE
// qmk compile -kb inland/mk47 -km siyoungmah

/* Copyright (C) 2023 jonylee@hfd
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

#include "os_detection.h"
#include "features/custom_shift_keys.h"
#include "features/achordion.h"

//====CUSTOM KEYS AND SHORTHANDS=======

// one shot keys
#define O_SHFT OSM(MOD_LSFT)
#define O_CTRL OSM(MOD_LCTL)
#define O_ALT OSM(MOD_LALT)
#define O_GUI OSM(MOD_LGUI)

// custom keycodes for Macros
enum custom_keycodes {
    INC_SIZE = SAFE_RANGE,
    DEC_SIZE,
    ZOOM_IN,
    ZOOM_OUT,
    SCRN_CAP4,
    SCRN_CAP5
};

// custom shift keys
// link: https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
const custom_shift_key_t custom_shift_keys[] = {
  {KC_DOT , KC_EXLM}, // Shift . is !
  {KC_COMM, KC_QUES}, // Shift , is ?
  {KC_SLSH, KC_BSLS}, // Shift / is backslash
  {KC_P1, KC_F1}, // Shift F1 is 1 
  {KC_P2, KC_F2}, // Shift F2 is 2 
  {KC_P3, KC_F3}, // Shift F3 is 3 
  {KC_P4, KC_F4}, // Shift F4 is 4 
  {KC_P5, KC_F5}, // Shift F5 is 5 
  {KC_P6, KC_F6}, // Shift F6 is 6 
  {KC_P7, KC_F7}, // Shift F7 is 7 
  {KC_P8, KC_F8}, // Shift F8 is 8 
  {KC_P9, KC_F9}, // Shift F9 is 9
};

uint8_t NUM_CUSTOM_SHIFT_KEYS =
    sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

//=======LAYOUT==========
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// BASE, Canary
    [0] = LAYOUT_planck_mit(
    //  .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    //  |      W |      L |      Y |      P |      B |        |        |      Z |      F |      O |      U |    DEL |
             KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,   KC_NO,   KC_NO,    KC_Z,    KC_F,    KC_O,    KC_U,  KC_DEL,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      C |      R |      S |      T |      G |        |        |      M |      N |      E |      I |      A |
    //  |        |   CTRL |    OPT |    CMD |        |        |        |        |        |        |        |        |
        KC_C,LCTL_T(KC_R),LALT_T(KC_S),LGUI_T(KC_T),KC_G,KC_NO,KC_NO,KC_M,RGUI_T(KC_N),RALT_T(KC_E),RCTL_T(KC_I),KC_A,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      Q |      J |      V |      D |      K |        |        |      X |      H |    / \ |    , ? |    . ! |
             KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,   KC_NO,   KC_NO,    KC_X,    KC_H, KC_SLSH, KC_COMM,  KC_DOT,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |    Tab |  Space |      Enter      |  Shift |   BSPC |        |        | Canary |
    //  |        |        |        |        | SYMBOL |       NAV       |        |    NUM |        |        | /Qwerty|
            KC_NO,   KC_NO,   KC_NO,  KC_TAB,LT(3,KC_SPC),LT(4,KC_ENT), O_SHFT,LT(2,KC_BSPC), KC_NO,  KC_NO,   DF(1)
    //  '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
    ),

// BASE, Qwerty
    [1] = LAYOUT_planck_mit(
    //  .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    //  |      Q |      W |      E |      R |      T |        |        |      Y |      U |      I |      O |      P |
             KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_NO,   KC_NO,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      A |      S |      D |      F |      G |        |        |      H |      J |      K |      L |   ' "  |
    //  |        |   CTRL |    OPT |    CMD |        |        |        |        |        |        |        |        |
        KC_A,LCTL_T(KC_S),LALT_T(KC_D),LGUI_T(KC_F),KC_G,KC_NO,KC_NO,KC_H,RGUI_T(KC_J),RALT_T(KC_K),RCTL_T(KC_L),KC_QUOT,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      Z |      X |      C |      V |      B |        |        |      N |      M |    / \ |    , ! |    . ? |
             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_NO,   KC_NO,    KC_N,    KC_M, KC_SLSH, KC_COMM,  KC_DOT,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |    Tab |  Space |      Enter      |  Shift |   BSPC |        |        | Canary |
    //  |        |        |        |        | SYMBOL |       NAV       |        |    NUM |        |        | /Qwerty|
            KC_NO,   KC_NO,   KC_NO,  KC_TAB,LT(3,KC_SPC),LT(4,KC_ENT), O_SHFT,LT(2,KC_BSPC), KC_NO,  KC_NO,   DF(0)
    //  '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
    ),

// NUMBERS
    [2] = LAYOUT_planck_mit(
    //  .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    //  |        |      7 |      8 |      9 |      * |        |        |      ^ |        |      0 |        |CMD/CTRL|
    //  |    F12 |     F7 |     F8 |     F9 |        |        |        |        |        |        |        |   SWAP |
           KC_F12,   KC_P7,   KC_P8,   KC_P9, KC_ASTR,   KC_NO,   KC_NO, KC_CIRC,   KC_NO,   KC_P0,   KC_NO, CG_SWAP,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |      4 |      5 |      6 |      - |        |        |      % |Command | Option | Control|CMD/CTRL|
    //  |    F11 |     F4 |     F5 |     F6 |        |        |        |        |        |        |        | revert |
           KC_F11,   KC_P4,   KC_P5,   KC_P6, KC_MINS,   KC_NO,   KC_NO, KC_PERC,   O_GUI,   O_ALT,  O_CTRL, CG_NORM,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |      1 |      2 |      3 |      + |        |        |      $ |        |        |        |        |
    //  |    F10 |     F1 |     F2 |     F3 |        |        |        |        |        |        |        |        |
           KC_F10,   KC_P1,   KC_P2,   KC_P3, KC_PLUS,   KC_NO,   KC_NO,  KC_DLR,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |    Tab |  Space |      Enter      |  Shift |        |        |        |        |
    //  |        |        |        |        |        |                 |        |        |        |        |        |
            KC_NO,   KC_NO,   KC_NO,  KC_TAB,  KC_SPC,     KC_ENT,        O_SHFT, KC_TRNS,   KC_NO,   KC_NO,   KC_NO
    //  '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
    ),

// SYMBOLS
    [3] = LAYOUT_planck_mit(
    //  .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    //  |      ~ |      & |      | |      = |      * |        |        |      ^ |      " |      ) |      } |      ] |
          KC_TILD, KC_AMPR, KC_PIPE,  KC_EQL, KC_ASTR,   KC_NO,   KC_NO, KC_CIRC,  KC_DQT, KC_RPRN, KC_RCBR, KC_RBRC,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      ` |    CTRL| OPT/ALT|    CMD |      - |        |        |      % |      ' |      ( |      { |      [ |
           KC_GRV,  O_CTRL,   O_ALT,   O_GUI, KC_MINS,   KC_NO,   KC_NO,  KC_PERC, KC_QUOT, KC_LPRN, KC_LCBR, KC_LBRC,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |      < |      > |      # |      _ |      + |        |        |      $ |      @ |      \ |      ; |      : |
            KC_LT,   KC_GT, KC_HASH, KC_UNDS, KC_PLUS,   KC_NO,   KC_NO,  KC_DLR,   KC_AT, KC_BSLS, KC_SCLN, KC_COLN,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |        |        |                 |  Shift |        |        |        |        |
            KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_TRNS,      KC_NO,        O_SHFT,   KC_NO,   KC_NO,  KC_NO,    KC_NO
    //  '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
    ),

// NAVIGATION
    [4] = LAYOUT_planck_mit(
    //  .--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.--------.
    //  |    ESC |MISSION | Capture| Capture|  Print |        |        |   PGUP |   HOME |      ↑ |    END |    DEL |
    //  |        | Control| Portion| Section| Screen |        |        |        |        |        |        |        |
           KC_ESC, KC_MCTL,SCRN_CAP4,SCRN_CAP5,KC_PSCR,  KC_NO,   KC_NO, KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |  shift |    CTRL| OPT/ALT|    CMD |        |        |        |   PGDN |      ← |      ↓ |      → |        |
           O_SHFT,  O_CTRL,   O_ALT,   O_GUI,   KC_NO,   KC_NO,   KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |        |        |        |        |        |   Zoom |   Zoom |Decrease|Increase|
    //  |        |        |        |        |        |        |        |        |    Out |     In |   Size |   Size |
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,ZOOM_OUT, ZOOM_IN,DEC_SIZE,INC_SIZE,
    //  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  |        |        |        |        |        |                 |  Shift |        |        |        |        |
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_TRNS,       O_SHFT,   KC_NO,   KC_NO,  KC_NO,    KC_NO
    //  '--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'--------'
    )

};

// Custom tapping terms
// Default tapping term is 200ms
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record){
    switch(keycode) {
        case O_SHFT: return 275;
        case KC_SPC: return 100;
        default: return TAPPING_TERM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t host_os = detected_host_os();
  if (!process_achordion(keycode, record)) { return false; }
  if (!process_custom_shift_keys(keycode, record)) { return false; }
  // to debug: 
//   if (record->event.pressed) {
//     // On every key press, print the event's keycode and matrix position.
//     dprintf("kc=0x%04X, row=%2u, col=%2u\n",
//         keycode, record->event.key.row, record->event.key.col);
//   }

  switch (keycode) {
    case SCRN_CAP4:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(G(S(KC_S))); 
            } else {
                tap_code16(G(S(KC_4)));
            }
        }
        break;
    case SCRN_CAP5:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(G(S(KC_S))); 
            } else {
                tap_code16(G(S(KC_5)));
            }
        }
        break;
    case DEC_SIZE:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(S(KC_LT))); 
            } else {
                tap_code16(G(S(KC_LT)));
            }
        }
        break;
    case INC_SIZE:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(S(KC_GT))); 
            } else {
                tap_code16(G(S(KC_GT)));
            }
        }
        break;
    case ZOOM_OUT:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_MINS)); 
            } else {
                tap_code16(G(KC_MINS));
            }
        }
        break;
    case ZOOM_IN:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_PLUS)); 
            } else {
                tap_code16(G(KC_PLUS));
            }
        }
        break;
  }
  return true;
}