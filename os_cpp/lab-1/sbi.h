//
// Created by 董宏昌 on 2021/3/8.
//

#ifndef TEST_RCORE_SBI_H
#define TEST_RCORE_SBI_H


namespace sbi {

void console_putchar(char c);
unsigned long console_getchar();
void shutdown();

}


#endif //TEST_RCORE_SBI_H
