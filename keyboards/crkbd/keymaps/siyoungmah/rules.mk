MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.

OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306

LTO_ENABLE      = yes

OS_DETECTION_ENABLE = yes
# DEFERRED_EXEC_ENABLE = yes	#OS Detection takes some time and needs to be deferred

TAP_DANCE_ENABLE = yes

SRC += oled/oled-icons.c oled/oled-bongocat.c features/custom_shift_keys.c

