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
#include "os_detection.h" // for language change between KOR and ENG
#include "features/custom_shift_keys.h"

//====CUSTOM KEYS AND SHORTHANDS=======

// one shot keys
#define O_SHFT OSM(MOD_LSFT)
#define O_CTRL OSM(MOD_LCTL)
#define O_ALT OSM(MOD_LALT)
#define O_GUI OSM(MOD_LGUI)

// // Tap-Hold Grave/ESC
// #define ESC_GRV0 LT(0, KC_GRV)
// #define ESC_GRV1 LT(1, KC_GRV)

// custom keycodes for Macros
enum custom_keycodes {
    SHFT_TOG = SAFE_RANGE,
};

// custom shift keys
// link: https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
const custom_shift_key_t custom_shift_keys[] = {
//   {KC_DOT , KC_QUES}, // Shift . is ?
//   {KC_COMM, KC_EXLM}, // Shift , is !
//   {KC_UNDS, KC_MINS}, // Shift _ is -
//   {KC_SLSH, KC_BSLS}, // Shift / is backslash
//   {KC_AMPR, KC_PIPE}, // Shift & is |
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

// =======Tap Dancing=======

// Tap Dance keycodes
enum td_keycodes {
    TD_LP, // single tap {, hold [
    TD_RP, // single tap }, hold ];
    TD_SHFT, // single tap shift, hold shift, double tap CAPS LOCK
    TD_LAYR, // toggle layers (NUM and NAV)
    // TD_M1, // tap for Mouse BTN1, hold for CMD
    // TD_M2, // tap for Mouse BTN2, hold for CTRL
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP // send two single taps
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void tdlp_finished(tap_dance_state_t *state, void *user_data);
void tdlp_reset(tap_dance_state_t *state, void *user_data);
void tdrp_finished(tap_dance_state_t *state, void *user_data);
void tdrp_reset(tap_dance_state_t *state, void *user_data);
void td_sticky_shift_finished(tap_dance_state_t *state, void *user_data);
void td_sticky_shift_reset(tap_dance_state_t *state, void *user_data);
void tdlayr_finished(tap_dance_state_t *state, void *user_data);
void tdlayr_reset(tap_dance_state_t *state, void *user_data);
void tdm1_finished(tap_dance_state_t *state, void *user_data);
void tdm1_finished(tap_dance_state_t *state, void *user_data);
void tdm2_reset(tap_dance_state_t *state, void *user_data);
void tdm2_reset(tap_dance_state_t *state, void *user_data);


//=======LAYOUT==========

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // base, Colemak_DH
//   [0] = LAYOUT_split_3x6_3(
//   //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
//   //|     ` ~ |           Q |           W |           F |           P |      B |                    |      J |           L |           U |           Y |         ' " |    DEL |
//       ESC_GRV0,         KC_Q,         KC_W,         KC_F,         KC_P,    KC_B,                         KC_J,         KC_L,         KC_U,         KC_Y,      KC_QUOT,  KC_DEL,       
//   //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
//   //|     _ - |           A |           R |           S |           T |      G |                    |      M |           N |           E |           I |           O |    ; : |
//   //|         |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
//        KC_UNDS, LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T),    KC_G,                         KC_M, RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O), KC_SCLN, 
//   //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
//   //| Mission |           Z |           X |           C |           D |      V |                    |      K |           H |         , ! |         . ? |         / \ |   KOR/ |
//   //| Control |        UNDO |         CUT |        COPY |             |  PASTE |                    |        |             |             |             |             |    ENG |    
//        KC_MCTL,   LT(0,KC_Z),   LT(0,KC_X),   LT(0,KC_C),         KC_D, LT(0,KC_V),                      KC_K,         KC_H,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(1),
//   //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
//   //                                      |         TAB |       SPACE |         SHIFT |     |          ENTER |   BACKSPACE |      TOGGLE |        
//   //                                      |         NAV |     SYMBOLS |        Toggle |     |            NUM |             |     NUM/NAV |        
//                                             LT(4,KC_TAB),  LT(3,KC_SPC),   TD(TD_SHFT),          LT(2,KC_ENT),     KC_BSPC,   TD(TD_LAYR)
//                                         //`-------------------------------------------'     `--------------------------------------------'
//   ),
  // base, Canary
  [0] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ESC |           W |           L |           Y |           P |      B |                    |      Z |           F |           O |           U |         DEL |        |
        KC_ESC,         KC_W,         KC_L,         KC_Y,         KC_P,    KC_B,                  LT(0, KC_Z),         KC_F,         KC_O,         KC_U,      KC_DEL,    KC_NO,       
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|         |           C |           R |           S |           T |      G |                    |      M |           N |           E |           I |           A |        |
  //|         |             |        CTRL |     OPT?ALT |         CMD |        |                    |        |         CMD |     OPT/ALT |        CTRL |             |        | 
         KC_NO,   LT(0,KC_C), LCTL_T(KC_R), LALT_T(KC_S), LGUI_T(KC_T),    KC_G,                         KC_M, RGUI_T(KC_N), RALT_T(KC_E), RCTL_T(KC_I),         KC_A,   KC_NO, 
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //| Mission |           Q |           J |           V |           D |      K |                    |      X |           H |         , ! |         . ? |         / \ |   KOR/ |
  //| Control |             |             |       PASTE |             |        |                    |    CUT |             |             |             |             |    ENG |    
       KC_MCTL,         KC_Q,         KC_J,   LT(0,KC_V),         KC_D,    KC_K,                   LT(0,KC_X),         KC_H,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(1),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |         TAB |       SPACE |         SHIFT |     |          ENTER |   BACKSPACE |      TOGGLE |        
  //                                      |         NAV |     SYMBOLS |        Toggle |     |            NUM |             |     NUM/NAV |        
                                            LT(4,KC_TAB),  LT(3,KC_SPC),   TD(TD_SHFT),          LT(2,KC_ENT),     KC_BSPC,   TD(TD_LAYR)
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),

  //base_2, QWERTY for Korean
  [1] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ESC |           Q |           W |           E |           R |      T |                    |      Y |           U |           I |           O |           P |    DEL |
        KC_ESC,         KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,                         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,  KC_DEL,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //|         |           A |           S |           D |           F |      G |                    |      H |           J |           K |           L |        ' "  |        |
  //|         |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
         KC_NO, LCTL_T(KC_A), LALT_T(KC_S),   LGUI(KC_D), LSFT_T(KC_F),    KC_G,                         KC_H,  RSFT_T(KC_J), RGUI_T(KC_K),RALT_T(KC_L),RCTL_T(KC_QUOT), KC_NO,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //| Mission |           Z |           X |           C |           V |      B |                    |      N |           M |         , ! |         . ? |         / \ |   KOR/ |
  //| Control |        UNDO |         CUT |        COPY |             |        |                    |        |             |             |             |             |    ENG |    
       KC_MCTL,   LT(1,KC_Z),   LT(1,KC_X),   LT(1,KC_C),   LT(1,KC_V),    KC_B,                         KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(0),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |         TAB |       SPACE |         SHIFT |     |          ENTER |   BACKSPACE |      TOGGLE |        
  //                                      |         NAV |     SYMBOLS |        Toggle |     |            NUM |             |     NUM/NAV |        
                                            LT(4,KC_TAB),  LT(3,KC_SPC),    TD(TD_SHFT),          LT(2,KC_ENT),     KC_BSPC,   TD(TD_LAYR)
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),

  // NUM/FN with right hand NAV
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,------------------------------------------------------.
  //|        |        |      7 |      8 |      9 |      0 |                    |        |   HOME |      ↑ |     END |   PGUP |    DEL |
  //|        |    F12 |     F7 |     F8 |     F9 |    INS |                    |        |        |        |         |        |        |
        KC_NO,  KC_F12,    KC_7,   KC_P8,   KC_P9,   KC_P0,                        KC_NO, KC_HOME,   KC_UP,   KC_END, KC_PGUP,  KC_DEL, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|CMD/CTRL|        |      4 |      5 |      6 |      - |                    |        |      ← |      ↓ |       → |   PGDN |        |
  //|   SWAP |    F11 |     F4 |     F5 |     F6 |        |                    |        |        |        |         |        |        |
      CG_SWAP,  KC_F11,   KC_P4,   KC_P5,   KC_P6, KC_MINS,                        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|CMD/CTRL|        |      1 |      2 |      3 |      . |                    |        |        |        |         |        |        |
  //| revert |    F10 |     F1 |     F2 |     F3 |        |                    |        |        |        |         |        |        |
      CG_NORM,  KC_F10,   KC_P1,   KC_P2,   KC_P3,  KC_DOT,                        KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------+--------|
                                      //|    TAB |    SPC |  SHIFT |  |        |   BSPC |   BASE |
                                      //|        |SYMBOLS |        |  |        |        |        |
                                    KC_TAB,LT(3,KC_SPC), TD(TD_SHFT),   KC_TRNS, KC_BSPC,   TG(2)
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|        |      ` |      # |      @ |      " |      * |                    |      ^ |      + |      ! |      ? |       |         |
        KC_NO,  KC_GRV, KC_HASH,   KC_AT,  KC_DQT, KC_ASTR,                      KC_CIRC, KC_PLUS, KC_EXLM, KC_QUES,  KC_NO,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |      < |      > |      & |      ' |        |                    |      % |    = + |      | |      ( |      ) |        |
        KC_NO,   KC_LT,   KC_GT, KC_AMPR, KC_QUOT,   KC_NO,                      KC_PERC, KC_EQL, KC_PIPE, KC_LPRN, KC_RPRN,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |        |        |      ~ |      _ |        |                    |      $ |      - |      ; |      : |      \ |        |
        KC_NO,   KC_NO,   KC_NO, KC_TILD, KC_UNDS,   KC_NO,                      KC_DLR,   KC_MIN, KC_SLSH, KC_COLN, KC_BSLS,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |        |  SHIFT |  |  ( [ { |  } ] ) |        |
                                            KC_NO, KC_TRNS,TD(TD_SHFT),TD(TD_LP),TD(TD_RP), KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  // Nav w/ mouse controls
  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|    ESC |        |        |        |        |        |                   |        |   HOME |      ↑ |    END |   PGUP |        |
       KC_ESC,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO, KC_HOME,   KC_UP,  KC_END, KC_PGUP,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |  shift |    CTRL| OPT/ALT|    CMD |        |                    |        |      ← |      ↓ |      → |   PGDN |        |
        KC_NO, KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI,   KC_NO,                        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|MISSION |        |        |        |        |        |                    |        |        |        |        |        |        |
  //| Control|        |        |        |        |        |                    |        |        |        |        |        |        |
      KC_MCTL,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        | ALT/OPT|SHFT TOG|  |SHFT TOG|    CMD |   BASE |
                                          KC_TRNS, KC_LALT,TD(TD_SHFT),TD(TD_SHFT), O_GUI,   TG(4)         
                                      //`--------------------------'  `--------------------------'
  )

// Nav w/ mouse controls
//   [4] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//   //|    ESC |        | M WH ↑ |    M ↑ | M WH ↓ |        |                    |        |   HOME |      ↑ |    END |   PGUP |        |
//        KC_ESC,   KC_NO, KC_WH_U, KC_MS_U, KC_WH_D,   KC_NO,                        KC_NO, KC_HOME,   KC_UP,  KC_END, KC_PGUP,   KC_NO, 
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//   //|        | M WH ← |    M ← |    M ↓ |    M → | M WH → |                    |        |      ← |      ↓ |      → |   PGDN |        |
//        KC_NO , KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,                        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,   KC_NO, 
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//   //|MISSION |        |        |        |        |        |                    |        |        |        |        |        |        |
//   //| Control|        |        |        |        |        |                    |        |        |        |        |        |        |
//       KC_MCTL,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                       //|        | ALT/OPT|SHFT TOG|  |   CTRL |    CMD |   BASE |
//                                           KC_TRNS, KC_LALT,TD(TD_SHFT),TD(TD_M2),TD(TD_M1),   TG(4)         
//                                       //`--------------------------'  `--------------------------'
//   )
};

//=======TAPDANCE FUNCTIONALITY=========
// Determine the tapdance state to return

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you wanat to send a 'HOLD'
        else return TD_SINGLE_HOLD;
    }
    if (state->count == 2){
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } 
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:
void tdlp_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_LCBR); break; // left parens, {}
        case TD_SINGLE_HOLD: register_code16(KC_LBRC); break; // left curly braces, []
        // case TD_DOUBLE_TAP: register_code(KC_LBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LCBR); register_code16(KC_LCBR); break; // fast typing, {{
        default: break;
    }
}

void tdlp_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_LCBR); break; // left parens, {}
        case TD_SINGLE_HOLD: register_code16(KC_LBRC); break; // left curly braces, []
        // case TD_DOUBLE_TAP: register_code(KC_LBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LCBR); register_code16(KC_LCBR); break; // fast typing, {{
        default: break;
    }
    td_state = TD_NONE;
}

void tdrp_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_RCBR); break; // left parens, {}
        case TD_SINGLE_HOLD: register_code16(KC_RBRC); break; // left curly braces, []
        // case TD_DOUBLE_TAP: register_code(KC_RBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RCBR); register_code16(KC_RCBR); break; // fast typing, }}
        default: break;
    }
}

void tdrp_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_RCBR); break; // left parens, {}
        case TD_SINGLE_HOLD: register_code16(KC_RBRC); break; // left curly braces, []
        // case TD_DOUBLE_TAP: register_code(KC_RBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RCBR); register_code16(KC_RCBR); break; // fast typing, }}
        default: break;
    }
    td_state = TD_NONE;
}

void td_sticky_shift_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    static bool held = false; // static variable to remember state.
    switch (td_state) {
        case TD_SINGLE_TAP: 
            if(held) {
                unregister_code(KC_LSFT); // if we are ending a shift toggle
                held = !held; 
            } else {
                set_oneshot_mods(MOD_BIT(KC_LSFT)); // tap for oneshot shift
            }
            break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break; // hold for normal shift
        case TD_DOUBLE_TAP: // double tap for toggle shift
            held = !held; // toggle between held and release
            if(held) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            break;
        default: break;
    }
}

void td_sticky_shift_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: break; // one shot shift still active
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break; // shift
        case TD_DOUBLE_TAP: break; // Caps Lock
        default: break;
    }
    td_state = TD_NONE;
}

void tdlayr_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: 
            // Check to see if the NUM layer is already set
            if(layer_state_is(2)){
                layer_off(2);
            } else {
                layer_on(2);
            }
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the NAV layer is already set
            if(layer_state_is(4)){
                layer_off(4);
            } else {
                layer_on(4);
            }
        default: break;
    }
}

void tdlayr_reset(tap_dance_state_t *state, void *user_data) {
    td_state = TD_NONE;
}

void tdm1_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_MS_BTN1); break; // mouse button, left click
        case TD_SINGLE_HOLD: register_code(KC_LGUI); break; // CMD when held
        default: break;
    }
}

void tdm1_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_MS_BTN1); break; // mouse button, left click
        case TD_SINGLE_HOLD: unregister_code(KC_LGUI); break; // release CMD
        default: break;
    }
    td_state = TD_NONE;
}

void tdm2_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code(KC_MS_BTN2); break; // mouse button, right click
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break; // CTRL when held
        default: break;
    }
}

void tdm2_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code(KC_MS_BTN2); break; // mouse button, right click
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break; // release CTRL
        default: break;
    }
    td_state = TD_NONE;
}
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlp_finished, tdlp_reset),
    [TD_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdrp_finished, tdrp_reset),
    [TD_SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sticky_shift_finished, td_sticky_shift_reset),
    [TD_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlayr_finished, tdlayr_reset),
    // [TD_M1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdm1_finished, tdm1_reset),
    // [TD_M2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdm2_finished, tdm2_reset),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record){
    switch(keycode) {
        case TD(TD_SHFT): return 275;
        case TD(TD_LAYR): return 275;
        default: return TAPPING_TERM;
    }
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t host_os = detected_host_os();

  if (!process_custom_shift_keys(keycode, record)) { return false; }
  

  switch (keycode) {
    // ESC + Grave
    case LT(0, KC_GRV): // add hold functionality to Grave key (ESC)
    case LT(1, KC_GRV):
        if(!record->tap.count && record->event.pressed) {
            tap_code(KC_ESC); // Intercept the hold function to send ESC
            return false;
        }
        return true;

    // TD_SHFT takes care of this. But leaving it in for reference for a tap-hold custom key
    // Toggle Shift On/Off
    // case SHFT_TOG:
    //     if(record->event.pressed) { // when SHFT_TOG is pressed
    //         static bool held = false; // Static variable to remember state.
    //         held = !held; // toggle between holding and releasing
    //         if(held) {
    //             register_code(KC_LSFT);
    //         } else {
    //             unregister_code(KC_LSFT);
    //         }
    //         return false;
    //     }
    //     break;
    
    // KOR <-> ENG, and QWERTY <-> Colemak
    case DF(1): // this runs when switching defaults from Colemak layer to QWERTY layer
    case DF(0): // this runs when switching defaults from QWERTY layer to Colemak layer
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code(KC_LNG1); // change languages on windows
            }
            else {
                tap_code(KC_CAPS); // change lanugages on mac
            }
        }
        break;
    
    // Common shortcuts on HOLD (Cut, Copy, Paste, Undo)
    case LT(0,KC_X):
    case LT(1,KC_X):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_X)); // Intercept hold function to send Ctrl-X
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_C):
    case LT(1,KC_C):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_C)); // Intercept hold function to send Ctrl-C
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_V):
    case LT(1,KC_V):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_V)); // Intercept hold function to send Ctrl-V
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_Z):
    case LT(1,KC_Z):
        if (!record->tap.count && record->event.pressed) {
            tap_code16(G(KC_Z)); // Intercept hold function to send Ctrl-Z
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
  }
  return true;
}

