//
// Created by 董宏昌 on 2021/3/9.
//

#ifndef TEST_RCORE_CONTEXT_H
#define TEST_RCORE_CONTEXT_H


// 暂时模拟 https://github.com/rcore-os/riscv
struct Sstatus {
    unsigned long bits;
};


struct Context {
    unsigned long x[32];
    Sstatus sstatus;
    unsigned long sepc;
};


#endif //TEST_RCORE_CONTEXT_H
