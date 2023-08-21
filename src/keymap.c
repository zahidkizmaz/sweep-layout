#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
    _BOARD,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    L_TAP,
    DOT_TAP,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void l_finished(tap_dance_state_t *state, void *user_data);
void l_reset(tap_dance_state_t *state, void *user_data);

void dot_finished(tap_dance_state_t *state, void *user_data);
void dot_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [L_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_finished, l_reset),
    [DOT_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_finished, dot_reset),
};


// QMK keycodes https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        //+------------------------------------------------------------------------------------------+          +-----------------------------------------------------------------------------------------+/
        /**/ KC_Q        , KC_W        , KC_E          , KC_R                      , KC_T          ,/*          */ KC_Y              , KC_U           , KC_I           , KC_O        , KC_P            ,/**/
        /**/ KC_A        , KC_S        , KC_D          , KC_F                      , KC_G          ,/*          */ KC_H              , KC_J           , KC_K           , KC_L        , KC_SCLN         ,/**/
        /**/ LSFT_T(KC_Z), KC_X        , LCTL_T(KC_C)  , LGUI_T(KC_V)              , LALT_T(KC_B)  ,/*          */ RALT_T(KC_N)      , RGUI_T(KC_M)   , RCTL_T(KC_COMM), TD(DOT_TAP) , RSFT_T(KC_SLSH) ,/**/
        /*------------------------------------------*/   TD(L_TAP)                 , KC_SPC        ,/*          */ KC_ENT            , KC_BSPC        /*--------------------------------------------------*/
                                                    /*----------------------------------------------*/          /*----------------------------------*/
    ),

    [_NAV] = LAYOUT(
        //+------------------------------------------------------------------------------------------------------+   +--------------------------------------------------------------------------------+/
        /**/ KC_1       , KC_2          , KC_3                   , KC_4                    , KC_5              ,/*   */ KC_6          , KC_7           , KC_8           , KC_9        , KC_0       ,/**/
        /**/ KC_ESC     , KC_TAB        , KC_AUDIO_VOL_DOWN      , KC_AUDIO_VOL_UP         , KC_AUDIO_MUTE     ,/*   */ KC_LEFT       , KC_DOWN        , KC_UP          , KC_RGHT     , RCTL(KC_A) ,/**/
        /**/ KC_LSFT    , TO(_BOARD)    , LCTL_T(KC_MPRV)        , LGUI_T(KC_MPLY)         , LALT_T(KC_MNXT)   ,/*   */ KC_RIGHT_ALT  , KC_RIGHT_GUI   , KC_RIGHT_CTRL  , TO(_BOARD)  , KC_RSFT    ,/**/
        /*-----------------------------------------------------*/  TD(L_TAP)               , KC_SPC            ,/*   */ KC_ENT        , KC_BSPC           /*------------------------------------------*/
                                                                /*----------------------------------------------*/   /*----------------------------------*/
    ),

    [_SYM] = LAYOUT(
        //+------------------------------------------------------------------------+       +-----------------------------------------------------------------------------------+
        /**/ KC_1        , KC_2        , KC_3        , KC_4             , KC_5   ,/*       */ KC_6       , KC_7                , KC_8              , KC_9       , KC_0     ,/**/
        /**/ KC_ESC      , KC_TAB      , KC_GRV      , KC_DQUO          , KC_CAPS,/*       */ KC_UNDS    , KC_LPRN             , KC_RPRN           , KC_EQUAL   , KC_QUOTE ,/**/
        /**/ KC_LSFT     , KC_NO       , KC_LCTL     , KC_LGUI          , KC_LALT,/*       */ KC_MINUS   , KC_LEFT_BRACKET     , KC_RIGHT_BRACKET  , KC_BSLS    , KC_RSFT  ,/**/
        /*------------------------------------------*/ TD(L_TAP)        , KC_SPC ,/*       */ KC_ENT     , KC_BSPC         /*-------------------------------------------------*/
                                                    /*----------------------------*/       /*-----------------------------*/
    ),

    [_BOARD] = LAYOUT(
        //+------------------------------------------------------------------------+       +------------------------------------------------------------------------+
        /**/ KC_F1       , KC_F2       , KC_F3       , KC_F4       , KC_F5       ,/*       */ KC_F6       , KC_F7       , KC_F8       , KC_F9       , KC_F10     ,/**/
        /**/ KC_NO       , KC_NO       , KC_BTN3     , KC_BTN1     , KC_BTN2     ,/*       */ KC_MS_L     , KC_MS_D     , KC_MS_U     , KC_MS_R     , KC_NO     ,/**/
        /**/ QK_BOOT     , KC_NO       , KC_NO       , KC_NO       , KC_SLEP     ,/*       */ KC_WH_L     , KC_WH_U     , KC_WH_D     , KC_WH_R     , QK_BOOT   ,/**/
        /*------------------------------------------*/ TD(L_TAP)   , KC_NO       ,/*       */ KC_NO       , TD(L_TAP)     /*---------------------------------------*/
                                                    /*----------------------------*/       /*----------------------------*/
    )
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed)
            return TD_SINGLE_HOLD;

        return TD_SINGLE_TAP;
    } else if (state->count == 2) {
        if (state->pressed)
            return TD_DOUBLE_HOLD;

        return TD_DOUBLE_TAP;
    }

    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'l' tap dance.
static td_tap_t ltap_state = {
    .state = TD_NONE
};
static td_tap_t dottap_state = {
    .state = TD_NONE
};

void l_finished(tap_dance_state_t *state, void *user_data) {
    ltap_state.state = cur_dance(state);
    switch (ltap_state.state) {
        case TD_SINGLE_TAP:
            layer_clear();
            layer_on(_BASE);
            break;
        case TD_SINGLE_HOLD:
            layer_clear();
            layer_on(_SYM);
            break;
        case TD_DOUBLE_TAP:
            layer_clear();
            layer_on(_NAV);
            break;
        case TD_DOUBLE_HOLD:
            layer_clear();
            layer_on(_SYM);
            break;
        default: break;
    }
}

void l_reset(tap_dance_state_t *state, void *user_data) {
    switch (ltap_state.state) {
        case TD_SINGLE_HOLD:
            layer_clear();
            layer_on(_BASE);
            break;
        case TD_DOUBLE_HOLD:
            layer_clear();
            layer_on(_BASE);
            break;
        default: break;
    }
    ltap_state.state = TD_NONE;
}

void dot_finished(tap_dance_state_t *state, void *user_data) {
    dottap_state.state = cur_dance(state);
    switch (dottap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_DOT);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_DOT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_DOT);
            register_code(KC_DOT);
            break;
        case TD_DOUBLE_HOLD:
            layer_clear();
            layer_on(_NAV);
            break;
        default: break;
    }
}

void dot_reset(tap_dance_state_t *state, void *user_data) {
    switch (dottap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_DOT);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_DOT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_DOT);
            break;
        default: break;
    }
    dottap_state.state = TD_NONE;
}
