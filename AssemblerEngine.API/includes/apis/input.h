#pragma once

#include <core/types.h>

enum ae_input_source_type
{
	AE_INPUT_MOUSE,
	AE_INPUT_KEYBOARD,
	AE_INPUT_CONTROLLER
};

enum ae_input_event_type
{
    AE_INPUT_MOUSE_BTN,
    AE_INPUT_MOUSE_POS,
    AE_INPUT_MOUSE_SCROLL
    AE_INPUT_KEYBOARD_KEY,
    AE_INPUT_KEYBOARD_TEXT
};

enum ae_input_key_codes
{
    AE_INPUT_KEY_ESCAPE =           0x01,
    AE_INPUT_KEY_1 =                0x02,
    AE_INPUT_KEY_2 =                0x03,
    AE_INPUT_KEY_3 =                0x04,
    AE_INPUT_KEY_4 =                0x05,
    AE_INPUT_KEY_5 =                0x06,
    AE_INPUT_KEY_6 =                0x07,
    AE_INPUT_KEY_7 =                0x08,
    AE_INPUT_KEY_8 =                0x09,
    AE_INPUT_KEY_9 =                0x0A,
    AE_INPUT_KEY_0 =                0x0B,
    AE_INPUT_KEY_MINUS =            0x0C,
    AE_INPUT_KEY_EQUALS =           0x0D,
    AE_INPUT_KEY_BACKSPACE =        0x0E,
    AE_INPUT_KEY_TAB =              0x0F,
    AE_INPUT_KEY_Q =                0x10,
    AE_INPUT_KEY_W =                0x11,
    AE_INPUT_KEY_E =                0x12,
    AE_INPUT_KEY_R =                0x13,
    AE_INPUT_KEY_T =                0x14,
    AE_INPUT_KEY_Y =                0x15,
    AE_INPUT_KEY_U =                0x16,
    AE_INPUT_KEY_I =                0x17,
    AE_INPUT_KEY_O =                0x18,
    AE_INPUT_KEY_P =                0x19,
    AE_INPUT_BRACKET_LEFT =         0x1A,
    AE_INPUT_BRACKET_RIGHT =        0x1B,
    AE_INPUT_ENTER =                0x1C,
    AE_INPUT_CTRL_LEFT =            0x1D,
    AE_INPUT_KEY_A =                0x1E,
    AE_INPUT_KEY_S =                0x1F,
    AE_INPUT_KEY_D =                0x20,
    AE_INPUT_KEY_F =                0x21,
    AE_INPUT_KEY_G =                0x22,
    AE_INPUT_KEY_H =                0x23,
    AE_INPUT_KEY_J =                0x24,
    AE_INPUT_KEY_K =                0x25,
    AE_INPUT_KEY_L =                0x26,
    AE_INPUT_KEY_SEMICOLON =        0x27,
    AE_INPUT_KEY_APOSTROPHE =       0x28,
    AE_INPUT_KEY_GRAVE =            0x29,
    AE_INPUT_KEY_SHIFT_LEFT =       0x2A,
    AE_INPUT_KEY_BACKSLASH =        0x2B,
    AE_INPUT_KEY_Z =                0x2C,
    AE_INPUT_KEY_X =                0x2D,
    AE_INPUT_KEY_C =                0x2E,
    AE_INPUT_KEY_V =                0x2F,
    AE_INPUT_KEY_B =                0x30,
    AE_INPUT_KEY_N =                0x31,
    AE_INPUT_KEY_M =                0x32,
    AE_INPUT_KEY_COMMA =            0x33,
    AE_INPUT_KEY_PERIOD =           0x34,
    AE_INPUT_KEY_SLASH =            0x35,
    AE_INPUT_KEY_SHIFT_RIGHT =      0x36,
    AE_INPUT_KEY_NUMPAD_MULTIPLY =  0x37,
    AE_INPUT_KEY_ALT_LEFT =         0x38,
    AE_INPUT_KEY_SPACE =            0x39,
    AE_INPUT_KEY_CAPSLOCK =         0x3A,
    AE_INPUT_KEY_F1 =               0x3B,
    AE_INPUT_KEY_F2 =               0x3C,
    AE_INPUT_KEY_F3 =               0x3D,
    AE_INPUT_KEY_F4 =               0x3E,
    AE_INPUT_KEY_F5 =               0x3F,
    AE_INPUT_KEY_F6 =               0x40,
    AE_INPUT_KEY_F7 =               0x41,
    AE_INPUT_KEY_F8 =               0x42,
    AE_INPUT_KEY_F9 =               0x43,
    AE_INPUT_KEY_F10 =              0x44,
    AE_INPUT_KEY_NUMLOCK =          0x45,
    AE_INPUT_KEY_SCROLLLOCK =       0x46,
    AE_INPUT_KEY_NUMPAD_7 =         0x47,
    AE_INPUT_KEY_NUMPAD_8 =         0x48,
    AE_INPUT_KEY_NUMPAD_9 =         0x49,
    AE_INPUT_KEY_NUMPAD_MINUS =     0x4A,
    AE_INPUT_KEY_NUMPAD_4 =         0x4B,
    AE_INPUT_KEY_NUMPAD_5 =         0x4C,
    AE_INPUT_KEY_NUMPAD_6 =         0x4D,
    AE_INPUT_KEY_NUMPAD_PLUS =      0x4E,
    AE_INPUT_KEY_NUMPAD_1 =         0x4F,
    AE_INPUT_KEY_NUMPAD_2 =         0x50,
    AE_INPUT_KEY_NUMPAD_3 =         0x51,
    AE_INPUT_KEY_NUMPAD_0 =         0x52,
    AE_INPUT_KEY_NUMPAD_PERIOD =    0x53,
    AE_INPUT_KEY_ALT_PRINTSCREEN =  0x54, // ALT + PRINT SCREEN. MAPVIRTUALKEYEX( VK_SNAPSHOT, MAPVK_VK_TO_VSC_EX, 0 ) RETURNS SCANCODE 0X54.
    AE_INPUT_KEY_BRACKETANGLE =     0x56, // KEY BETWEEN THE LEFT SHIFT AND Z. */
    AE_INPUT_KEY_F11 =              0x57,
    AE_INPUT_KEY_F12 =              0x58,
    AE_INPUT_KEY_OEM_1 =            0x5A, // VK_OEM_WSCTRL 
    AE_INPUT_KEY_OEM_2 =            0x5B, // VK_OEM_FINISH 
    AE_INPUT_KEY_OEM_3 =            0x5C, // VK_OEM_JUMP 
    AE_INPUT_KEY_ERASEEOF =         0x5D,
    AE_INPUT_KEY_OEM_4 =            0x5E, // VK_OEM_BACKTAB
    AE_INPUT_KEY_OEM_5 =            0x5F, // VK_OEM_AUTO
    AE_INPUT_KEY_ZOOM =             0x62,
    AE_INPUT_KEY_HELP =             0x63,
    AE_INPUT_KEY_F13 =              0x64,
    AE_INPUT_KEY_F14 =              0x65,
    AE_INPUT_KEY_F15 =              0x66,
    AE_INPUT_KEY_F16 =              0x67,
    AE_INPUT_KEY_F17 =              0x68,
    AE_INPUT_KEY_F18 =              0x69,
    AE_INPUT_KEY_F19 =              0x6A,
    AE_INPUT_KEY_F20 =              0x6B,
    AE_INPUT_KEY_F21 =              0x6C,
    AE_INPUT_KEY_F22 =              0x6D,
    AE_INPUT_KEY_F23 =              0x6E,
    AE_INPUT_KEY_OEM_6 =            0x6F,   // VK_OEM_PA3
    AE_INPUT_KEY_KATAKANA =         0x70,
    AE_INPUT_KEY_OEM_7 =            0x71,   // VK_OEM_RESET
    AE_INPUT_KEY_F24 =              0x76,
    AE_INPUT_KEY_SBCSCHAR =         0x77,
    AE_INPUT_KEY_CONVERT =          0x79,
    AE_INPUT_KEY_NONCONVERT =       0x7B,   // VK_OEM_PA1

    AE_INPUT_KEY_MEDIA_PREVIOUS =   0xE010,
    AE_INPUT_KEY_MEDIA_NEXT =       0xE019,
    AE_INPUT_KEY_NUMPAD_ENTER =     0xE01C,
    AE_INPUT_KEY_CTRL_RIGHT =       0xE01D,
    AE_INPUT_KEY_VOLUME_MUTE =      0xE020,
    AE_INPUT_KEY_LAUNCH_APP2 =      0xE021,
    AE_INPUT_KEY_MEDIA_PLAY =       0xE022,
    AE_INPUT_KEY_MEDIA_STOP =       0xE024,
    AE_INPUT_KEY_VOLUME_DOWN =      0xE02E,
    AE_INPUT_KEY_VOLUME_UP =        0xE030,
    AE_INPUT_KEY_BROWSER_HOME =     0xE032,
    AE_INPUT_KEY_NUMPAD_DIVIDE =    0xE035,
    AE_INPUT_KEY_PRINTSCREEN =      0xE037, // SC_PRINTSCREEN:
                                            // - MAKE: 0XE02A 0XE037
                                            // - BREAK: 0XE0B7 0XE0AA
                                            // - MAPVIRTUALKEYEX( VK_SNAPSHOT, MAPVK_VK_TO_VSC_EX, 0 ) RETURNS SCANCODE 0X54;
                                            // - THERE IS NO VK_KEYDOWN WITH VK_SNAPSHOT.
    
    AE_INPUT_KEY_ALT_RIGHT =        0xE038,
    AE_INPUT_KEY_CANCEL =           0xE046, // CTRL + PAUSE
    AE_INPUT_KEY_HOME =             0xE047,
    AE_INPUT_KEY_ARROW_UP =         0xE048,
    AE_INPUT_KEY_PAGE_UP =          0xE049,
    AE_INPUT_KEY_ARROW_LEFT =       0xE04B,
    AE_INPUT_KEY_ARROW_RIGHT =      0xE04D,
    AE_INPUT_KEY_END =              0xE04F,
    AE_INPUT_KEY_ARROW_DOWN =       0xE050,
    AE_INPUT_KEY_PAGED_OWN =        0xE051,
    AE_INPUT_KEY_INSERT =           0xE052,
    AE_INPUT_KEY_DELETE =           0xE053,
    AE_INPUT_KEY_META_LEFT =        0xE05B,
    AE_INPUT_KEY_META_RIGHT =       0xE05C,
    AE_INPUT_KEY_APPLICATION =      0xE05D,
    AE_INPUT_KEY_POWER =            0xE05E,
    AE_INPUT_KEY_SLEEP =            0xE05F,
    AE_INPUT_KEY_WAKE =             0xE063,
    AE_INPUT_KEY_BROWSER_SEARCH =   0xE065,
    AE_INPUT_KEY_BROWSER_FAV =      0xE066,
    AE_INPUT_KEY_BROWSER_REFRESH =  0xE067,
    AE_INPUT_KEY_BROWSER_STOP =     0xE068,
    AE_INPUT_KEY_BROWSER_FORWARD =  0xE069,
    AE_INPUT_KEY_BROWSER_BACK =     0xE06A,
    AE_INPUT_KEY_LAUNCH_APP1 =      0xE06B,
    AE_INPUT_KEY_LAUNCH_EMAIL =     0xE06C,
    AE_INPUT_KEY_LAUNCH_MEDIA =     0xE06D,
    AE_INPUT_KEY_PAUSE =            0xE11D45  // sc_pause:
                                              // - make: 0xE11D 45 0xE19D C5
                                              // - make in raw input: 0xE11D 0x45
                                              // - break: none
                                              // - No repeat when you hold the key down
                                              // - There are no break so I don't know how the key down/up is expected to work. Raw input sends "keydown" and "keyup" messages, and it appears that the keyup message is sent directly after the keydown message (you can't hold the key down) so depending on when GetMessage or PeekMessage will return messages, you may get both a keydown and keyup message "at the same time". If you use VK messages most of the time you only get keydown messages, but some times you get keyup messages too.
};

enum ae_input_mouse_codes
{
    AE_INPUT_BUTTON_1,
    AE_INPUT_BUTTON_2,
    AE_INPUT_BUTTON_3,
    AE_INPUT_BUTTON_4,
    AE_INPUT_BUTTON_5,
    AE_INPUT_BUTTON_6,
    AE_INPUT_BUTTON_7,
    AE_INPUT_BUTTON_8,
    AE_INPUT_BUTTON_LEFT = AE_INPUT_BUTTON_1,
    AE_INPUT_BUTTON_RIGHT = AE_INPUT_BUTTON_2,
    AE_INPUT_BUTTON_MIDDLE = AE_INPUT_BUTTON_3
};

enum ae_input_key_states
{
    AE_INPUT_STATE_KEY_DOWN,
    AE_INPUT_STATE_KEY_UP
};

enum ae_input_key_modifiers
{
    AE_INPUT_MOD_SHIFT = (1 << 0),
    AE_INPUT_MOD_CTRL = (1 << 1),
    AE_INPUT_MOD_CAPSLOCK = (1 << 2),
    AE_INPUT_MOD_NUMLOCK = (1 << 3),
    AE_INPUT_MOD_ALT = (1 << 4)
};

struct ae_input_source
{

};

struct ae_input_event
{
    enum ae_input_event_type type;

    char* source_id;

    union
    {
        // keyboard key event
        struct
        {
            enum ae_input_key_codes     key_code;
            enum ae_input_key_states    key_state;
            enum ae_input_key_modifiers key_mod;
        };

        // keyboard text event
        struct
        {
            uint32_t                    unicode;
        };

        // mouse btn event
        struct
        {
            enum ae_input_mouse_codes   button;
        };

        // mouse pos event
        struct
        {
            vec2                        position;
        };
        
        // mouse scroll event
        struct
        {
            vec2                        scroll;
        };

    };
};

struct ae_keyboar_state
{

};

struct ae_input_api
{
    enum ae_input_key_states get_key();
    enum ae_input_key_modifiers get_key_mod();
	void (*poll_events)();
};