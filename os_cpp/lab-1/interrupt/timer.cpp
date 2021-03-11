//
// Created by 董宏昌 on 2021/3/9.
//

#include "timer.h"
#include "../sbi.h"
#include "../console.h"


namespace interrupt {
namespace timer {

/*
 * 设置下一次时钟中断
 *
 * 获取当前时间，加上中断间隔，通过 SBI 调用预约下一次中断
 */
void set_next_timeout() {
    /*
     * rust
     * time::read()
     */
    unsigned long time = 0;
    asm volatile ("csrrs %0, %1, a0"
    : "=r" (time)
    : "i" (0xC01)
    );

    /// 时钟中断的间隔，单位是 CPU 指令
    static unsigned long kInterval = 5000000L;

    sbi::set_timer(time + kInterval);
}

void init() {
    /*
     * rust
     * // 开启 STIE，允许时钟中断
     * sie::set_stimer();
     */
    unsigned long bits = 1L << 5;
    asm volatile ("csrrs a0, %1, %0"
        :
        : "r"(bits), "i"(0x104)
    );
    /*
     * rust
     * // 开启 SIE（不是 sie 寄存器），允许内核态被中断打断
     * sstatus::set_sie();
     */
    bits = 1 << 1;
    asm volatile ("csrrs a0, %1, %0"
        :
        : "r"(bits), "i"(0x100)
    );

    // 设置下一次时钟中断
    set_next_timeout();
}

/*
 * 每一次时钟中断时调用
 *
 * 设置下一次时钟中断，同时计数 +1
 */
void tick() {
    set_next_timeout();

    /// 触发时钟中断计数
    static unsigned long kTicks = 0;

    kTicks += 1;
    if (kTicks % 3 == 0) {
        console::puts("tick");
    }
}

}
}

