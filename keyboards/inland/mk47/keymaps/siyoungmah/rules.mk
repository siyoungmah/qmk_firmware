RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.

OS_DETECTION_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes	#OS Detection takes some time and needs to be deferred

# TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
# COMBO_ENABLE = yes
# CONSOLE_ENABLE = yes

SRC += features/custom_shift_keys.c features/achordion.c