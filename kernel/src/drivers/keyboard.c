#include <drivers/keyboard.h>

static bool is_shift_down = false;
static bool is_caps_lock_on = false;
static bool is_num_lock_on = false;
static bool is_scroll_lock_on = false;
static bool is_extended_code = false;
static uint32_t skip_count = 0;

bool kbd_init()
{
    outb(0x64, 0xAE);

    for(int i=0; i<0xFFFF; i++)
    {
        if(kbd_is_input_full() == false)
        {
            break;
        }
    }

    outb(0x60, 0xF4);

    for(int i=0; i<100; i++)
    {
        for(int j=0; j<0xFFFF; j++)
        {
            if(kbd_is_output_full())
            {
                break;
            }
        }

        if(inb(0x60) == 0xFA)
        {
            return true;
        }
    }

    kbd_set_led(false, false, false);

    return false;
}

uint8_t kbd_get_key()
{
    while(kbd_is_output_full() == false);

    return inb(0x60);
}

bool kbd_set_led(bool caps_lock, bool num_lock, bool scroll_lock)
{
    int32_t i, j;

    for(i=0; i<0xFFFF; i++)
    {
        if(kbd_is_input_full() == false)
        {
            break;
        }

        outb(0x60, 0xED);
    }

    for(i=0; i<0xFFFF; i++)
    {
        if(kbd_is_input_full() == false)
        {
            break;
        }
    }

    for(i=0; i<100; i++)
    {
        for(j=0; j<0xFFFF; j++)
        {
            if(kbd_is_output_full() == true)
            {
                break;
            }
        }
        
        if(inb(0x60) == 0xFA)
        {
            break;
        }
    }

    if(i >= 100)
    {
        return false;
    }

    outb(0x60, (caps_lock << 2) | (num_lock << 1) | scroll_lock);

    for(i=0; i<0xFFFF; i++)
    {
        if(kbd_is_input_full() == false)
        {
            break;
        }
    }

    for(i=0; i<100; i++)
    {
        for(j=0; j<0xFFFF; j++)
        {
            if(kbd_is_output_full() == true)
            {
                break;
            }
        }

        if(inb(0x60) == 0xFA)
        {
            break;
        }
    }

    if(i >= 100)
    {
        return false;
    }

    return true;
}

void kbd_update_status(uint8_t code)
{
    bool is_down = false, is_led_changed = false;
    uint8_t down_code = code & 0x7F;

    if(code & 0x80)
    {   
        // key up
        is_down = false;
    }
    else
    {
        // key down
        is_down = true;
    }

    if(down_code == 42 || down_code == 54)
    {
        // shift
        is_shift_down = true;
    }
    else if(down_code == 58 && is_down)
    {
        is_caps_lock_on ^= true;
        is_led_changed = true;
    }
    else if(down_code == 69 && is_down)
    {
        is_num_lock_on ^= true;
        is_led_changed = true;
    }
    else if(down_code == 70 && is_down)
    {
        is_scroll_lock_on ^= true;
        is_led_changed = true;
    }

    if(is_led_changed)
    {
        kbd_set_led(is_caps_lock_on, is_num_lock_on, is_scroll_lock_on);
    }
}

bool kbd_is_alphabet(uint8_t code)
{
    if(kbd_normal_map[code] >= 'a' && kbd_normal_map[code] <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool kbd_is_number_or_symbol(uint8_t code)
{
    if(code >= 2 && code <= 53 && kbd_is_alphabet(code) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool kbd_is_numpad(uint8_t code)
{
    if(code >= 71 && code <= 83)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool kbd_is_shifted(uint8_t code)
{
    uint8_t down_code = code & 0x7F;

    if(kbd_is_alphabet(down_code))
    {
        if(is_shift_down ^ is_caps_lock_on)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(kbd_is_number_or_symbol(down_code))
    {
        if(is_shift_down)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if(kbd_is_numpad(down_code) && !is_extended_code)
    {
        if(is_num_lock_on)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool kbd_code_to_ascii(uint8_t code, uint8_t *ascii, uint8_t *flags)
{
    if(skip_count > 0)
    {
        skip_count --;

        return false;
    }

    if(code == 0xE1)
    {
        // pause pressed
        *ascii = KEY_PAUSE;
        *flags = KEY_FLAGS_DOWN;
        skip_count = 2;

        return false;
    }
    else if(code == 0xE0)
    {
        // is extended code
        is_extended_code = true;

        return false;
    }

    if(kbd_is_shifted(code))
    {
        *ascii = kbd_shifted_map[code & 0x7F];
    }
    else
    {
        *ascii = kbd_normal_map[code & 0x7F];
    }

    if(is_extended_code)
    {
        *flags = KEY_FLAGS_EXTENDED;
        is_extended_code = false;
    }
    else
    {
        *flags = KEY_FLAGS_UP;
    }

    if(code & 0x80 == 0)
    {
        *flags |= KEY_FLAGS_DOWN;
    }

    kbd_update_status(code);

    return true;
}