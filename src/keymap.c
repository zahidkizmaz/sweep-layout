#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    L_TAP,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void l_finished(tap_dance_state_t *state, void *user_data);
void l_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [L_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_finished, l_reset)
};


// QMK keycodes https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        //+------------------------------------------------------------------------------------------+              +----------------------------------------------------------------------------------+/
        /**/ KC_Q        , KC_W        , KC_E          , KC_R                      , KC_T          ,/*              */ KC_Y              , KC_U           , KC_I           , KC_O        , KC_P    , /**/
        /**/ KC_A        , KC_S        , KC_D          , KC_F                      , KC_G          ,/*              */ KC_H              , KC_J           , KC_K           , KC_L        , KC_SCLN , /**/
        /**/ LSFT_T(KC_Z), KC_X        , LCTL_T(KC_C)  , LGUI_T(KC_V)              , LALT_T(KC_B)  ,/*              */ RALT_T(KC_N)      , RGUI_T(KC_M)   , RCTL_T(KC_COMM), KC_DOT      , RSFT_T(KC_SLSH) , /**/
        /*------------------------------------------*/   TD(L_TAP)                 , KC_SPC        ,/*              */ KC_ENT            , KC_BSPC        /*-------------------------------------------*/
                                                    /*----------------------------------------------*/              /*----------------------------------*/
    ),

    [_NAV] = LAYOUT(
        //+--------------------------------------------------------------------------------------------------------------------------------+          +----------------------------------------------------------------------------------+/
        /**/ KC_1              , KC_2          , KC_3                         , KC_4                       , KC_5                        ,/*          */ KC_6              , KC_7           , KC_8           , KC_9        , KC_0    , /**/
        /**/ KC_ESC            , KC_TAB        , KC_AUDIO_VOL_DOWN            , KC_AUDIO_VOL_UP            , KC_AUDIO_MUTE               ,/*          */ KC_LEFT           , KC_DOWN        , KC_UP          , KC_RGHT     , KC_NO , /**/
        /**/ KC_LSFT           , KC_NO         , LCTL_T(KC_MEDIA_PREV_TRACK)  , LGUI_T(KC_MEDIA_PLAY_PAUSE), LALT_T(KC_MEDIA_NEXT_TRACK) ,/*          */ KC_RIGHT_ALT      , KC_RIGHT_GUI   , KC_RIGHT_CTRL  , KC_NO       , KC_RSFT , /**/
        /*-----------------------------------------------------------------*/   TD(L_TAP)                  , KC_SPC                      ,/*          */ KC_ENT            , KC_BSPC        /*-------------------------------------------*/
                                                                            /*-------------------------------------------------------------*/         /*----------------------------------*/
    ),

    [_SYM] = LAYOUT(
        //+------------------------------------------------------------------------+       +-----------------------------------------------------------------------------------+
        /**/ KC_F1       , KC_F2       , KC_F3       , KC_F4            , KC_F5  ,/*       */ KC_F6      , KC_F7               , KC_F8             , KC_F9      , KC_F10   ,/**/
        /**/ KC_ESC      , KC_TAB      , KC_NO       , KC_NO            , KC_CAPS,/*       */ KC_MINUS   , KC_LPRN             , KC_RPRN           , KC_EQUAL   , KC_QUOTE ,/**/
        /**/ KC_LSFT     , KC_NO       , KC_LCTL     , KC_LGUI          , KC_LALT,/*       */ KC_UNDS    , KC_LEFT_BRACKET     , KC_RIGHT_BRACKET  , KC_BSLS    , KC_RSFT  ,/**/
        /*------------------------------------------*/ TD(L_TAP)        , KC_SPC ,/*       */ KC_ENT     , KC_BSPC         /*-------------------------------------------------*/
                                                    /*----------------------------*/       /*-----------------------------*/
    )
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed)
            return TD_SINGLE_HOLD;

        return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'l' tap dance.
static td_tap_t ltap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void l_finished(tap_dance_state_t *state, void *user_data) {
    ltap_state.state = cur_dance(state);
    switch (ltap_state.state) {
        case TD_SINGLE_TAP:
            layer_on(_BASE);
            layer_off(_NAV);
            layer_off(_SYM);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_BASE);
            layer_off(_NAV);
            layer_on(_SYM);
            break;
        case TD_DOUBLE_TAP:
            layer_off(_BASE);
            layer_on(_NAV);
            layer_off(_SYM);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_BASE);
            layer_off(_NAV);
            layer_on(_SYM);
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP:
            layer_off(_BASE);
            layer_on(_NAV);
            layer_off(_SYM);
            break;
        default: break;
    }
}

void l_reset(tap_dance_state_t *state, void *user_data) {
    switch (ltap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_BASE);
            layer_off(_NAV);
            layer_off(_SYM);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_BASE);
            layer_off(_NAV);
            layer_off(_SYM);
            break;
        default: break;
    }
    ltap_state.state = TD_NONE;
}
