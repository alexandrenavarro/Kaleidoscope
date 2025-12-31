// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 100's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for querying the firmware version via Focus
#include "Kaleidoscope-FirmwareVersion.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for turning the LEDs off after a certain amount of time
#include "Kaleidoscope-IdleLEDs.h"

// Support for overlaying colors
#include "Kaleidoscope-Colormap-Overlay.h"

// Support for setting and saving the default LED mode
#include "Kaleidoscope-DefaultLEDModeConfig.h"

// Support for changing the brightness of the LEDs
#include "Kaleidoscope-LEDBrightnessConfig.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for secondary actions on keys
#include "Kaleidoscope-Qukeys.h"

// Support for one-shot modifiers and layer keys
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

// Support for dynamic, Chrysalis-editable macros
#include "Kaleidoscope-DynamicMacros.h"

// Support for SpaceCadet keys
#include "Kaleidoscope-SpaceCadet.h"

// Support for editable layer names
#include "Kaleidoscope-LayerNames.h"

// Support for the GeminiPR Stenography protocol
#include "Kaleidoscope-Steno.h"

// Support for CharShift
#include "Kaleidoscope-CharShift.h"

// Support for HostOS
#include "Kaleidoscope-HostOS.h"

// Support for AutoShift
#include "Kaleidoscope-AutoShift.h"

/** This 'enum' is a list of all the macros used by the Model 100's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_A_CIRCUMFLEX,
       MACRO_A_GRAVE,
       MACRO_AT,
       MACRO_ALT_SPACE,
       MACRO_C_CEDILLA,
       MACRO_CLOSE,
       MACRO_CTRL_A,
       MACRO_CTRL_B,
       MACRO_CTRL_C,
       MACRO_CTRL_D,
       MACRO_CTRL_DOWN,
       MACRO_CTRL_E,
       MACRO_CTRL_END,
       MACRO_CTRL_ENTER,
       MACRO_CTRL_F,
       MACRO_CTRL_G,
       MACRO_CTRL_H,
       MACRO_CTRL_I,
       MACRO_CTRL_J,
       MACRO_CTRL_K,
       MACRO_CTRL_INSERT,
       MACRO_CTRL_HOME,
       MACRO_CTRL_L,
       MACRO_CTRL_LEFT,
       MACRO_CTRL_M,
       MACRO_CTRL_N,
       MACRO_CTRL_O,
       MACRO_CTRL_P,
       MACRO_CTRL_PAGE_DOWN,
       MACRO_CTRL_PAGE_UP,
       MACRO_CTRL_Q,
       MACRO_CTRL_R,
       MACRO_CTRL_RIGHT,
       MACRO_CTRL_S,
       MACRO_CTRL_SHIFT_F10,
       MACRO_CTRL_SPACE,
       MACRO_CTRL_T,
       MACRO_CTRL_U,
       MACRO_CTRL_UP,
       MACRO_CTRL_V,
       MACRO_CTRL_W,
       MACRO_CTRL_X,
       MACRO_CTRL_Y,
       MACRO_CTRL_Z,
       MACRO_E_ACUTE,
       MACRO_E_CIRCUMFLEX,
       MACRO_E_DIAERESIS,
       MACRO_E_GRAVE,
       MACRO_ESCAPE_ALT_F12_CTRL_P,
       MACRO_I_CIRCUMFLEX,
       MACRO_I_DIAERESIS,
       MACRO_MAXIMIZE,
       MACRO_MINIMIZE,
       MACRO_MOVE_LEFT,
       MACRO_MOVE_RIGHT,
       MACRO_NEXT_HISTORY,
       MACRO_O_CIRCUMFLEX,
       MACRO_PREVIOUS_HISTORY,
       MACRO_PRINT_OS,
       MACRO_SET_OS_LINUX,
       MACRO_SET_OS_MACOS,
       MACRO_SET_OS_WINDOWS,
       MACRO_SHIFT_CTRL_DOWN_X,
       MACRO_SHIFT_CTRL_END_X,
       MACRO_SHIFT_CTRL_HOME_X,
       MACRO_SHIFT_CTRL_LEFT_X,
       MACRO_SHIFT_CTRL_RIGHT_X,
       MACRO_SHIFT_CTRL_UP_X,
       MACRO_SHIFT_DOWN_CTRL_X,
       MACRO_SHIFT_END_CTRL_X,
       MACRO_SHIFT_HOME_CTRL_X,
       MACRO_SHIFT_PERCENT,
       MACRO_SHIFT_PG_DOWN_CTRL_X,
       MACRO_SHIFT_PG_UP_CTRL_X,
       MACRO_SHIFT_UP_CTRL_X,
       MACRO_SHIFT_SUPER_Z,
       MACRO_U_CIRCUMFLEX,
       MACRO_U_GRAVE,
       MACRO_U_DIAERESIS
     };


/** The Model 100's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, LETTER_VARIANT, SYMBOL, NUMPAD, FUNCTION, FUNCTION_VARIANT, NAV}; // layers
#define NUMROW NUMPAD

/**
  * To change your keyboard's layout from QWERTY to DVORAK or COLEMAK, comment out the line
  *
  * #define PRIMARY_KEYMAP_QWERTY
  *
  * by changing it to
  *
  * // #define PRIMARY_KEYMAP_QWERTY
  *
  * Then uncomment the line corresponding to the layout you want to use.
  *
  */

//#define PRIMARY_KEYMAP_QWERTY
//#define PRIMARY_KEYMAP_DVORAK
//#define PRIMARY_KEYMAP_COLEMAK
//#define PRIMARY_KEYMAP_CUSTOM

#define Space_Underscore             CS(0)
#define Dollar_Hash                  CS(1)
#define LeftParenthesis_Bracket      CS(2)
#define RightParenthesis_Bracket     CS(3)
#define Comma_SemiColon              CS(4)
#define Period_Colon                 CS(5)
#define Apostrophe_QuestionMark      CS(6)


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(

#if defined (PRIMARY_KEYMAP_QWERTY)
  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

#elif defined (PRIMARY_KEYMAP_DVORAK)

  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1,         Key_2,     Key_3,      Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Quote,     Key_Comma, Key_Period, Key_P, Key_Y, Key_Tab,
   Key_PageUp,   Key_A,         Key_O,     Key_E,      Key_U, Key_I,
   Key_PageDown, Key_Semicolon, Key_Q,     Key_J,      Key_K, Key_X, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),   Key_6, Key_7, Key_8, Key_9, Key_0, LockLayer(NUMPAD),
   Key_Enter,      Key_F, Key_G, Key_C, Key_R, Key_L, Key_Slash,
                   Key_D, Key_H, Key_T, Key_N, Key_S, Key_Minus,
   Key_RightAlt,   Key_B, Key_M, Key_W, Key_V, Key_Z, Key_Equals,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

#elif defined (PRIMARY_KEYMAP_COLEMAK)

  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_F, Key_P, Key_B, Key_Tab,
   Key_PageUp,   Key_A, Key_R, Key_S, Key_T, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_D, Key_V, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_J, Key_L, Key_U,     Key_Y,         Key_Semicolon, Key_Equals,
                  Key_M, Key_N, Key_E,     Key_I,         Key_O,         Key_Quote,
   Key_RightAlt,  Key_K, Key_H, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

#elif defined (PRIMARY_KEYMAP_CUSTOM)
  // Edit this keymap to make a custom layout
  [PRIMARY] = KEYMAP_STACKED
  (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

//#else

//#error "No default keymap defined. You should make sure that you have a line like '#define PRIMARY_KEYMAP_QWERTY' in your sketch"

#endif

  [PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY] = KEYMAP_STACKED
  (M(MACRO_PRINT_OS),                      ___,                                    ___,                                    ___,                                    LeftParenthesis_Bracket,                RightParenthesis_Bracket,               Key_Delete,
   Dollar_Hash,                            Key_B,                                  Key_2,                                  Key_P,                                  Key_O,                                  Key_7,                                  Key_Tab,
   Key_Z,                                  Key_Q,                                  Key_U,                                  Key_I,                                  Key_E,                                  Comma_SemiColon,
   Key_Equals,                             M(MACRO_A_GRAVE),                       Key_Y,                                  Key_X,                                  Period_Colon,                           Key_K,                                  Key_Enter,
   OSM(LeftShift),                         Key_Backspace,                          Key_Enter,                              OSM(LeftGui),
   Key_Escape,

   ___,                                    RALT(Key_0),                            LSHIFT(Key_Equals),                     Key_6,                                  LSHIFT(Key_Period),                     Key_Backslash,                          LSHIFT(Key_Quote),
   Key_3,                                  OSL(LETTER_VARIANT),                    Key_V,                                  Key_D,                                  Key_L,                                  Key_J,                                  Key_W,
                                           Key_C,                                  Key_T,                                  Key_S,                                  Key_R,                                  Key_N,                                  Key_Semicolon,
   Key_Insert,                             Apostrophe_QuestionMark,                Key_A,                                  Key_G,                                  Key_H,                                  Key_F,                                  RightParenthesis_Bracket,
   Key_RightAlt,                           OSL(SYMBOL),                            Space_Underscore,                       OSM(LeftShift),
   M(MACRO_ALT_SPACE)),

  [PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY] = KEYMAP_STACKED
  (M(MACRO_PRINT_OS),                      Key_Apple_Globe,                        LeftParenthesis_Bracket,                RightParenthesis_Bracket,               LeftParenthesis_Bracket,                RightParenthesis_Bracket,               Key_Delete,
   Dollar_Hash,                            Key_B,                                  Key_2,                                  Key_P,                                  Key_O,                                  Key_7,                                  Key_Tab,
   Key_Z,                                  Key_Q,                                  Key_U,                                  Key_I,                                  Key_E,                                  Comma_SemiColon,
   Key_Equals,                             Key_Equals,                             Key_Y,                                  Key_X,                                  Period_Colon,                           Key_K,                                  Key_Enter,
   OSM(LeftShift),                         Key_Backspace,                          Key_Enter,                              OSM(LeftGui),
   Key_Escape,

   ___,                                    Key_NonUsBackslashAndPipe,              LSHIFT(Key_Slash),                      Key_Equals,                             LSHIFT(Key_Period),                     LSHIFT(Key_RightBracket),               LSHIFT(Key_Quote),
   Key_3,                                  OSL(LETTER_VARIANT),                    Key_V,                                  Key_D,                                  Key_L,                                  Key_J,                                  Key_W,
                                           Key_C,                                  Key_T,                                  Key_S,                                  Key_R,                                  Key_N,                                  Key_Semicolon,
   Key_Insert,                             Apostrophe_QuestionMark,                Key_A,                                  Key_G,                                  Key_H,                                  Key_F,                                  RightParenthesis_Bracket,
   Key_RightAlt,                           OSL(SYMBOL),                            Space_Underscore,                       OSM(LeftShift),
   M(MACRO_ALT_SPACE)),


  [LETTER_VARIANT] =  KEYMAP_STACKED
  (___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    M(MACRO_A_CIRCUMFLEX),                  M(MACRO_U_CIRCUMFLEX),                  M(MACRO_I_CIRCUMFLEX),                  M(MACRO_O_CIRCUMFLEX),                  Key_Slash,                              ___,
   ___,                                    M(MACRO_A_GRAVE),                       M(MACRO_U_GRAVE),                       M(MACRO_I_DIAERESIS),                   M(MACRO_E_CIRCUMFLEX),                  ___,
   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    LSHIFT(Key_M),                          ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___,

   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    LSHIFT(Key_LeftBracket),                ___,                                    ___,                                    ___,                                    ___,                                    ___,
                                           M(MACRO_C_CEDILLA),                     ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___),

  [SYMBOL] =  KEYMAP_STACKED
  (___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    Key_LeftBracket,                        Key_NonUsBackslashAndPipe,              LSHIFT(Key_NonUsBackslashAndPipe),      Key_RightBracket,                       LSHIFT(Key_Quote),                      ___,
   ___,                                    RALT(Key_4),                            LeftParenthesis_Bracket,                RightParenthesis_Bracket,               RALT(Key_Equals),                       Key_Equals,
   ___,                                    RALT(Key_2),                            RALT(Key_5),                            RALT(Key_Minus),                        Key_8,                                  RALT(Key_3),                            ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___,

   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    RALT(Key_0),                            Key_1,                                  Key_Backslash,                          Apostrophe_QuestionMark,                RALT(Key_7),                            ___,
                                           RALT(Key_8),                            LSHIFT(Key_Equals),                     Key_6,                                  LSHIFT(Key_Period),                     Key_3,                                  ___,
   ___,                                    RALT(Key_6),                            Key_Slash,                              Key_Comma,                              Key_Period,                             LSHIFT(Key_M),                          ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___),

  [NUMROW] =  KEYMAP_STACKED
  (___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    Key_F1,                                 Key_F2,                                 Key_F3,                                 Key_F4,                                 Key_F5,                                 ___,
   M(MACRO_CTRL_G),                        LSHIFT(Key_1),                          LSHIFT(Key_2),                          LSHIFT(Key_3),                          LSHIFT(Key_4),                          LSHIFT(Key_5),
   ___,                                    Key_F11,                                Key_F12,                                Key_F13,                                Key_F14,                                Key_F15,                                ___,
   ___,                                    Key_Backspace,                          ___,                                    ___,
   ___,

   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    Key_F6,                                 Key_F7,                                 Key_F8,                                 Key_F9,                                 Key_F10,                                Key_F11,
                                           LSHIFT(Key_6),                          LSHIFT(Key_7),                          LSHIFT(Key_8),                          LSHIFT(Key_9),                          LSHIFT(Key_0),                          ___,
   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (M(MACRO_CTRL_M),                        Key_F1,                                 Key_F2,                                 Key_F3,                                 Key_F4,                                 Key_F5,                                 LCTRL(Key_Delete),
   M(MACRO_CTRL_N),                        M(MACRO_CTRL_S),                        M(MACRO_CTRL_T),                        M(MACRO_CTRL_L),                        M(MACRO_CTRL_Z),                        M(MACRO_CLOSE),                         LCTRL(Key_Tab),
   M(MACRO_CTRL_P),                        M(MACRO_CTRL_W),                        M(MACRO_CTRL_X),                        M(MACRO_CTRL_C),                        M(MACRO_CTRL_V),                        M(MACRO_CTRL_F),
   LCTRL(Key_KeypadDivide),                M(MACRO_PREVIOUS_HISTORY),              M(MACRO_CTRL_R),                        M(MACRO_CTRL_H),                        M(MACRO_NEXT_HISTORY),                  M(MACRO_CTRL_B),                        LCTRL(Key_Enter),
   Key_LeftShift,                          OSL(FUNCTION_VARIANT),                  LCTRL(Key_Enter),                       Key_LeftControl,
   ___,

   Key_F12,                                Key_F6,                                 Key_F7,                                 Key_F8,                                 Key_F9,                                 Key_F10,                                Key_F11,
   ___,                                    LCTRL(Key_Backspace),                   Key_Backspace,                          Key_PageDown,                           Key_PageUp,                             Key_Delete,                             LCTRL(Key_Delete),
                                           Key_Home,                               Key_LeftArrow,                          Key_DownArrow,                          Key_UpArrow,                            Key_RightArrow,                         Key_End,
   LCTRL(Key_Insert),                      LCTRL(Key_Home),                        LCTRL(Key_LeftArrow),                   LALT(Key_DownArrow),                    LALT(Key_UpArrow),                      LCTRL(Key_RightArrow),                  LCTRL(Key_End),
   ___,                                    ___,                                    LCTRL(Key_Space),                       ___,
   LALT(LSHIFT(Key_1))),

  [FUNCTION_VARIANT] =  KEYMAP_STACKED
  (___,                                    LCTRL(Key_F1),                          LCTRL(Key_F2),                          LCTRL(Key_F3),                          LCTRL(Key_F4),                          LCTRL(Key_F5),                          Key_Delete,
   M(MACRO_CTRL_O),                        ___,                                    M(MACRO_CTRL_SHIFT_F10),                M(MACRO_CTRL_K),                        LCTRL(Key_F4),                          M(MACRO_CTRL_A),                        ___,
   M(MACRO_CTRL_D),                        M(MACRO_CTRL_Q),                        M(MACRO_CTRL_U),                        M(MACRO_CTRL_I),                        M(MACRO_CTRL_E),                        LALT(Key_F7),
   ___,                                    M(MACRO_ESCAPE_ALT_F12_CTRL_P),         ___,                                    M(MACRO_CTRL_J),                        M(MACRO_CTRL_Y),                        ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___,

   LCTRL(Key_F12),                        LCTRL(Key_F6),                           LCTRL(Key_F7),                          LCTRL(Key_F8),                          LCTRL(Key_F8),                          LCTRL(Key_F10),                         LCTRL(Key_F11),
   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
                                           ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___),

  [NAV] =  KEYMAP_STACKED
  (___,                                    LALT(Key_F1),                           LALT(Key_F2),                           LALT(Key_F3),                           LALT(Key_F4),                           LALT(Key_F5),                           ___,
   ___,                                    M(MACRO_CLOSE),                         ___,                                    M(MACRO_ALT_SPACE),                     ___,                                    ___,                                    ___,
   ___,                                    Key_LeftArrow,                          Key_DownArrow,                          Key_UpArrow,                            Key_RightArrow,                         LALT(Key_F7),
   ___,                                    LALT(Key_LeftArrow),                    ___,                                    ___,                                    LALT(Key_RightArrow),                   ___,                                    ___,
   ___,                                    ___,                                    ___,                                    ___,
   ___,

   LALT(Key_F12),                          LALT(Key_F6),                           LALT(Key_F7),                           LALT(Key_F8),                           LALT(Key_F9),                           LALT(Key_F10),                          LALT(Key_F11),
   ___,                                    LCTRL(Key_Backspace),                   Key_Backspace,                          Key_PageDown,                           Key_PageUp,                             Key_Delete,                             LCTRL(Key_Delete),
                                           Key_Home,                               Key_LeftArrow,                          Key_DownArrow,                          Key_UpArrow,                            Key_RightArrow,                         Key_End,
   LCTRL(Key_Insert),                      LCTRL(Key_Home),                        LCTRL(Key_LeftArrow),                   LALT(Key_DownArrow),                    LALT(Key_UpArrow),                      LCTRL(Key_RightArrow),                  LCTRL(Key_End),
   ___,                                    ___,                                    Key_Space,                              ___,
   ___)

) // KEYMAPS(

// ShiftBlocker

namespace kaleidoscope {
namespace plugin {

// When activated, this plugin will suppress any `Shift` key (including modifier
// combos with `Shift`) before it's added to the HID report.
class ShiftBlocker : public Plugin {

 public:
  EventHandlerResult onAddToReport(Key key) {
    if (active_ && key.isKeyboardShift())
      return EventHandlerResult::ABORT;
    return EventHandlerResult::OK;
  }

  void enable() {
    active_ = true;
  }
  void disable() {
    active_ = false;
  }

 private:
  bool active_{false};

};

} // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::ShiftBlocker ShiftBlocker;

 bool isShiftKeyHeld() {
   for (Key key : kaleidoscope::live_keys.all()) {
     if (key.isKeyboardShift())
       return true;
   }
   return false;
 }

//
/* Re-enable astyle's indent enforcement */
// clang-format on

#define RGB_UNSET CRGB(0x00, 0x00, 0x00)
#define RGB_RED   CRGB(0xff, 0x00, 0x00)

// Set up a default palette to be use for the Colormap and Colormap-Overlay
// plugins
PALETTE(
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_UNSET,
  RGB_RED)  // PALETTE(

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 100 - Firmware version "));
    Macros.type(PSTR(KALEIDOSCOPE_FIRMWARE_VERSION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */


const macro_t  *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_A_CIRCUMFLEX:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(LeftBracket)));
        ShiftBlocker.disable();
        return MACRO(T(Q));
      } else {
        return MACRO(T(LeftBracket), T(Q));
      }
    }
    break;

  case MACRO_A_GRAVE:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(CapsLock), T(0), T(CapsLock)));
        ShiftBlocker.disable();
      } else {
        return MACRO(T(0));
      }
    }
    break;

  case MACRO_AT:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Space), U(LeftGui));
      } else {
        return MACRO(D(RightAlt), T(0), U(RightAlt));
      }
    }
    break;

  case MACRO_ALT_SPACE:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Space), U(LeftGui));
      } else {
        return MACRO(D(LeftAlt), T(Space), U(LeftAlt));
      }
    }
    break;

  case MACRO_C_CEDILLA:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(CapsLock), T(9), T(CapsLock)));
        ShiftBlocker.disable();
      } else {
        return MACRO(T(9));
      }
    }
    break;

  case MACRO_CLOSE:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(A), U(LeftGui));
      } else {
        return MACRO(D(LeftAlt), T(F4), U(LeftAlt));
      }
    }
    break;

  case MACRO_CTRL_A:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(A), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(A), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_B:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(B), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(B), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_C:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(C), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(C), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_D:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(D), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(D), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_DOWN:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftControl), T(DownArrow), U(LeftControl));
    }
    break;

  case MACRO_CTRL_E:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(E), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(E), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_ENTER:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Enter), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Enter), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_END:
    if (keyToggledOn(event.state)) {
       if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift)) {
          Macros.play(MACRO(D(LeftShift)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftAlt)) {
        Macros.play(MACRO(D(LeftAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightAlt)) {
        Macros.play(MACRO(D(RightAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftGui) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightGui)) {
        Macros.play(MACRO(D(LeftGui)));
      }
      return MACRO(D(LeftControl), T(End), U(LeftControl));
    }
    break;

  case MACRO_CTRL_F:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(F), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(F), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_G:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(G), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(G), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_H:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(H), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(H), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_I:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(I), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(I), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_INSERT:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Insert), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Insert), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_J:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(J), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(J), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_K:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(K), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(K), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_HOME:
    if (keyToggledOn(event.state)) {
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift)) {
        Macros.play(MACRO(D(LeftShift)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftAlt)) {
        Macros.play(MACRO(D(LeftAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightAlt)) {
        Macros.play(MACRO(D(RightAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftGui) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightGui)) {
        Macros.play(MACRO(D(LeftGui)));
      }
      return MACRO(D(LeftControl), T(Home), U(LeftControl));
    }
    break;

  case MACRO_CTRL_L:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(L), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(L), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_LEFT:
    if (keyToggledOn(event.state)) {
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift)) {
        Macros.play(MACRO(D(LeftShift)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftAlt)) {
        Macros.play(MACRO(D(LeftAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightAlt)) {
        Macros.play(MACRO(D(RightAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftGui) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightGui)) {
        Macros.play(MACRO(D(LeftGui)));
      }
      return MACRO(D(LeftControl), T(LeftArrow), U(LeftControl));
    }
    break;

  case MACRO_CTRL_M:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(M), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(M), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_N:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(N), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(N), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_O:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(O), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(O), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_P:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(P), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(P), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_PAGE_DOWN:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftControl), T(PageDown), U(LeftControl));
    }
    break;

  case MACRO_CTRL_PAGE_UP:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftControl), T(PageUp), U(LeftControl));
    }
    break;

  case MACRO_CTRL_Q:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Q), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Q), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_R:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(R), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(R), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_RIGHT:
    if (keyToggledOn(event.state)) {
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift)) {
        Macros.play(MACRO(D(LeftShift)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftAlt)) {
        Macros.play(MACRO(D(LeftAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightAlt)) {
        Macros.play(MACRO(D(RightAlt)));
      }
      if (Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftGui) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightGui)) {
        Macros.play(MACRO(D(LeftGui)));
      }
      return MACRO(D(LeftControl), T(RightArrow), U(LeftControl));
    }
    break;

  case MACRO_CTRL_S:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(S), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(S), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_SHIFT_F10:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(S), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), D(LeftShift), T(F10), U(LeftShift), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_SPACE:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Space), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Space), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_T:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(T), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(T), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_U:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(U), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(U), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_UP:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftControl), T(UpArrow), U(LeftControl));
    }
    break;

  case MACRO_CTRL_V:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(V), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(V), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_W:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(W), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(W), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_X:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(X), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(X), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_Y:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Y), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Y), U(LeftControl));
      }
    }
    break;

  case MACRO_CTRL_Z:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(Z), U(LeftGui));
      } else {
        return MACRO(D(LeftControl), T(Z), U(LeftControl));
      }
    }
    break;

  case MACRO_E_ACUTE:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(CapsLock), T(2), T(CapsLock)));
        ShiftBlocker.disable();
      } else {
        return MACRO(T(2));
      }
    }
    break;

  case MACRO_E_CIRCUMFLEX:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(LeftBracket)));
        ShiftBlocker.disable();
        return MACRO(T(E));
      } else {
        return MACRO(T(LeftBracket), T(E));
      }
    }
    break;

  case MACRO_E_DIAERESIS:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        return MACRO(T(LeftBracket),  T(E));
      } else {
        Macros.play(MACRO(D(LeftShift), T(LeftBracket), U(LeftShift)));
        ShiftBlocker.enable();
        Macros.play(MACRO(T(E)));
        ShiftBlocker.disable();
      }
    }
    break;

  case MACRO_E_GRAVE:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(CapsLock), T(7), T(CapsLock)));
        ShiftBlocker.disable();
      } else {
        return MACRO(T(7));
      }
    }
    break;

  case MACRO_ESCAPE_ALT_F12_CTRL_P:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(T(Escape), D(LeftAlt), T(F12), U(LeftAlt), D(LeftControl), T(P), U(LeftControl));
      } else {
        return MACRO(T(Escape), D(LeftAlt), T(F12), U(LeftAlt), D(LeftControl), T(P), U(LeftControl));
      }
    }
    break;

  case MACRO_I_CIRCUMFLEX:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(LeftBracket)));
        ShiftBlocker.disable();
        return MACRO(T(I));
      } else {
        return MACRO(T(LeftBracket), T(I));
      }
    }
    break;

  case MACRO_I_DIAERESIS:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        return MACRO(T(LeftBracket),  T(I));
      } else {
        Macros.play(MACRO(D(LeftShift), T(LeftBracket), U(LeftShift)));
        ShiftBlocker.enable();
        Macros.play(MACRO(T(I)));
        ShiftBlocker.disable();
      }
    }
    break;

  case MACRO_MAXIMIZE:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(T(LeftControl), T(Apple_Globe), T(F));
      } else {
        return MACRO(D(LeftGui), T(UpArrow), U(LeftGui));
      }
    }
    break;

  case MACRO_MINIMIZE:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(M), U(LeftGui));
      } else {
        return MACRO(D(LeftGui), T(DownArrow), U(LeftGui));
      }
    }
    break;

  case MACRO_MOVE_LEFT:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftControl), D(Apple_Globe), T(LeftArrow), U(Apple_Globe), U(LeftControl));
      } else {
        return MACRO(D(LeftGui), D(Apple_Globe), T(LeftArrow), U(Apple_Globe), U(LeftGui));
      }
    }
    break;

  case MACRO_MOVE_RIGHT:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftControl), T(RightArrow), U(LeftControl));
      } else {
        return MACRO(D(LeftGui), T(RightArrow), U(LeftGui));
      }
    }
    break;

  case MACRO_NEXT_HISTORY:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(RightArrow), U(LeftGui));
      } else {
        return MACRO(D(LeftAlt), T(RightArrow), U(LeftAlt));
      }
    }
    break;

  case MACRO_O_CIRCUMFLEX:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(LeftBracket)));
        ShiftBlocker.disable();
        return MACRO(T(O));
      } else {
        return MACRO(T(LeftBracket), T(O));
      }
    }
    break;

  case MACRO_PREVIOUS_HISTORY:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        return MACRO(D(LeftGui), T(LeftArrow), U(LeftGui));
      } else {
        return MACRO(D(LeftAlt), T(LeftArrow), U(LeftAlt));
      }
    }
    break;

  case MACRO_PRINT_OS:
    if (keyToggledOn(event.state)) {
      if (HostOS.os() == kaleidoscope::hostos::LINUX) {
        Macros.type(PSTR("Linux"));
      }
      if (HostOS.os() == kaleidoscope::hostos::MACOS) {
        Macros.type(PSTR("MacOs"));
      }
      if (HostOS.os() == kaleidoscope::hostos::WINDOWS) {
        Macros.type(PSTR("Windows"));
      }
      if (HostOS.os() == kaleidoscope::hostos::OTHER) {
        Macros.type(PSTR("Other"));
      }
    }
    break;

  case MACRO_SET_OS_LINUX:
    if (keyToggledOn(event.state)) {
        HostOS.os(kaleidoscope::hostos::LINUX);
        return MACRO(Tr(LockLayer(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY)));
    }
    break;

  case MACRO_SET_OS_MACOS:
    if (keyToggledOn(event.state)) {
        HostOS.os(kaleidoscope::hostos::MACOS);
        return MACRO(Tr(LockLayer(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY)));
    }
    break;

  case MACRO_SET_OS_WINDOWS:
    if (keyToggledOn(event.state)) {
        HostOS.os(kaleidoscope::hostos::WINDOWS);
        return MACRO(Tr(LockLayer(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY)));
    }
    break;


  case MACRO_SHIFT_CTRL_DOWN_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(DownArrow), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_CTRL_END_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(End), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_CTRL_HOME_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(Home), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_CTRL_LEFT_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(LeftArrow), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;


  case MACRO_SHIFT_CTRL_RIGHT_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(RightArrow), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_CTRL_UP_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftControl), T(UpArrow), U(LeftControl), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_DOWN_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(DownArrow), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_END_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(End), U(LeftShift), D(LeftControl), T(X), U(LeftControl), T(Space), T(Space), T(Backspace), T(Backspace));
    }
    break;

  case MACRO_SHIFT_HOME_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(Home), U(LeftShift), D(LeftControl), T(X), U(LeftControl), T(Space), T(Backspace));
    }
    break;

  case MACRO_SHIFT_PERCENT:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(Equals), U(LeftShift));
    }
    break;

  case MACRO_SHIFT_PG_DOWN_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(PageDown), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_PG_UP_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(PageUp), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_UP_CTRL_X:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), T(UpArrow), U(LeftShift), D(LeftControl), T(X), U(LeftControl));
    }
    break;

  case MACRO_SHIFT_SUPER_Z:
    if (keyToggledOn(event.state)) {
      return MACRO(D(LeftShift), D(LeftGui), T(LeftBracket), U(LeftGui), U(LeftShift));
    }
    break;

  case MACRO_U_CIRCUMFLEX:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(LeftBracket)));
        ShiftBlocker.disable();
        return MACRO(T(U));
      } else {
        return MACRO(T(LeftBracket), T(U));
      }
    }
    break;

  case MACRO_U_DIAERESIS:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        return MACRO(T(LeftBracket),  T(U));
      } else {
        Macros.play(MACRO(D(LeftShift), T(LeftBracket), U(LeftShift)));
        ShiftBlocker.enable();
        Macros.play(MACRO(T(U)));
        ShiftBlocker.disable();
      }
    }
    break;

  case MACRO_U_GRAVE:
    if (keyToggledOn(event.state)) {
      if (isShiftKeyHeld()) {
        ShiftBlocker.enable();
        Macros.play(MACRO(T(CapsLock), T(Quote), T(CapsLock)));
        ShiftBlocker.disable();
      } else {
        return MACRO(T(Quote));
      }
    }
    break;

  default:
    break;
  }

  return MACRO_NONE;
}



// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 100.


static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 * Toggles between using the built-in keymap, and the EEPROM-stored one.
 */
static void toggleKeymapSource(uint8_t combo_index) {
  if (Layer.getKey == Layer.getKeyFromPROGMEM) {
    Layer.getKey = EEPROMKeymap.getKey;
  } else {
    Layer.getKey = Layer.getKeyFromPROGMEM;
  }
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}},
                 {.action = toggleKeymapSource,
                  // Left Fn + Prog + Shift
                  .keys = {R3C6, R0C0, R3C7}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables controlling (and saving) the brightness of the LEDs via Focus.
  LEDBrightnessConfig,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  GeminiPR,

  // ----------------------------------------------------------------------
  // LED mode plugins

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed,
  solidOrange,
  solidYellow,
  solidGreen,
  solidBlue,
  solidIndigo,
  solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // The colormap overlay plugin provides a way to set LED colors regardless of
  // the active LED effect. This is used for lighting up the keys assigned in
  // the factory 'numpad' mode
  ColormapOverlay,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // ----------------------------------------------------------------------
  // Miscellaneous plugins

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // CharShift,
  CharShift,

  // ShiftBlocker
  ShiftBlocker,

  // HostOS,
  HostOS,

  // AutoShift
//   AutoShift,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode  //,
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Qukeys
  QUKEYS(
  //  r2c1, r2c2, r2c3, r2c4
  // r2c11, r2c12, r2c13, r2c14
       //kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 1), Key_LeftShift),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 2), Key_LeftGui),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 3), Key_LeftControl),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 4), Key_LeftAlt),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 11), Key_LeftAlt),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 12), Key_LeftControl),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 13), Key_LeftGui),
       //kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 14), Key_LeftShift),

       //kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 1), Key_LeftShift),
       kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 2), Key_LeftGui),
       kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 3), Key_LeftControl),
       kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 4), Key_LeftAlt),
//        kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 11), Key_LeftAlt),
//        kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 12), Key_LeftControl),
//        kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 13), Key_LeftGui),
       //kaleidoscope::plugin::Qukey(NAV, KeyAddr(2, 14), Key_LeftShift),


       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(1, 7), ShiftToLayer(NAV)),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, KeyAddr(1, 7), ShiftToLayer(NAV)),
       kaleidoscope::plugin::Qukey(FUNCTION, KeyAddr(1, 7), ShiftToLayer(FUNCTION_VARIANT)),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 7), Key_LeftAlt),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, KeyAddr(2, 7), Key_LeftAlt),
       kaleidoscope::plugin::Qukey(FUNCTION, KeyAddr(2, 7), Key_LeftAlt),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(1, 8), ShiftToLayer(NUMROW)),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, KeyAddr(1, 8), ShiftToLayer(NUMROW)),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(3, 6), ShiftToLayer(FUNCTION)),
       kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, KeyAddr(3, 6), ShiftToLayer(FUNCTION)) //,
//        kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_LINUX_BEPO_VARIANT_ON_AZERTY, KeyAddr(3, 9), ShiftToLayer(NUMBER_SHORTCUT)),
//        kaleidoscope::plugin::Qukey(PRIMARY_KEYMAP_MACOS_BEPO_VARIANT_ON_AZERTY, KeyAddr(3, 9), ShiftToLayer(NUMBER_SHORTCUT))
  )

  //Qukeys.setHoldTimeout(300);
  //Qukeys.setMaxIntervalForTapRepeat(150);
  Qukeys.setMinimumHoldTime(250);


  //OneShot
  OneShot.setTimeout(1000);

  // CharShift
  CS_KEYS(
    kaleidoscope::plugin::CharShift::KeyPair(Key_Space, Key_8),                     // #define Space_Underscore                             CS(0)
    kaleidoscope::plugin::CharShift::KeyPair(Key_RightBracket, RALT(Key_3)),        // #define Dollar_Hash                                  CS(1)
    kaleidoscope::plugin::CharShift::KeyPair(Key_5, RALT(Key_5)),                   // #define LeftParenthesis_Bracket                      CS(2)
    kaleidoscope::plugin::CharShift::KeyPair(Key_Minus, RALT(Key_Minus)),           // #define RightParenthesis_Bracket                     CS(3)
    kaleidoscope::plugin::CharShift::KeyPair(Key_M, Key_Comma),                     // #define Comma_SemiColon                              CS(4)
    kaleidoscope::plugin::CharShift::KeyPair(LSHIFT(Key_Comma), Key_Period),        // #define Period_Colon                                 CS(5)
    kaleidoscope::plugin::CharShift::KeyPair(Key_4, LSHIFT(Key_M)),                 // #define Apostrophe_QuestionMark                      CS(6)
  );

  //  AutoShift for letter keys and number keys only:
//   AutoShift.setEnabled(AutoShift.letterKeys() | AutoShift.symbolKeys());
//   AutoShift.setTimeout(160);

  // Add colormap overlays for all keys of the numpad. This makes sure that
  // all keys of the numpad light up once the numpad layer is active.
  //
  // The call signature is:
  // kaleidoscope::plugin::Overlay(<layer>, <key_address>, <palette_index>)
  //
  // Key address matrix: https://github.com/keyboardio/Kaleidoscope/blob/master/plugins/Kaleidoscope-Hardware-Keyboardio-Model100/src/kaleidoscope/device/keyboardio/Model100.h#L175-L205
  //
  // (0, 0) (0, 1) (0, 2) (0, 3) (0, 4) (0, 5) (0, 6) | (0, 9) (0, 10) (0, 11) (0, 12) (0, 13) (0, 14) (0, 15)
  // (1, 0) (1, 1) (1, 2) (1, 3) (1, 4) (1, 5) (1, 6) | (1, 9) (1, 10) (1, 11) (1, 12) (1, 13) (1, 14) (1, 15)
  // (2, 0) (2, 1) (2, 2) (2, 3) (2, 4) (2, 5)        |        (2, 10) (2, 11) (2, 12) (2, 13) (2, 14) (2, 15)
  // (3, 0) (3, 1) (3, 2) (3, 3) (3, 4) (3, 5) (2, 6) | (2, 9) (3, 10) (3, 11) (3, 12) (3, 13) (3, 14) (3, 15)
  //                      (0, 7) (1, 7) (2, 7) (3, 7) | (3, 8) (2, 8)  (1, 8)  (0, 8)
  //                                           (3, 6) | (3, 9)
  COLORMAP_OVERLAYS(
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 11), 23),  // 7
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 11), 23),  // 4
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 11), 23),  // 1
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 11), 23),  // 0
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 12), 23),  // 8
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 12), 23),  // 5
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 12), 23),  // 2
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 12), 23),  // period
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 13), 23),  // 9
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 13), 23),  // 6
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 13), 23),  // 3
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 13), 23),  // multiply
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(0, 14), 23),  // substract
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(1, 14), 23),  // add
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(2, 14), 23),  // equals
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 14), 23),  // divide
    kaleidoscope::plugin::Overlay(NUMPAD, KeyAddr(3, 15), 23),  // enter
    )                                                           // COLORMAP_OVERLAYS(

  // Set the hue of the boot greeting effect to something that will result in a
  // nice green color.
  BootGreetingEffect.hue = 85;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = CRGB(255, 0, 0);

  // Set the rainbow effects to be reasonably bright, but low enough
  // to mitigate audible noise in some environments.
  LEDRainbowEffect.brightness(170);
  LEDRainbowWaveEffect.brightness(160);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/plugins/Kaleidoscope-LED-Stalker/README.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for eight layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  EEPROMKeymap.setup(8);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(8);
  DefaultColormap.setup();

  // For Dynamic Macros, we need to reserve storage space for the editable
  // macros. A kilobyte is a reasonable default.
  DynamicMacros.reserve_storage(1024);

  // If there's a default layer set in EEPROM, we should set that as the default
  // here.
  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  // Editable layer names are stored in EEPROM too, and we reserve 16 bytes per
  // layer for them. We need one extra byte per layer for bookkeeping, so we
  // reserve 17 / layer in total.
  LayerNames.reserve_storage(17 * 8);

  // Unless configured otherwise with Chrysalis, we want to make sure that the
  // firmware starts with LED effects off. This avoids over-taxing devices that
  // don't have a lot of power to share with USB devices
  DefaultLEDModeConfig.activateLEDModeIfUnconfigured(&LEDOff);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
