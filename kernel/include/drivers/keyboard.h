#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <drivers/io.h>

#define KEY_FLAGS_UP        0
#define KEY_FLAGS_DOWN      1
#define KEY_FLAGS_EXTENDED  2

#define KEY_NONE        0x00
#define KEY_ENTER       '\n'
#define KEY_TAB         '\t'
#define KEY_ESC         0x1B
#define KEY_BACKSPACE   0x08
#define KEY_CTRL        0x81
#define KEY_LSHIFT      0x82
#define KEY_RSHIFT      0x83
#define KEY_PRINTSCREEN 0x84
#define KEY_LALT        0x85
#define KEY_CAPSLOCK    0x86
#define KEY_F1          0x87
#define KEY_F2          0x88
#define KEY_F3          0x89
#define KEY_F4          0x8A
#define KEY_F5          0x8B
#define KEY_F6          0x8C
#define KEY_F7          0x8D
#define KEY_F8          0x8E
#define KEY_F9          0x8F
#define KEY_F10         0x90
#define KEY_NUMLOCK     0x91
#define KEY_SCROLLLOCK  0x92
#define KEY_HOME        0x93
#define KEY_UP          0x94
#define KEY_PAGEUP      0x95
#define KEY_LEFT        0x96
#define KEY_CENTER      0x97
#define KEY_RIGHT       0x98
#define KEY_END         0x99
#define KEY_DOWN        0x9A
#define KEY_PAGEDOWN    0x9B
#define KEY_INS         0x9C
#define KEY_DEL         0x9D
#define KEY_F11         0x9E
#define KEY_F12         0x9F
#define KEY_PAUSE       0xA0

inline bool kbd_is_output_full()
{
    if(inb(0x64) & 0x01)
    {
        return true;
    }
    
    return false;
}

inline bool kbd_is_input_full()
{
    if(inb(0x64) & 0x02)
    {
        return true;
    }
    
    return false;
}


bool kbd_init();
uint8_t kbd_get_key();
bool kbd_set_led(bool caps_lock, bool num_lock, bool scroll_lock);
bool kbd_is_alphabet(uint8_t code);
bool kbd_is_number_or_symbol(uint8_t code);
bool kbd_is_numpad(uint8_t code);
bool kbd_is_shifted(uint8_t code);
void kbd_update_status(uint8_t code);
bool kbd_code_to_ascii(uint8_t code, uint8_t *ascii, uint8_t *flags);

typedef struct kbd_map_entry
{
    uint8_t normal;
    uint8_t combined;
} kbd_map_entry_t;

static uint8_t kbd_normal_map[89] =
{
    KEY_NONE,
    KEY_ESC,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    KEY_BACKSPACE,
    KEY_TAB,
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '\n',
    KEY_CTRL,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '`',
    KEY_LSHIFT,
    '\\',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    KEY_RSHIFT,
    '*',
    KEY_LALT,
    ' ',
    KEY_CAPSLOCK,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_NUMLOCK,
    KEY_SCROLLLOCK,
    KEY_HOME,
    KEY_UP,
    KEY_PAGEUP,
    '-',
    KEY_LEFT,
    KEY_CENTER,
    KEY_RIGHT,
    '+',
    KEY_END,
    KEY_DOWN,
    KEY_PAGEDOWN,
    KEY_INS,
    KEY_DEL,
    KEY_NONE,
    KEY_NONE,
    KEY_NONE,
    KEY_F11,
    KEY_F12       
};

static uint8_t kbd_shifted_map[89] =
{
    KEY_NONE,
    KEY_ESC,
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ')',
    '_',
    '+',
    KEY_BACKSPACE,
    KEY_TAB,
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '{',
    '}',
    '\n',
    KEY_CTRL,
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ':',
    '\"',
    '~',
    KEY_LSHIFT,
    '|',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    '<',
    '>',
    '?',
    KEY_RSHIFT,
    '*',
    KEY_LALT,
    ' ',
    KEY_CAPSLOCK  ,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_NUMLOCK,
    KEY_SCROLLLOCK,
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',
    KEY_NONE,
    KEY_NONE,
    KEY_NONE,
    KEY_F11,
    KEY_F12
};
#endif