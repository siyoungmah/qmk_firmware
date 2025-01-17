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
#include "features/achordion.h"
// #include "print.h" // for debugging

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
    U_COPY = SAFE_RANGE,
    U_CUT,
    U_PASTE,
    U_UNDO,
    INC_SIZE,
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
//   {KC_UNDS, KC_MINS}, // Shift _ is -
  {KC_SLSH, KC_BSLS}, // Shift / is backslash
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
    // TD_LP, // single tap a{, hold [
    // TD_RP, // single atap }, hold ];
    // TD_SHFT, // saingle tap shift, hold shift, double tap CAPS LOCK
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
// static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
// td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
// void tdlp_finished(tap_dance_state_t *state, void *user_data);
// void tdlp_reset(tap_dance_state_t *state, void *user_data);
// void tdrp_finished(tap_dance_state_t *state, void *user_data);
// void tdrp_reset(tap_dance_state_t *state, void *user_data);
// void td_sticky_shift_finished(tap_dance_state_t *state, void *user_data);
// void td_sticky_shift_reset(tap_dance_state_t *state, void *user_data);
// void tdlayr_finished(tap_dance_state_t *state, void *user_data);
// void tdlayr_reset(tap_dance_state_t *state, void *user_data);
// void tdm1_finished(tap_dance_state_t *state, void *user_data);
// void tdm1_finished(tap_dance_state_t *state, void *user_data);
// void tdm2_reset(tap_dance_state_t *state, void *user_data);
// void tdm2_reset(tap_dance_state_t *state, void *user_data);


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
  //|         |           W |           L |           Y |           P |      B |                    |      Z |           F |           O |           U |         DEL |        |
         KC_NO,         KC_W,         KC_L,         KC_Y,         KC_P,    KC_B,                  LT(0, KC_Z),         KC_F,         KC_O,         KC_U,       KC_DEL,   KC_NO,     
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|         |           C |           R |           S |           T |      G |                    |      M |           N |           E |           I |           A |        |
  //|         |             |        CTRL |     OPT?ALT |         CMD |        |                    |        |         CMD |     OPT/ALT |        CTRL |             |        | 
         KC_NO,   LT(0,KC_C), LCTL_T(KC_R), LALT_T(KC_S), LGUI_T(KC_T),    KC_G,                         KC_M, RGUI_T(KC_N), RALT_T(KC_E), RCTL_T(KC_I),         KC_A,   KC_NO, 
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|  Enable |           Q |           J |           V |           D |      K |                    |      X |           H |         / \ |         , ? |         . ! |   KOR/ |
  //| Debugger|             |             |       PASTE |             |        |                    |    CUT |             |             |             |             |    ENG |    
         KC_NO,         KC_Q,         KC_J,   LT(0,KC_V),         KC_D,    KC_K,                   LT(0,KC_X),         KC_H,      KC_SLSH,      KC_COMM,       KC_DOT,   DF(1),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |         TAB |       SPACE |         ENTER |     |          ENTER |       SHIFT |        BSPC |       
  //                                      |             |     SYMBOLS |           NAV |     |            NUM |   CAPS WORD |        NUMS |        
                                                  KC_TAB, LT(3,KC_SPC),   LT(4,KC_ENT),                 KC_NO,       O_SHFT, LT(2,KC_BSPC)
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),

  //base_2, QWERTY for Korean
  [1] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|         |           Q |           W |           E |           R |      T |                    |      Y |           U |           I |           O |           P |        |
         KC_NO,         KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,                         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,   KC_NO,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //|         |           A |           S |           D |           F |      G |                    |      H |           J |           K |           L |        ' "  |        |
  //|         |             |        CTRL |     OPT?ALT |         CMD |        |                    |        |         CMD |     OPT/ALT |        CTRL |             |        | 
         KC_NO,         KC_A, LCTL_T(KC_S), LALT_T(KC_D), LGUI_T(KC_F),    KC_G,                         KC_H,  RGUI_T(KC_J), RALT_T(KC_K),RCTL_T(KC_L),      KC_QUOT,   KC_NO,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|         |           Z |           X |           C |           V |      B |                    |      N |           M |         / \ |         , ! |         . ? |   KOR/ |
  //|         |        UNDO |         CUT |        COPY |             |        |                    |        |             |             |             |             |    ENG |    
         KC_NO,   LT(1,KC_Z),   LT(1,KC_X),   LT(1,KC_C),   LT(1,KC_V),    KC_B,                         KC_N,         KC_M,      KC_SLSH,      KC_COMM,       KC_DOT,   DF(0),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |         TAB |       SPACE |         ENTER |     |          ENTER |       SHIFT |        BSPC |        
  //                                      |             |     SYMBOLS |           NAV |     |            NUM |   CAPS WORD |        NUMS |        
                                                  KC_TAB, LT(3,KC_SPC),   LT(4,KC_ENT),                 KC_NO,       O_SHFT, LT(2,KC_BSPC)
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),

  // NUM
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,------------------------------------------------------.
  //|        |        |      7 |      8 |      9 |      * |                    |      ^ |        |      0 |         |        |CMD/CTRL|
  //|        |    F12 |     F7 |     F8 |     F9 |        |                    |        |        |        |         |        |   SWAP |
        KC_NO,  KC_F12,   KC_P7,   KC_P8,   KC_P9, KC_ASTR,                      KC_CIRC,   KC_NO,   KC_P0,    KC_NO,   KC_NO, CG_SWAP,  
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|        |        |      4 |      5 |      6 |      - |                    |      % |Command | Option | Control |  Shift |CMD/CTRL|
  //|        |    F11 |     F4 |     F5 |     F6 |        |                    |        |        |        |         |        | revert |
        KC_NO,  KC_F11,   KC_P4,   KC_P5,   KC_P6, KC_MINS,                      KC_PERC,   O_GUI,   O_ALT,   O_CTRL, O_SHFT,  CG_NORM, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|        |        |      1 |      2 |      3 |      + |                    |      $ |        |        |         |        |        |
  //|        |    F10 |     F1 |     F2 |     F3 |        |                    |        |        |        |         |        |        |
        KC_NO,  KC_F10,   KC_P1,   KC_P2,   KC_P3, KC_PLUS,                       KC_DLR,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------+--------|
                                      //|    TAB |  SPACE |  ENTER |  |        |        |        |
                                      //|        |        |        |  |        |        |        |
                                           KC_TAB,  KC_SPC,  KC_ENT,      KC_NO,   KC_NO, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|        |      ~ |      & |      | |      - |      * |                    |      ^ |      " |      ) |      } |      ] |        |
        KC_NO, KC_TILD, KC_AMPR, KC_PIPE, KC_MINS, KC_ASTR,                      KC_CIRC,  KC_DQT, KC_RPRN, KC_RCBR, KC_RBRC,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |      ` |    CTRL| OPT/ALT|    CMD |      = |                    |      % |      ' |      ( |      { |      [ |        |
        KC_NO,  KC_GRV,  O_CTRL,   O_ALT,   O_GUI,  KC_EQL,                      KC_PERC, KC_QUOT, KC_LPRN, KC_LCBR, KC_LBRC,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |      < |      > |      # |      _ |      + |                    |      $ |      @ |      \ |      ; |      : |        |
        KC_NO,   KC_LT,   KC_GT, KC_HASH, KC_UNDS, KC_PLUS,                       KC_DLR,   KC_AT, KC_BSLS, KC_SCLN, KC_COLN,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |        |        |  |        |  SHIFT |        |
                                            KC_NO, KC_TRNS,   KC_NO,      KC_NO,  O_SHFT,  KC_NO
                                      //`--------------------------'  `--------------------------'
  ),

  // Nav w/ mouse controls
  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|        |    ESC |MISSION | Capture| Capture|  Print |                    |   PGUP |   HOME |      ↑ |    END |    DEL |        |
  //|        |        | Control| Portion| Section| Screen |                    |        |        |        |        |        |        |
        KC_NO,  KC_ESC, KC_MCTL,SCRN_CAP4,SCRN_CAP5,KC_PSCR,                     KC_PGUP, KC_HOME,   KC_UP,  KC_END,  KC_DEL,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |  shift |    CTRL| OPT/ALT|    CMD |        |                    |   PGDN |      ← |      ↓ |      → |        |        |
        KC_NO,  O_SHFT,  O_CTRL,   O_ALT,   O_GUI,   KC_NO,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |   Undo |    Cut |  Paste |   Copy |        |                    |        |   Zoom |   Zoom |Decrease|Increase|        |
  //|        |        |        |        |        |        |                    |        |    Out |     In |   Size |   Size |        |
        KC_NO,  U_UNDO,   U_CUT, U_PASTE,  U_COPY,   KC_NO,                        KC_NO,ZOOM_OUT, ZOOM_IN,DEC_SIZE,INC_SIZE,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |        |        |  |        |        |        |
                                            KC_NO,   KC_NO, KC_TRNS,       KC_NO,  KC_NO,    KC_NO         
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

// td_state_t cur_dance(tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // Key has not been interrupted, but the key is still held. Means you wanat to send a 'HOLD'
//         else return TD_SINGLE_HOLD;
//     }
//     if (state->count == 2){
//         // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
//         // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
//         // keystrokes of the key, and not the 'double tap' action/macro.
//         if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
//         else if (state->pressed) return TD_DOUBLE_HOLD;
//         else return TD_DOUBLE_TAP;
//     } 
//     else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
// }

// Handle the possible states for each tapdance keycode you define:
// void tdlp_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: register_code16(KC_LCBR); break; // left curly braces, {}
//         case TD_SINGLE_HOLD: register_code(KC_LBRC); break; // left brackets, []
//         // case TD_DOUBLE_TAP: register_code(KC_LBRC); break; // left brackets, []
//         case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LCBR); register_code16(KC_LCBR); break; // fast typing, ((
//         default: break;
//     }
// }

// void tdlp_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: unregister_code16(KC_LCBR); break; // left curly braces, {}
//         case TD_SINGLE_HOLD: unregister_code(KC_LBRC); break; // left brackets, []
//         // case TD_DOUBLE_TAP: unregister_code(KC_LBRC); break; // left brackets, []
//         case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LCBR); break; // fast typing, ((
//         default: break;
//     }
//     td_state = TD_NONE;
// }

// void tdrp_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: register_code16(KC_RCBR); break; // left parens, ()
//         case TD_SINGLE_HOLD: register_code(KC_RBRC); break; // left curly braces, {}
//         // case TD_DOUBLE_TAP: register_code(KC_RBRC); break; // left brackets, []
//         case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RCBR); register_code16(KC_RCBR); break; // fast typing, ((
//         default: break;
//     }
// }

// void tdrp_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: unregister_code16(KC_RCBR); break; // left parens, ()
//         case TD_SINGLE_HOLD: unregister_code(KC_RBRC); break; // left curly braces, {}
//         // case TD_DOUBLE_TAP: unregister_code(KC_RBRC); break; // left brackets, []
//         case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RCBR); break; // fast typing, ((
//         default: break;
//     }
//     td_state = TD_NONE;
// }

// void td_sticky_shift_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     static bool held = false; // static variable to remember state.
//     switch (td_state) {
//         case TD_SINGLE_TAP: 
//             if(held) {
//                 unregister_code(KC_LSFT); // if we are ending a shift toggle
//                 held = !held; 
//             } else {
//                 set_oneshot_mods(MOD_BIT(KC_LSFT)); // tap for oneshot shift
//             }
//             break;
//         case TD_SINGLE_HOLD: register_code(KC_LSFT); break; // hold for normal shift
//         case TD_DOUBLE_TAP: // double tap for toggle shift
//             held = !held; // toggle between held and release
//             if(held) {
//                 register_code(KC_LSFT);
//             } else {
//                 unregister_code(KC_LSFT);
//             }
//             break;
//         default: break;
//     }
// }

// void td_sticky_shift_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: break; // one shot shift still active
//         case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break; // shift
//         case TD_DOUBLE_TAP: break; // Caps Lock
//         default: break;
//     }
//     td_state = TD_NONE;
// }

// void tdlayr_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: 
//             // Check to see if the NUM layer is already set
//             if(layer_state_is(2)){
//                 layer_off(2);
//             } else {
//                 layer_on(2);
//             }
//             break;
//         case TD_DOUBLE_TAP:
//             // Check to see if the NAV layer is already set
//             if(layer_state_is(4)){
//                 layer_off(4);
//             } else {
//                 layer_on(4);
//             }
//         default: break;
//     }
// }

// void tdlayr_reset(tap_dance_state_t *state, void *user_data) {
//     td_state = TD_NONE;
// }

// void tdm1_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: register_code(KC_MS_BTN1); break; // mouse button, left click
//         case TD_SINGLE_HOLD: register_code(KC_LGUI); break; // CMD when held
//         default: break;
//     }
// }

// void tdm1_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: unregister_code(KC_MS_BTN1); break; // mouse button, left click
//         case TD_SINGLE_HOLD: unregister_code(KC_LGUI); break; // release CMD
//         default: break;
//     }
//     td_state = TD_NONE;
// }

// void tdm2_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: register_code(KC_MS_BTN2); break; // mouse button, right click
//         case TD_SINGLE_HOLD: register_code(KC_LCTL); break; // CTRL when held
//         default: break;
//     }
// }

// void tdm2_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: unregister_code(KC_MS_BTN2); break; // mouse button, right click
//         case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break; // release CTRL
//         default: break;
//     }
//     td_state = TD_NONE;
// }
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
// tap_dance_action_t tap_dance_actions[] = {
    // [TD_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlp_finished, tdlp_reset),
    // [TD_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdrp_finished, tdrp_reset),
    // [TD_SHFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sticky_shift_finished, td_sticky_shift_reset),
    // [TD_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlayr_finished, tdlayr_reset),
    // [TD_M1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdm1_finished, tdm1_reset),
    // [TD_M2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdm2_finished, tdm2_reset),
// };

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record){
    switch(keycode) {
        // case TD(TD_SHFT): return 275;
        // case TD(TD_LAYR): return 275;
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
    // Common shortcuts on HOLD (Cut, Copy, Paste, Undo)
    case LT(0,KC_X):
    case LT(1,KC_X):
        if (!record->tap.count && record->event.pressed) {
             // Intercept hold function to send Ctrl-X
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_X));
            } else {
                tap_code16(G(KC_X));
            }
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_C):
    case LT(1,KC_C):
            if (!record->tap.count && record->event.pressed) {
             // Intercept hold function to send Ctrl-C
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_C));
            } else {
                tap_code16(G(KC_C));
            }
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_V):
    case LT(1,KC_V):
        if (!record->tap.count && record->event.pressed) {
             // Intercept hold function to send Ctrl-V
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_V));
            } else {
                tap_code16(G(KC_V));
            }
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case LT(0,KC_Z):
    case LT(1,KC_Z):
        if (!record->tap.count && record->event.pressed) {
             // Intercept hold function to send Ctrl-Z
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_Z));
            } else {
                tap_code16(G(KC_Z));
            }
            return false;
        }
        return true;             // Return true for normal processing of tap keycode
    case U_UNDO:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_Z));
            } else {
                tap_code16(G(KC_Z));
            }
        }
        break;
    case U_PASTE:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_V));
            } else {
                tap_code16(G(KC_V));
            }
        }
        break;
    case U_COPY:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_C));
            } else {
                tap_code16(G(KC_C));
            }
        }
        break;
    case U_CUT:
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code16(C(KC_X));
            } else {
                tap_code16(G(KC_X));
            }
        }
        break;
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
