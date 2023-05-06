// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

/* Graphical active layer and modifier status display.
   Modified from @soundmonster's keymap:
   (keyboards/crkbd/keymaps/soundmonster)

   Usage guide
   1 Place this file next to keymap.c or in userspace.
   2 Add the following lines into rules.mk:
        OLED_ENABLE = yes
        SRC += oled-icons.c
   3 Add the following lines into the main 'oled_task_user()'
     function to render this module:
        extern void render_mod_status(void);
        render_mod_status();
   4 Add the font file reference into `config.h`:
        #define OLED_FONT_H "oledfont.c"
*/

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
static void render_logo(void) {
	static char const corne_logo[] PROGMEM = {
		0x80, 0x81, 0x82, 0x83, 0x84,
		0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
		0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};

	oled_write_P(corne_logo, false);
	oled_write_P(PSTR("corne"), false);
}


#define L_COLEMAK 0
#define L_QWERTY 1
#define L_NUM_FN 2
#define L_SYMBOLS 3
#define L_NAV 4

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case L_COLEMAK:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case L_QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case L_NUM_FN:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case L_SYMBOLS:
            oled_write_ln_P(PSTR("Symbols\n"), false);
            break;
        case L_NAV:
            oled_write_ln_P(PSTR("NAV\n"), false);
            break;  
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}


static void render_gui_alt(uint8_t const gui, uint8_t const alt) {
	static char const gui_off_1[] PROGMEM = {0x85, 0x86, 0};
	static char const gui_off_2[] PROGMEM = {0xa5, 0xa6, 0};
	static char const gui_on_1[]  PROGMEM = {0x8d, 0x8e, 0};
	static char const gui_on_2[]  PROGMEM = {0xad, 0xae, 0};

	static char const alt_off_1[] PROGMEM = {0x87, 0x88, 0};
	static char const alt_off_2[] PROGMEM = {0xa7, 0xa8, 0};
	static char const alt_on_1[]  PROGMEM = {0x8f, 0x90, 0};
	static char const alt_on_2[]  PROGMEM = {0xaf, 0xb0, 0};

	// Fillers between icon frames
	static char const off_off_1[] PROGMEM = {0xc5, 0};
	static char const off_off_2[] PROGMEM = {0xc6, 0};
	static char const on_off_1[]  PROGMEM = {0xc7, 0};
	static char const on_off_2[]  PROGMEM = {0xc8, 0};
	static char const off_on_1[]  PROGMEM = {0xc9, 0};
	static char const off_on_2[]  PROGMEM = {0xca, 0};
	static char const on_on_1[]   PROGMEM = {0xcb, 0};
	static char const on_on_2[]   PROGMEM = {0xcc, 0};

	// Top half with in between fillers
	oled_write_P(gui ? gui_on_1 : gui_off_1, false);
	if (gui && alt) { oled_write_P(on_on_1,   false); }
	else if (gui)   { oled_write_P(on_off_1,  false); }
	else if (alt)   { oled_write_P(off_on_1,  false); }
	else            { oled_write_P(off_off_1, false); }
	oled_write_P(alt ? alt_on_1 : alt_off_1, false);

	// Bottom half with in between fillers
	oled_write_P(gui ? gui_on_2 : gui_off_2, false);
	if (gui && alt) { oled_write_P(on_on_2,   false); }
	else if (gui)   { oled_write_P(on_off_2,  false); }
	else if (alt)   { oled_write_P(off_on_2,  false); }
	else            { oled_write_P(off_off_2, false); }
	oled_write_P(alt ? alt_on_2 : alt_off_2, false);
}


static void render_ctrl_shift(uint8_t const ctrl, uint8_t const shift) {
	static char const ctrl_off_1[] PROGMEM = {0x89, 0x8a, 0};
	static char const ctrl_off_2[] PROGMEM = {0xa9, 0xaa, 0};
	static char const ctrl_on_1[]  PROGMEM = {0x91, 0x92, 0};
	static char const ctrl_on_2[]  PROGMEM = {0xb1, 0xb2, 0};

	static char const shift_off_1[] PROGMEM = {0x8b, 0x8c, 0};
	static char const shift_off_2[] PROGMEM = {0xab, 0xac, 0};
	static char const shift_on_1[]  PROGMEM = {0xcd, 0xce, 0};
	static char const shift_on_2[]  PROGMEM = {0xcf, 0xd0, 0};

	// Fillers between icon frames
	static char const off_off_1[] PROGMEM = {0xc5, 0};
	static char const off_off_2[] PROGMEM = {0xc6, 0};
	static char const on_off_1[]  PROGMEM = {0xc7, 0};
	static char const on_off_2[]  PROGMEM = {0xc8, 0};
	static char const off_on_1[]  PROGMEM = {0xc9, 0};
	static char const off_on_2[]  PROGMEM = {0xca, 0};
	static char const on_on_1[]   PROGMEM = {0xcb, 0};
	static char const on_on_2[]   PROGMEM = {0xcc, 0};

	// Top half with in between fillers
	oled_write_P(ctrl ? ctrl_on_1 : ctrl_off_1, false);
	if (ctrl && shift) { oled_write_P(on_on_1,   false); }
	else if (ctrl)     { oled_write_P(on_off_1,  false); }
	else if (shift)    { oled_write_P(off_on_1,  false); }
	else               { oled_write_P(off_off_1, false); }
	oled_write_P(shift ? shift_on_1 : shift_off_1, false);

	// Bottom half with in between fillers
	oled_write_P(ctrl ? ctrl_on_2 : ctrl_off_2, false);
	if (ctrl && shift) { oled_write_P(on_on_2,   false); }
	else if (ctrl)     { oled_write_P(on_off_2,  false); }
	else if (shift)    { oled_write_P(off_on_2,  false); }
	else               { oled_write_P(off_off_2, false); }
	oled_write_P(shift ? shift_on_2 : shift_off_2, false);
}


// Primary modifier status display function
void render_mod_status(void) {
	uint8_t mods = get_mods();
#ifndef NO_ACTION_ONESHOT
	mods |= get_oneshot_mods();
#endif

	render_logo();
	oled_set_cursor(0,6);
	// render_layer_state(get_highest_layer(layer_state|default_layer_state));
  oled_render_layer_state();

	oled_set_cursor(0,11);
	render_gui_alt(mods & MOD_MASK_GUI, mods & MOD_MASK_ALT);
	render_ctrl_shift(mods & MOD_MASK_CTRL, mods & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock);
}
#endif // OLED_ENABLE