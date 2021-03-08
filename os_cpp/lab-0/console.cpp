//
// Created by 董宏昌 on 2021/3/8.
//

#include "console.h"
#include "sbi.h"


namespace console
{

void puts(const char *str)
{
    do {
        sbi::console_putchar(*str);
        ++str;
    } while (*str != '\0');
    sbi::console_putchar('\n');
}

}

