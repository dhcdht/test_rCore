//
// Created by 董宏昌 on 2021/3/10.
//

#include "interrupt.h"
#include "../console.h"


namespace interrupt {

asm(
    ".include \"./interrupt/interrupt.asm\""
);

extern "C" {

extern void __interrupt();

}

void init() {

    // 实现 rust stvec::write(__interrupt as usize, stvec::TrapMode::Direct);
    // 参考
    //      https://github.com/rcore-os/riscv/blob/master/src/register/stvec.rs
    //      https://github.com/rust-embedded/riscv/blob/39ff09eefe1bb8fb62ad418b2a4109e90e2e3216/src/register/macros.rs
    // 注册 __interrupt 中断函数
    unsigned long bits = (unsigned long)__interrupt;
    asm volatile ("csrrw a0, %1, %0"
    : "=r" (bits)
    : "i" (0x105)
    );

    console::puts("mod interrupt init");
}

}

