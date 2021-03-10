//
// Created by 董宏昌 on 2021/3/8.
//

#include "sbi.h"


namespace sbi {

enum call_enum {
    sbi_set_timer = 0,
    sbi_console_putchar,
    sbi_console_getchar,
    sbi_clear_ipi,
    sbi_send_ipi,
    sbi_remote_fence_i,
    sbi_remote_sfence_vma,
    sbi_remote_sfence_vma_asid,
    sbi_shutdown,
};

unsigned long sbi_call(call_enum which, unsigned long arg0 = 0, unsigned long arg1 = 0, unsigned long arg2 = 0) {
    register unsigned long ret asm ("a0") = 0;
    register unsigned long a7 asm ("a7") = which;
    register unsigned long a0 asm ("a0") = arg0;
    register unsigned long a1 asm ("a1") = arg1;
    register unsigned long a2 asm ("a2") = arg2;
    asm volatile ("ecall"
    : "+r" (ret)
    : "r" (a0), "r" (a1), "r" (a2), "r" (a7)
    : "memory"
    );

    return ret;
}

void console_putchar(char c) {
    sbi_call(call_enum::sbi_console_putchar, c);
}

unsigned long console_getchar() {
    return sbi_call(call_enum::sbi_console_getchar);
}

void shutdown() {
    sbi_call(call_enum::sbi_shutdown);
}

}
