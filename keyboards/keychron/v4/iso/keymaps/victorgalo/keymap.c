/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "keymap_extras/keymap_spanish.h"
#include QMK_KEYBOARD_H
#include "quantum.h"

bool onMac = false;

bool isCapsLockOn;

bool dash_mode = false;
uint16_t last_keycode = KC_NO;
uint16_t last_separator_keycode = KC_NO;
uint16_t last_space_time = 0;

enum custom_keycodes {
    QK_COPY = SAFE_RANGE,
    QK_PASTE,
    QK_CUT,
    QK_UNDO,
    QK_REDO
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

/* HOME ROW MODS */
// Left-hand home row mods
#define SFT_A LSFT_T(KC_A)
#define GUI_S LGUI_T(KC_S)
#define CTL_D LCTL_T(KC_D)
#define ALT_F LALT_T(KC_F)

// Mac variation
#define CTL_S LCTL_T(KC_S)
#define GUI_D LGUI_T(KC_D)

// Right-hand home row mods
#define ALT_J RALT_T(KC_J)
#define CTL_K RCTL_T(KC_K)
#define GUI_L RGUI_T(KC_L)
#define SFT_SCLN RSFT_T(KC_SCLN)

// Mac variation
#define CTL_L RCTL_T(KC_L)
#define GUI_K RGUI_T(KC_K)

/*
Function to set color with hsv arguments
- "hue", "sat" and "val" arguments above 255 will get value from rgb matrix config
- "val_ratio" is used to adjust brightness ratio
*/
void rgb_matrix_set_color_hsv(uint8_t led, uint16_t hue, uint16_t sat, uint16_t val, float val_ratio) {
    const uint8_t h = hue <= 255 ? hue : rgb_matrix_config.hsv.h;
    const uint8_t s = sat <= 255 ? sat : rgb_matrix_config.hsv.s;
    const uint8_t v = val <= 255 ? val * val_ratio : rgb_matrix_config.hsv.v * val_ratio;
    HSV hsv_in = {h, s, v};
    RGB rgb_out = hsv_to_rgb(hsv_in);
    rgb_matrix_set_color(led, rgb_out.r, rgb_out.g, rgb_out.b);
}

enum layers {
    _BASE_WIN,
    _BASE_MAC,
    _SWITCHER,
    _NAV,
    _NUM,
    _MEDIA,
    _EXTRA,
    _GAMING
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    if (pressed) {
        switch (keycode) {
            case TO(_BASE_MAC):
                onMac = true;
                break;
            case TO(_BASE_WIN):
                onMac = false;
                break;
            case QK_COPY:
                if (onMac) {
                    SEND_STRING(SS_LGUI("c"));
                } else {
                    SEND_STRING(SS_LCTL("c"));
                }
                break;
            case QK_PASTE:
                if (onMac) {
                    SEND_STRING(SS_LGUI("v"));
                } else {
                    SEND_STRING(SS_LCTL("v"));
                }
                break;
            case QK_CUT:
                if (onMac) {
                    SEND_STRING(SS_LGUI("x"));
                } else {
                    SEND_STRING(SS_LCTL("x"));
                }
                break;
            case QK_UNDO:
                if (onMac) {
                    SEND_STRING(SS_LGUI("z"));
                } else {
                    SEND_STRING(SS_LCTL("z"));
                }
                break;
            case QK_REDO:
                if (onMac) {
                    SEND_STRING(SS_LGUI(SS_LSFT("z")));
                } else {
                    SEND_STRING(SS_LCTL(SS_LSFT("z")));
                }
                break;
        }
    }

    return true;
}


void led_set_user(uint8_t usb_led) {
    if (usb_led & 2) {
        isCapsLockOn = true;
    } else {
        isCapsLockOn = false;
    }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_WIN] = LAYOUT_60_iso(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
        QK_LEAD,    SFT_A,   GUI_S,   CTL_D,   ALT_F,   KC_G,    KC_H,    ALT_J,   CTL_K,    GUI_L,    SFT_SCLN, KC_QUOT,  KC_NUHS,  KC_ENT,
        SC_LSPO, MO(_NUM),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,            SC_RSPC,
        KC_LCTL, KC_LWIN,  KC_LALT,                            LT(_NAV, KC_SPC),                       KC_RALT,  KC_LEFT,  KC_DOWN,  MO(_SWITCHER)),

    [_BASE_MAC] = LAYOUT_60_iso(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
        QK_LEAD,    SFT_A,   CTL_S,   GUI_D,   ALT_F,   KC_G,    KC_H,    ALT_J,   GUI_K,    CTL_L,    SFT_SCLN, KC_QUOT,  KC_NUHS,  KC_ENT,
        SC_LSPO, MO(_NUM),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,            SC_RSPC,
        KC_LCTL, KC_LALT,  KC_LWIN,                            LT(_NAV, KC_SPC),                       KC_RALT,  KC_LEFT,  KC_DOWN,  LT(_SWITCHER, KC_RIGHT)),

    [_SWITCHER] = LAYOUT_60_iso(
        KC_ESC,  TO(_BASE_WIN),    TO(_BASE_MAC),    TO(_MEDIA),    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     TO(_GAMING),     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    RGB_SPD,    RGB_SPI,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
        KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_G,    KC_H,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT, KC_NUBS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_UP,            KC_RSFT,
        KC_LCTL, KC_LWIN,  KC_LALT,                            LT(_NAV, KC_SPC),                       KC_LEFT,  KC_DOWN,  KC_RIGHT,  LT(_SWITCHER, KC_RIGHT)),

    [_NAV] = LAYOUT_60_iso(
        KC_GRV,             KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,     KC_F7,     KC_F8,     KC_F9,      KC_F10,     KC_F11,     KC_F12,              KC_BSPC,
        KC_TAB,             KC_Q,       KC_W,       KC_E,       QK_REP,     QK_AREP,    KC_PGUP,   KC_HOME,   KC_UP,      KC_END,     KC_BSPC,    KC_DEL,              KC_RBRC,
        KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_G,       KC_PGDN,   KC_LEFT,   KC_DOWN,   KC_RIGHT,   KC_ENT,     KC_SCLN,             KC_NUHS,             KC_ENT,
        KC_LSFT, QK_REDO,   QK_UNDO,    QK_CUT,     QK_COPY,    QK_PASTE,   KC_SPC,     KC_N,      QK_REP,    QK_AREP,   KC_DOT,     KC_SLSH,      KC_RSFT,
        KC_LCTL, KC_TRNS,   KC_TRNS,                            KC_SPC,                                                  KC_TRNS,    KC_LEFT,    KC_DOWN,    LT(_SWITCHER, KC_RIGHT)),

    [_NUM] = LAYOUT_60_iso(
        KC_GRV,     KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,     KC_TRNS,     KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_BSPC,
        KC_TAB,     KC_Q,      KC_W,       KC_E,       QK_REP,     QK_AREP,    KC_PLUS,     KC_P7,     KC_P8,    KC_P9,     KC_P0,    KC_TRNS,     KC_RBRC,
        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_G,       KC_EQL,     KC_P4,     KC_P5,    KC_P6,    KC_PAST,     KC_SCLN,    KC_NUHS,    KC_ENT,
        KC_LSFT,    QK_REDO,   QK_UNDO,    QK_CUT,     QK_COPY,    QK_PASTE,   KC_SPC,     KC_MINS,   KC_P1,    KC_P2,   KC_P3,     KC_SLSH,      KC_RSFT,
        KC_LCTL,    KC_TRNS,   KC_TRNS,                            KC_SPC,                                                  KC_DOT,    KC_LEFT,    KC_DOWN,    LT(_SWITCHER, KC_RIGHT)),

    [_MEDIA] = LAYOUT_60_iso(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_TASK, KC_FLXP, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, KC_APP,  KC_SCRL,  KC_INS,   KC_PGUP,  KC_HOME,
        KC_TRNS, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, KC_UP,   KC_PSCR,  KC_PGDN,  KC_END,   _______,  _______,
        _______, _______,  _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_DEL,             _______,
        _______, _______,  _______,                            _______,                             _______,  _______,  _______,  TO(_SWITCHER)),

    [_EXTRA] = LAYOUT_60_iso(
        KC_GRV,  KC_BRID,  KC_BRIU, KC_NO,   KC_NO,   RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_MOD,
        RGB_TOG, RGB_MOD,  RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______,  KC_INS,   KC_PGUP,  KC_HOME,
        KC_TRNS, RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, KC_UP,   _______,  KC_PGDN,  KC_END,   _______,  _______,
        _______, _______,  _______, _______, _______, _______, _______, NK_TOGG, KC_LEFT, KC_DOWN,  KC_RIGHT, KC_DEL,   _______,
        _______, _______,  _______,                            _______,                             _______,  _______,  _______,  TO(_SWITCHER)),

    [_GAMING] = LAYOUT_60_iso(
        KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
        KC_TRNS,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_NUHS,  KC_ENT,
        KC_LSFT, KC_NUBS,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,             MT(MOD_RSFT, KC_UP),
        KC_LCTL, KC_LWIN,  KC_LALT,                            KC_SPC,                       KC_RALT,  KC_LEFT,  KC_DOWN,  TO(_SWITCHER)),
};


enum letter {
    _A,
    _E,
    _I,
    _O,
    _U,
    _N,
};

const uint8_t letter_index[8] = {
    [_A] = 0,
    [_E] = 1,
    [_I] = 2,
    [_O] = 3,
    [_U] = 4,
    [_N] = 5,
};

/*
This represent unicode decimal values
Each index will be mapped to numpad keycode to out put the correct sequence
*/
const uint8_t spanish_accent_decimal_unicodes[8][2] = {
    {
        160,    // á
        193     // Á
    },{
        130,    // é
        201     // É
    },{
        161,    // í
        205     // Í
    },{
        162,    // ó
        211     // Ó
    },{
        163,    // ú
        218     // Ú
    },
    {
        164,    // ñ
        209     // Ñ
    },
    {
        168,    // ¿
        168     // ¿
    },
    {
        173,    // ¡
        173     // ¡
    }
};

void break_int_in_array(uint8_t int_code, uint8_t *array) {
    uint8_t i = 0;
    uint8_t size = 0;
    uint8_t temp_code = int_code;

    // Calculate the number of digits in int_code
    do {
        size++;
        temp_code /= 10;
    } while (temp_code != 0);

    // Fill the array with digits from int_code
    for (i = size; i > 0; i--) {
        array[i - 1] = int_code % 10;
        int_code /= 10;
    }
}

void send_spanish_accent(uint8_t letter) {

    bool isCaps;
    uint8_t decimal_unicode_in;
    uint8_t decimal_unicode_size = 3;
    uint8_t decimal_unicode_out[decimal_unicode_size];

    /* Map to numpad keycodes */
    const uint16_t numpad_key_map[10] = {
        KC_P0, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9
    };

    /* Map to letter keycodes */
    const uint16_t vowel_letter_key_map[6] = {
        KC_A, KC_E, KC_I, KC_O, KC_U, KC_N
    };


    void tap_win_alt_code(void) {
        if (isCaps) {
            tap_code(numpad_key_map[0]); // Leading 0 on all upper case "Windows alt codes"
        }
        for (int i = 0; i < decimal_unicode_size; ++i) {
            tap_code(numpad_key_map[decimal_unicode_out[i]]);
        }
    }

    void tap_letter_key(uint8_t letter) {
    if (letter == 5) { // Check if the letter is KC_N (index 5 in vowel_letter_key_map)
        tap_code(KC_N);
    } else {
        tap_code(KC_E);
    }
}

    isCaps = isCapsLockOn ? true : false;

    if (onMac) {
        if (isCaps) {
            tap_code(KC_CAPS_LOCK);
            register_code(KC_LALT);
            tap_letter_key(letter);
            unregister_code(KC_LALT);
            register_code(KC_LSFT);
            tap_code(vowel_letter_key_map[letter]);
            unregister_code(KC_LSFT);
            tap_code(KC_CAPS);
        } else {
            register_code(KC_LALT);
            tap_letter_key(letter);
            unregister_code(KC_LALT);
            tap_code(vowel_letter_key_map[letter]);
        }
    } else {
        decimal_unicode_in = isCaps ? spanish_accent_decimal_unicodes[letter][1] : spanish_accent_decimal_unicodes[letter][0];
        break_int_in_array(decimal_unicode_in, decimal_unicode_out);
        register_code(KC_LALT);
        tap_win_alt_code();
        unregister_code(KC_LALT);
    }
}

void leader_end_user(void) {

    /*  CapsLock */
    if (leader_sequence_one_key(QK_LEAD)) {
        tap_code(KC_CAPS);
    }

    /* spanish accent (dead) -> LDR > [ */
    if (leader_sequence_one_key(KC_LBRC)) {
        tap_code(KC_QUOT);
    }

    /* áÁ -> LDR > A */
    if (leader_sequence_one_key(LSFT_T(KC_A))) {
        send_spanish_accent(_A);
    }

    /* éÉ -> LDR > E */
    if (leader_sequence_one_key(KC_E)) {
        send_spanish_accent(_E);
    }

    if (leader_sequence_one_key(KC_I)) {
        send_spanish_accent(_I);
    }

    if (leader_sequence_one_key(KC_O)) {
        send_spanish_accent(_O);
    }

    if (leader_sequence_one_key(KC_U)) {
        send_spanish_accent(_U);
    }

    if (leader_sequence_one_key(KC_N)) {
        send_spanish_accent(_N);
    }
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
    case KC_MINS:
      // Apply shift to the next key.
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case SC_LSPO:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}
