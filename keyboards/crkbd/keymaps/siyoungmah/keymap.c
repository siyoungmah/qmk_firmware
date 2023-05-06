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
#include "os_detection.h"

//====CUSTOM KEYS AND SHORTHANDS=======
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

// custom keycodes for Macros
enum custom_keycodes {
    SHFT_TOG = SAFE_RANGE,
};

// =======Tap Dancing=======

// Tap Dance keycodes
enum td_keycodes {
    TD_LP, // single tap (, double tap [, hold {
    TD_RP, // single tap ), double tap ], hold }};
    TD_CAPS, // single tap shift, hold shift, double tap CAPS LOCK
    TD_LAYR, // toggle layers (NUM and NAV)
    TD_AS, // Alt, but Alt + Shift when douple tap hold
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
void tdcaps_finished(tap_dance_state_t *state, void *user_data);
void tdcaps_reset(tap_dance_state_t *state, void *user_data);
void tdlayr_finished(tap_dance_state_t *state, void *user_data);
void tdlayr_reset(tap_dance_state_t *state, void *user_data);
// void tdas_finished(tap_dance_state_t *state, void *user_data);
// void tdas_reset(tap_dance_state_t *state, void *user_data);


//=======LAYOUT==========

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // base, Colemak_DH
  [0] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ` ~ |           Q |           W |           F |           P |      B |                    |      J |           L |           U |           Y |         ' " |    DEL |
      ESC_GRV0,         KC_Q,         KC_W,         KC_F,         KC_P,    KC_B,                         KC_J,         KC_L,         KC_U,         KC_Y,      KC_QUOT,  KC_DEL,       
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //| Mission |           A |           R |           S |           T |      G |                    |      M |           N |           E |           I |           O |    ; : |
  //| Command |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
       CTRL_UP, LCTL_T(KC_A), LALT_T(KC_R), LGUI_T(KC_S), LSFT_T(KC_T),    KC_G,                         KC_M, RSFT_T(KC_N), RGUI_T(KC_E), RALT_T(KC_I), RCTL_T(KC_O), KC_SCLN, 
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------| 
  //|  Spot-  |           Z |           X |           C |           D |      V |                    |      K |           H |         , < |         . > |         / ? |   KOR/ |
  //|   light |             |             |             |             |        |                    |        |             |             |             |             |    ENG |    
       CMD_SPC,         KC_Z,         KC_X,         KC_C,         KC_D,    KC_V,                         KC_K,         KC_H,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(1),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |      TOGGLE |       SHIFT |           TAB |     |          ENTER |       SPACE |        BSPC |        
  //                                      |     NUM/NAV |    CAPSLOCK |       SYMBOLS |     |           FUNC |             |             |        
                                             TD(TD_LAYR),   TD(TD_CAPS),   LT(4,KC_TAB),          LT(2,KC_ENT),       KC_SPC,      KC_BSPC
                                        //`-------------------------------------------'     `--------------------------------------------'
  ),
  
  //base_2, QWERTY for Korean
  [1] = LAYOUT_split_3x6_3(
  //,--------------------------------------------------------------------------.                    ,-------------------------------------------------------------------------.
  //|     ` ~ |           Q |           W |           E |           R |      T |                    |      Y |           U |           I |           O |         ' " |    DEL |
      ESC_GRV1,         KC_Q,         KC_W,         KC_E,         KC_R,    KC_T,                         KC_Y,         KC_U,         KC_I,         KC_O,      KC_QUOT, KC_DEL,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //| Mission |           A |           S |           D |           F |      G |                    |      H |           J |           K |           L |             |    ; : |
  //| Command |        CTRL |     OPT/ALT |         CMD |       SHIFT |        |                    |        |       SHIFT |         CMD |     OPT/ALT |        CTRL |        | 
       CTRL_UP, LCTL_T(KC_A), LALT_T(KC_S),   LGUI(KC_D), LSFT_T(KC_F),    KC_G,                         KC_H,  RSFT_T(KC_J), RGUI_T(KC_K),RALT_T(KC_L),      KC_RCTL, KC_SCLN,
  //|---------+-------------+-------------+-------------+-------------+--------|                    |--------+-------------+-------------+-------------+-------------+--------|
  //|  Spot-  |           Z |           X |           C |           V |      B |                    |      N |           M |         , < |         . > |         / ? |   KOR/ |
  //|   light |             |             |             |             |        |                    |        |             |             |             |             |    ENG |
       CMD_SPC,         KC_Z,         KC_X,         KC_C,         KC_V,    KC_B,                         KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,   DF(0),
  //|---------+-------------+-------------+-------------+-------------+---------------`     |----------------+-------------+-------------+-------------+-------------+--------|
  //                                      |      TOGGLE |       SHIFT |           TAB |     |          ENTER |       SPACE |        BSPC |        
  //                                      |     NUM/NAV |    CAPSLOCK |       SYMBOLS |     |           FUNC |             |             |        
                                             TD(TD_LAYR),   TD(TD_CAPS),   LT(4,KC_TAB),          LT(2,KC_ENT),       KC_SPC,      KC_BSPC
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
                                        //|        |        |        |  |        |        |        |
                                              KC_NO,   KC_NO,   KC_NO,    KC_TRNS,   KC_NO,    KC_NO
                                        //`--------------------------'  `--------------------------'
  ),

  // NUM
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,------------------------------------------------------.
  //|        |        |      7 |      8 |      9 |      0 |                    |        |      + |        |       * |        |    DEL |
  //|        |        |   Home |      ↑ |   PGUP |    INS |                    |        |        |        |         |        |        |
        KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,   KC_P0,                        KC_NO, KC_PPLS,   KC_NO,  KC_PAST,   KC_NO,  KC_DEL, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|    ( { |    ) } |      4 |      5 |      6 |      : |                    |        |      - |      ↑ |       / |   CTRL |        |
  //|      [ |      ] |      ← |        |      → |      ; |                    |        |  SHIFT |    CMD | OPT/ALT |   CTRL |        |
    TD(TD_LP),TD(TD_RP),   KC_P4,   KC_P5,   KC_P6, KC_COLN,                        KC_NO, SFT_MIN,  GUI_UP,  ALT_DIV, KC_RCTL,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+---------+--------+--------|
  //|      < |      > |      1 |      2 |      3 |      = |                    |        |      ← |      ↓ |       → |        |        |
  //|      , |      . |    END |      ↓ |   PGDN |        |                    |        |        |        |         |        |        |
      KC_COMM,  KC_DOT,   KC_P1,   KC_P2,   KC_P3,  KC_EQL,                        KC_NO, KC_LEFT, KC_DOWN,  KC_RGHT,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+---------+--------+--------|
                                      //|        |  SHIFT |    TAB |  |    ENT |    SPC |    BSPC |
                                            TG(3), KC_LSFT,  KC_TAB,     KC_ENT,  KC_SPC,  KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols
  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //|      ! |      @ |      # |      $ |      % |      ^ |                    |      & |      * |      ( |      ) |    ' " |  BSPC  |
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_CIRC,                      KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |   CTRL | OPT/ALT|    CMD |  SHIFT |        |                    |        |    = + |      < |     > |     \ | |   ; :  |
        KC_NO,  O_CTRL,   O_ALT,   O_GUI,  O_SHFT,   KC_NO,                        KC_NO,  KC_EQL,   KC_LT,  KC_GT,  KC_BSLS, KC_SCLN, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //|        |        |        |        |        |        |                    |        |        |    , < |    . > |    / ? |        |
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |        |        |  |  ( [ { |  } ] ) |    - _ |
                                            KC_NO,   KC_NO, KC_TRNS,  TD(TD_LP),TD(TD_RP), KC_MINS
                                      //`--------------------------'  `--------------------------'
  ),

  // Nav
  [5] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  //| M SPD 2|        | M WH ↑ |    M ↑ | M WH ↓ |        |                    |        |   HOME |      ↑ |    END |   PGUP |        |
      KC_ACL2,   KC_NO, KC_WH_U, KC_MS_U, KC_WH_D,   KC_NO,                        KC_NO, KC_HOME,   KC_UP,  KC_END, KC_PGUP,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //| M SPD 1| M WH ← |    M ← |    M ↓ |    M → | M WH → |                    |        |      ← |      ↓ |      → |   PGDN |        |
      KC_ACL1, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,                        KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  //| M SPD 0|        |        |        |        |        |                    |        |        |        |        |        |        |
      KC_ACL0,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      //|        |SHFT TOG|     ALT|  | M BTN R| M BTN L| M BTN M|
                                            TG(5),SHFT_TOG, KC_LALT,    KC_BTN2, KC_BTN1, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  )
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
        case TD_SINGLE_TAP: register_code16(KC_LPRN); break; // left parens, ()
        case TD_SINGLE_HOLD: register_code16(KC_LCBR); break; // left curly braces, {}
        case TD_DOUBLE_TAP: register_code16(KC_LBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LPRN); register_code16(KC_LPRN); break; // fast typing, ((
        default: break;
    }
}

void tdlp_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LPRN); break; // left parens, ()
        case TD_SINGLE_HOLD: unregister_code16(KC_LCBR); break; // left curly braces, {}
        case TD_DOUBLE_TAP: unregister_code16(KC_LBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LPRN); break; // fast typing, ((
        default: break;
    }
    td_state = TD_NONE;
}

void tdrp_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_RPRN); break; // left parens, ()
        case TD_SINGLE_HOLD: register_code16(KC_RCBR); break; // left curly braces, {}
        case TD_DOUBLE_TAP: register_code16(KC_RBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_RPRN); register_code16(KC_RPRN); break; // fast typing, ((
        default: break;
    }
}

void tdrp_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code16(KC_RPRN); break; // left parens, ()
        case TD_SINGLE_HOLD: unregister_code16(KC_RCBR); break; // left curly braces, {}
        case TD_DOUBLE_TAP: unregister_code16(KC_RBRC); break; // left brackets, []
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_RPRN); break; // fast typing, ((
        default: break;
    }
    td_state = TD_NONE;
}

void tdcaps_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: register_code16(KC_LSFT); break; // shift
        case TD_SINGLE_HOLD: register_code16(KC_LSFT); break; // shift
        case TD_DOUBLE_TAP: register_code16(KC_CAPS); break; // Caps Lock
        case TD_DOUBLE_SINGLE_TAP: tap_code16(KC_LSFT); register_code16(KC_LSFT); break; // fast typing
        default: break;
    }
}

void tdcaps_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP: unregister_code16(KC_LSFT); break; // shift
        case TD_SINGLE_HOLD: unregister_code16(KC_LSFT); break; // shift
        case TD_DOUBLE_TAP: unregister_code16(KC_CAPS); break; // Caps Lock
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(KC_LSFT); break; // fast typing
        default: break;
    }
    td_state = TD_NONE;
}

void tdlayr_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: 
            // Check to see if the NUM layer is already set
            if(layer_state_is(3)){
                layer_off(3);
            } else {
                layer_on(3);
            }
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the NAV layer is already set
            if(layer_state_is(5)){
                layer_off(5);
            } else {
                layer_on(5);
            }
        default: break;
    }
}

void tdlayr_reset(tap_dance_state_t *state, void *user_data) {
    td_state = TD_NONE;
}

// void tdas_finished(tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP: register_code(KC_LALT); break; // alt
//         case TD_SINGLE_HOLD: register_code(KC_LALT); break; // alt
//         case TD_DOUBLE_TAP: 
//             register_code(KC_LALT);
//             register_code(KC_LSFT);
//             break; // ALT + SHIFT
//         case TD_DOUBLE_HOLD: 
//             register_code(KC_LALT);
//             register_code(KC_LSFT);
//             break; // ALT + SHIFT
//         default: break;
//     }
// }

// void tdas_reset(tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP: unregister_code(KC_LALT); break; // alt
//         case TD_SINGLE_HOLD: unregister_code(KC_LALT); break; // alt
//         case TD_DOUBLE_TAP: 
//             unregister_code(KC_LALT);
//             unregister_code(KC_LSFT);
//             break; // ALT + SHIFT
//         case TD_DOUBLE_HOLD: 
//             unregister_code(KC_LALT);
//             unregister_code(KC_LSFT);
//             break; // ALT + SHIFT
//         default: break;
//     }
//     td_state = TD_NONE;
// }


// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlp_finished, tdlp_reset),
    [TD_RP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdrp_finished, tdrp_reset),
    [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdcaps_finished, tdcaps_reset),
    [TD_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdlayr_finished, tdlayr_reset),
    // [TD_AS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tdas_finished, tdas_reset),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record){
    switch(keycode) {
        case TD(TD_CAPS): return 275;
        case TD(TD_LAYR): return 275;
        case TD(TD_AS): return 275;
        default: return TAPPING_TERM;
    }
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t host_os = detected_host_os();
  switch (keycode) {
    // ESC + Grave
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

    // Toggle Shift On/Off
    case SHFT_TOG:
        if(record->event.pressed) { // when SHFT_TOG is pressed
            static bool held = false; // Static variable to remember state.
            held = !held; // toggle between holding and releasing
            if(held) {
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
            }
            return false;
        }
        break;
    
    // KOR <-> ENG, and QWERTY <-> Colemak
    case DF(1): // this runs when switching defaults from Colemak layer to QWERTY layer
        if (record->event.pressed) {
            if(host_os == OS_WINDOWS) {
                tap_code(KC_LNG1); // change languages on windows
            }
            else {
                tap_code(KC_CAPS); // change lanugages on mac
            }
        }
        break;

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
  }
  return true;
}

