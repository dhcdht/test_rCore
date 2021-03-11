//
// Created by 董宏昌 on 2021/3/9.
//

#include "handler.h"
#include "context.h"
#include "../console.h"
#include "timer.h"
#include "../sbi.h"


namespace interrupt {

/*
 * 处理 ebreak 断点
 *
 * 继续执行，其中 `sepc` 增加 2 字节，以跳过当前这条 `ebreak` 指令
 */
void breakpoint(Context &context) {
    console::puts("Interrupted: Breakpoint");
    context.sepc += 2;
}

void supervisor_timer(Context &context) {
    console::puts("Interrupted: supervisor_timer");
    timer::tick();
}

void fault(Context &context, unsigned long scause, unsigned long stval) {
    console::puts("Interrupted: fault");
    sbi::shutdown();
}

extern "C" {

asm(
    ".include \"./interrupt/interrupt.asm\""
);

/*
 * 中断的处理入口
 *
 * `interrupt.asm` 首先保存寄存器至 Context，其作为参数和 scause 以及 stval 一并传入此函数
 * 具体的中断类型需要根据 scause 来推断，然后分别处理
 */
void handle_interrupt(Context &context, unsigned long scause, unsigned long stval) {
    unsigned long mask = 1L << (sizeof(unsigned long) * 8 - 1);
    /*
     * 判断是 exception 还是 interrupt
     * 参考 https://github.com/rcore-os/riscv/blob/master/src/register/scause.rs#L106
     */
    // exception
    if ((scause&mask) == 0) {
//        char str[3];
//        str[0] = '0' + scause;
//        str[1] = '0';
//        str[2] = '\0';
//        console::puts(str);

        switch (scause) {
            // 断点中断（ebreak）
            case 3: {
                breakpoint(context);
            } break;

            // 其他情况，终止当前线程
            default: {
                fault(context, scause, stval);
            } break;
        }
    }
    // interrupt
    else {
        unsigned long scause_code = scause&!mask;

//        char str[3];
//        str[0] = '0' + scause_code;
//        str[1] = '1';
//        str[2] = '\0';
//        console::puts(str);

        switch (scause_code) {
            /*
             * todo: 这里中断类型有问题
             * 目前是 case 0：，根据 https://github.com/rcore-os/riscv/blob/master/src/register/scause.rs#L22
             * 解释为 Interrupt UserSoft 0
             * 实际期望是 Interrupt SupervisorTimer 5
             */
            case 0:
            // 时钟中断
            case 5: {
                supervisor_timer(context);
            } break;

            // 其他情况，终止当前线程
            default: {
                fault(context, scause, stval);
            } break;
        }
    }
}

}

}

