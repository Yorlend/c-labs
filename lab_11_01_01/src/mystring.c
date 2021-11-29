#include "mystring.h"
#include "errors.h"
#include <stdarg.h>


#define MAX_DIG 7

static void push_char(char **s, size_t *n, const char ch)
{
    if (*n != 0)
    {
        if ((*n)-- == 1)
            *(*s)++ = '\0';
        else
            *(*s)++ = ch; 
    }
}

static int push_string(char **s, size_t *n, const char *str)
{
    int parsed = 0;

    while (*str)
    {
        push_char(s, n, *(str++));
        parsed++;
    }

    return parsed;
}

static int push_number(char **s, size_t *n, short num)
{
    int parsed = 0;

    char digs[MAX_DIG] = {[MAX_DIG - 1] = '\0'};
    size_t count = MAX_DIG - 1;

    if (num < 0)
    {
        push_char(s, n, '-');
        num *= -1;
        parsed++;
    }

    do
    {
        digs[--count] = '0' + num % 10;
        num /= 10;
    } while (num != 0);

    parsed += push_string(s, n, &digs[count]);
    
    return parsed;
}

static int parse(char **s, size_t *n, const char **format, va_list *args)
{
    int parsed = 0;

    switch (*(*format)++)
    {
        case 's':
            parsed += push_string(s, n, va_arg(*args, const char *));
            break;

        case 'h':
            if (*(*format)++ == 'i')
                parsed += push_number(s, n, va_arg(*args, int));
            break;
    }
    
    return parsed;
}

static int check_format(const char *format)
{
    int flag = 1;

    while (!flag && *format)
    {
        if (*format == '%')
            flag = (*format == 's')
            || ((*format == 'h' && *format++) && (*format == 'i'));
        format++;
    }

    return flag;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    if (!check_format(format) || (s == NULL && n > 0))
        return ARG_ERR;

    int parsed = 0;
    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%' && *(format++))
            parsed += parse(&s, &n, &format, &args);
        else
        {
            push_char(&s, &n, *(format++));
            parsed++;
        }
    }

    push_char(&s, &n, '\0');

    va_end(args);
    return parsed;
}