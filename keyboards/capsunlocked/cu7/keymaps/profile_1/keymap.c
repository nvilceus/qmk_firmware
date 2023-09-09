/*
Copyright 2021 CapsUnlocked

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

// Define layers
enum my_layers {
	L1 = 0,
	L2,
	L3,
	L4,
	L5,
	L6,
	L7
};

// Light all LEDs red when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 0, 255, 200}
);

// Light all LEDs orange when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 5, 255, 200}
);

// Light all LEDs yellow when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 16, 255, 200}
);

// Light all LEDs green when keyboard layer 4 is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 82, 255, 200}
);

// Light all LEDs blue when keyboard layer 5 is active
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 92, 255, 200}
);

// Light all LEDs purple when keyboard layer 6 is active
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 6, 220, 255, 200}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,
	my_layer2_layer,
	my_layer3_layer,
	my_layer4_layer,
	my_layer5_layer,
	my_layer6_layer
);

// Call the post init code.
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers; // Enable the LED layers
}

// Macro Variable Declarations, important to start this type of instatiation with SAFE_RANGE to ensure true compiled keycodes don't interfere with iso encoding
enum custom_keycodes {
	MOVE_TO_L1 = SAFE_RANGE,
	PLAY
};

// Define a type for as many tap dance states as you need
typedef enum {
	TD_NONE,
    TD_UNKNOWN,
	TD_SINGLE_TAP,
	TD_SINGLE_HOLD,
	TD_DOUBLE_TAP
} td_state_t;

typedef struct {
	bool is_press_action;
	td_state_t state;
} td_tap_t;

enum {
	L_SWITCH, // Our custom tap dance key
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void lswitch_finished(tap_dance_state_t *state, void *user_data);
void lswitch_reset(tap_dance_state_t *state, void *user_data);

uint16_t L_LEVEL = L1;

// Keymaps for each layer
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L1] = LAYOUT(
                TD(L_SWITCH),
    KC_MNXT,    PLAY,    RSA(KC_F24),
    KC_MPRV,    KC_MUTE,    MEH(KC_F24)
  ),
  [L2] = LAYOUT(
               TD(L_SWITCH),
    KC_F13,    KC_F14,    KC_F15,
    KC_F16,    KC_F17,    KC_F18
  ),
  [L3] = LAYOUT(
               TD(L_SWITCH),
    KC_F19,    KC_F20,    KC_F21,
    KC_F22,    KC_F23,    KC_F24
  ),
  [L4] = LAYOUT(
                   TD(L_SWITCH),
    MEH(KC_F4),    MEH(KC_F5),    MEH(KC_F6),
    MEH(KC_F7),    MEH(KC_F10),    MEH(KC_F11)
  ),
  [L5] = LAYOUT(
                    TD(L_SWITCH),
    MEH(KC_F12),    MEH(KC_F13),    MEH(KC_F14),
    MEH(KC_F15),    MEH(KC_F16),    MEH(KC_F17)
  ),
  [L6] = LAYOUT(
                    TD(L_SWITCH),
    MEH(KC_F18),    MEH(KC_F19),    MEH(KC_F20),
    MEH(KC_F21),    MEH(KC_F22),    MEH(KC_F23)
  ),
  [L7] = LAYOUT(
               _______,
    KC_PWR,    MOVE_TO_L1,    QK_CLEAR_EEPROM,
    KC_SLEP,    RGB_TOG,    QK_BOOT
  ),
};

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, L1));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, L2));
	rgblight_set_layer_state(2, layer_state_cmp(state, L3));
	rgblight_set_layer_state(3, layer_state_cmp(state, L4));
	rgblight_set_layer_state(4, layer_state_cmp(state, L5));
	rgblight_set_layer_state(5, layer_state_cmp(state, L6));
    return state;
}

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t lswitch_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void lswitch_finished(tap_dance_state_t *state, void *user_data) {
    lswitch_tap_state.state = cur_dance(state);
    switch (lswitch_tap_state.state) {
        case TD_SINGLE_TAP:
            ++L_LEVEL;
			if (L_LEVEL > L6) {
				L_LEVEL = L1;
			}
			layer_move(L_LEVEL);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L7);
            break;
        case TD_DOUBLE_TAP:
			--L_LEVEL;
			if (L_LEVEL - L1 == -1) {
				L_LEVEL = L6;
			}
			layer_move(L_LEVEL);
            break;
        default:
            break;
    }
}

void lswitch_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (lswitch_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(L7);
    }
    lswitch_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [L_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lswitch_finished, lswitch_reset)
};

// Encoder mouse scrolling if holding encoder button else volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
	if (IS_LAYER_ON(L7)) {
		if (clockwise) {
			tap_code(KC_WH_U);
		}
		else {
			tap_code(KC_WH_D);
		}
	} 
	else {
		if (clockwise) {
			tap_code_delay(KC_VOLU, 6);
		} 
		else {
			tap_code_delay(KC_VOLD, 6);
		}
	} 
    return false;
}

// Functions for custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode){
		case MOVE_TO_L1:
			if(record->event.pressed){
				L_LEVEL = L1;
				layer_move(L_LEVEL);
			}
			else {
				return false;
			}
		case PLAY: // Made for built in action on keydown functionality caveat with KC_MPLY on L1 button 2 for case above
			if(record->event.pressed){
				return false;
			}
			else {
				tap_code(KC_MPLY);
			}
	}
	return true;
}