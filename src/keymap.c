#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _SYM,
    // _BOARD,
};

// Tap Dance declarations
enum {
    TD_LSFT_NAV,
    TD_LSFT_BASE,
    TD_SCLN_SYM,
};
// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_SCLN_SYM] = ACTION_TAP_DANCE_LAYER_MOVE(KC_SCLN, _SYM),
    [TD_LSFT_NAV] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LEFT_SHIFT, _NAV),
    [TD_LSFT_BASE] = ACTION_TAP_DANCE_LAYER_MOVE(KC_LEFT_SHIFT, _BASE),
};

// QMK keycodes https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        //+------------------------------------------------------------------------------------------+              +----------------------------------------------------------------------------------+/
        /**/ KC_Q        , KC_W        , KC_E          , KC_R                      , KC_T          ,/*              */ KC_Y              , KC_U           , KC_I           , KC_O        , KC_P    , /**/
        /**/ KC_A        , KC_S        , KC_D          , KC_F                      , KC_G          ,/*              */ KC_H              , KC_J           , KC_K           , KC_L        , TD(TD_SCLN_SYM) , /**/
        /**/ KC_Z        , KC_X        , LCTL_T(KC_C)  , LGUI_T(KC_V)              , LALT_T(KC_B)  ,/*              */ RALT_T(KC_N)      , RGUI_T(KC_M)   , RCTL_T(KC_COMM), KC_DOT      , KC_SLSH , /**/
        /*------------------------------------------*/   TD(TD_LSFT_NAV)           , KC_SPC        ,/*              */ KC_ENT            , KC_BSPC        /*-------------------------------------------*/
                                                    /*----------------------------------------------*/              /*----------------------------------*/
    ),

    [_NAV] = LAYOUT(
        //+--------------------------------------------------------------------------------------------------------------------------------+          +----------------------------------------------------------------------------------+/
        /**/ KC_1              , KC_2          , KC_3                         , KC_4                       , KC_5                        ,/*          */ KC_6              , KC_7           , KC_8           , KC_9        , KC_0    , /**/
        /**/ KC_ESC            , KC_TAB        , KC_AUDIO_VOL_DOWN            , KC_AUDIO_VOL_UP            , KC_AUDIO_MUTE               ,/*          */ KC_LEFT           , KC_DOWN        , KC_UP          , KC_RGHT     , TD(TD_SCLN_SYM) , /**/
        /**/ KC_TRNS           , KC_TRNS       , LCTL_T(KC_MEDIA_PREV_TRACK)  , LGUI_T(KC_MEDIA_PLAY_PAUSE), LALT_T(KC_MEDIA_NEXT_TRACK) ,/*          */ KC_RIGHT_ALT      , KC_RIGHT_GUI   , KC_RIGHT_CTRL  , KC_NO       , KC_TRNS , /**/
        /*-----------------------------------------------------------------*/   TD(TD_LSFT_BASE)           , KC_SPC                      ,/*          */ KC_ENT            , KC_BSPC        /*-------------------------------------------*/
                                                                            /*-------------------------------------------------------------*/         /*----------------------------------*/
    ),

    [_SYM] = LAYOUT(
        //+------------------------------------------------------------------------+       +-----------------------------------------------------------------------------------+
        /**/ KC_GRAVE    , KC_TRNS     , KC_TRNS     , KC_TRNS          , KC_TRNS,/*       */ KC_TRNS    , KC_LEFT_BRACKET     , KC_RIGHT_BRACKET  , KC_MINUS   , KC_EQUAL , /**/
        /**/ KC_TRNS     , KC_TRNS     , KC_TRNS     , KC_TRNS          , KC_TRNS,/*       */ KC_TRNS    , KC_LPRN             , KC_RPRN           , KC_UNDS    , KC_QUOTE, /**/
        /**/ QK_BOOT     , KC_TRNS     , KC_TRNS     , KC_TRNS          , KC_TRNS,/*       */ KC_TRNS    , KC_TRNS             , KC_TRNS           , KC_TRNS    , KC_TRNS , /**/
        /*------------------------------------------*/ TD(TD_LSFT_BASE) , KC_SPC ,/*       */ KC_ENT     , KC_BSPC         /*-------------------------------------------------*/
                                                    /*----------------------------*/       /*-----------------------------*/
    )

    // [_BOARD] = LAYOUT(
    //     //+------------------------------------------------------------------------+       +------------------------------------------------------------------------+
    //     /**/ KC_NO       , KC_NO       , KC_NO       , KC_NO       , KC_NO       ,/*       */ KC_NO       , KC_NO       , KC_NO       , KC_NO       , KC_NO    , /**/
    //     /**/ KC_NO       , KC_NO       , KC_NO       , KC_NO       , QK_BOOT     ,/*       */ QK_BOOT     , KC_NO       , KC_NO       , KC_NO       , KC_NO    , /**/
    //     /**/ KC_NO       , KC_NO       , KC_NO       , KC_NO       , KC_NO       ,/*       */ KC_NO       , KC_NO       , KC_NO       , KC_NO       , KC_NO    , /**/
    //     /*------------------------------------------*/ KC_TRNS     , KC_TRNS     ,/*       */ KC_TRNS     , KC_TRNS       /*---------------------------------------*/
    //                                                 /*----------------------------*/       /*-----------------------------*/
    // )
};
