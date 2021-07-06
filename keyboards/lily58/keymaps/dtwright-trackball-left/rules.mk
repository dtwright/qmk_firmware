# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
LTO_ENABLE = yes  # if firmware size over limit, try this option

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. 
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_DRIVER_ENABLE = yes    # OLED display
TAP_DANCE_ENABLE = yes      # tap-dance (i.e., double-tapping sends alternate keycodes) support
COMBO_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

# If you want to change the display of OLED, you need to change here
SRC +=  ./lib/rgb_state_reader.c \
        ./lib/layer_state_reader.c \
        ./lib/logo_reader.c \
        ./lib/keylogger.c \
        # ./lib/mode_icon_reader.c \
        # ./lib/host_led_state_reader.c \
        # ./lib/timelogger.c \

# trackball stuff
PIMORONI_TRACKBALL_ENABLE = no
POINTING_DEVICE_ENABLE = yes
SPLIT_KEYBOARD = yes
SPLIT_TRANSPORT = trackball
NO_I2C = yes
USE_SERIAL = yes

ifeq ($(strip $(PIMORONI_TRACKBALL_ENABLE)), yes)
    SRC += pimoroni_trackball.c
    OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
endif

ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    ifeq ($(strip $(SPLIT_TRANSPORT)), trackball)
        SPLIT_TRANSPORT = custom
        QUANTUM_LIB_SRC += transport.c serial.c i2c_master.c i2c_slave.c
        OPT_DEFS += -DCUSTOM_TRANSPORT
        # Unused functions are pruned away, which is why we can add multiple drivers here without bloat.
        ifeq ($(PLATFORM),AVR)
            ifneq ($(NO_I2C),yes)
                QUANTUM_LIB_SRC += i2c_master.c \
                                   i2c_slave.c
            endif
        endif

        SERIAL_DRIVER ?= bitbang
        OPT_DEFS += -DSERIAL_DRIVER_$(strip $(shell echo $(SERIAL_DRIVER) | tr '[:lower:]' '[:upper:]'))
        ifeq ($(strip $(SERIAL_DRIVER)), bitbang)
            QUANTUM_LIB_SRC += serial.c
        else
            QUANTUM_LIB_SRC += serial_$(strip $(SERIAL_DRIVER)).c
        endif
    endif
endif

ifeq ($(PROMICRO), yes)
  BOOTLOADER = caterina
else ifeq ($(ELITEC), yes)
  BOOTLOADER = atmel-dfu
endif
