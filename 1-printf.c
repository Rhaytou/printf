#include <stdarg.h>
#include "main.h"

typedef struct
{
    int l_modifier;
    int h_modifier;
    int width;
    int precision;
    char conversion;
} params_t;

void init_params(params_t *);
int get_conversion(char, params_t *, va_list);

int my_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    params_t params;
    init_params(&params);
    int sum = 0;

    for (const char *p = format; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            sum++;
            continue;
        }
        p++;
        if (*p == '%')
        {
            putchar('%');
            sum++;
            continue;
        }
        init_params(&params);
        p += get_conversion(*p, &params, ap);
        sum += handle_format(&params, ap);
    }
    va_end(ap);
    return sum;
}

void init_params(params_t *params)
{
    params->l_modifier = 0;
    params->h_modifier = 0;
    params->width = 0;
    params->precision = 0;
    params->conversion = 0;
}

int get_conversion(char c, params_t *params, va_list ap)
{
    switch (c)
    {
    case 'c':
        putchar(va_arg(ap, int));
        return 0;
    case 's':
        puts(va_arg(ap, char *));
        return 0;
    case '%':
        putchar('%');
        return 0;
    default:
        return 0;
    }
}

int handle_format(params_t *params, va_list ap)
{
