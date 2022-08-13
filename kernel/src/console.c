#include <console.h>

volatile uint16_t *vga = (uint16_t*) 0xB8000;
static uint32_t x = 0, y = 0;
static uint8_t color = 0x0F;
static int8_t *itoa_buffer[32];

void printf(int8_t *str, ...)
{
    va_list args;
    va_start(args, str);

    for(int i=0; str[i] != '\0'; i++)
    {
        if(str[i] == '%')
        {
            switch(str[i + 1])
            {
                case 'd':
                case 'i':
                case 'u':
                case 'o':
                case 'x':
                case 'X':
                    int32_t si = va_arg(args, int32_t), j = 0;
                    uint32_t ui = (uint32_t) si;

                    if(si == 0)
                    {
                        putchar('0');
                        i ++;
                        break;
                    }

                    if(str[i+1] == 'd' || str[i+1] == 'i')
                    {
                        if(si < 0)
                        {
                            putchar('-');
                            si *= -1;
                        }

                        while(si != 0)
                        {
                            itoa_buffer[j] = '0' + (si % 10);
                            si /= 10;
                            j ++;
                        }
                    }
                    else
                    {
                        if(str[i+1] == 'u')
                        {
                            while(ui != 0)
                            {
                                itoa_buffer[j] = '0' + (ui % 10);
                                ui /= 10;
                                j ++;
                            }
                        }
                        else if(str[i+1] == 'o')
                        {
                            while(ui != 0)
                            {
                                itoa_buffer[j] = '0' + (ui % 8);
                                ui /= 8;
                                j ++;
                            }
                        }
                        else if(str[i+1] == 'x')
                        {
                            while(ui != 0)
                            {
                                int x = (ui % 16);
                                itoa_buffer[j] = (x < 10) ? ('0' + x) : ('a' + (x - 10));
                                ui /= 16;
                                j ++;
                            }
                        }
                        else if(str[i+1] == 'X')
                        {
                            while(ui != 0)
                            {
                                int x = (ui % 16);
                                itoa_buffer[j] = (x < 10) ? ('0' + x) : ('A' + (x - 10));
                                ui /= 16;
                                j ++;
                            }
                        }
                    }

                    do
                    {
                        j --;
                        putchar(itoa_buffer[j]);
                    } while(j >= 0);

                    i ++;
                    break;                
                case 'c':
                    int c = va_arg(args, int);
                    putchar(c);
                    i ++;
                    break;

                case 's':
                    const char *s = va_arg(args, const char*);
                    for(int j=0; s[j] != '\0'; j++)
                        putchar(s[j]);
                    i ++;
                    break;

                case '%':
                    putchar('%');
                    i ++;
                    break;
            }
        }
        else
        {
            putchar(str[i]);
        }
    }
}

void putchar(uint8_t c)
{
    if(c == '\r')
    {
        x = 0;

        return;
    }
    else if(c == '\n')
    {
        y ++;

        if(y >= CONSOLE_HEIGHT)
        {
            scroll();
        }

        return;
    }

    vga[y * CONSOLE_WIDTH + x] = c | (color << 8);
    x ++;

    if(x >= CONSOLE_WIDTH)
    {
        x = 0;
        y ++;

        if(y >= CONSOLE_HEIGHT)
        {
            scroll();
        }
    }
}

void putstr(uint8_t *str)
{
    for(int i=0; str[i] != '\0'; i++)
    {
        putchar(str[i]);
    }
}

void set_color(uint8_t _color)
{
    color = _color;
}

uint8_t get_color()
{
    return color;
}

void clear_console()
{
    for(uint32_t i=0; i<CONSOLE_WIDTH*CONSOLE_HEIGHT; i++)
    {
        vga[i] = ' ' | (color << 8);
    }
}

void scroll()
{

}