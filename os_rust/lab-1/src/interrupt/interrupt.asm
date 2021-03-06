
# 我们将会用一个宏来用循环保存寄存器。这是必要的设置
.altmacro
# 寄存器宽度对应的字节数
.set REG_SIZE, 8
# Context 的大小
.set CONTEXT_SIZE, 34

# 宏：将寄存器存到栈上
.macro SAVE reg, offset
    sd \reg, \offset*8(sp)
.endm
.macro SAVE_N n
    SAVE x\n, \n
.endm

# 宏：将寄存器从栈中取出
.macro LOAD reg, offset
    ld \reg, \offset*8(sp)
.endm
.macro LOAD_N n
    LOAD x\n, \n
.endm

    .section .text
    .globl __interrupt
# 进入中断
# 保存 Context 并且进入 Rust 中的中断处理函数 interrupt::handler::handle_interrupt()
__interrupt:
    # 在栈上开辟 Context 所需的空间
    addi sp, sp, -34*8

    # 保存通用寄存器，除了 x0（固定为 0）
    SAVE x1, 1
    # 将原来的 sp（sp 又名 x2）写入 2 位置
    addi x1, sp, 34*8
    SAVE x1, 2
    # 保存 x3 至 x31
    .set n, 3
    .rept 29
        SAVE_N %n
        .set n, n+1
    .endr

    # 取出 CSR 并保存
    csrr t0, sstatus
    csrr t1, sepc
    SAVE t0, 32
    SAVE t1, 33

    # 调用 handle_interrupt，传入参数
    # context: &mut Context
    mv a0, sp
    # scause: Scause
    csrr a1, scause
    # stval: usize
    csrr a2, stval
    jal handle_interrupt

    .globl __restore
# 离开中断
# 从 Context 中恢复所有寄存器，并跳转至 Context 中 sepc 的位置
__restore:
    # 恢复 CSR
    LOAD t0, 32
    LOAD t1, 33
    csrw sstatus, t0
    csrw sepc, t1

    # 恢复通用寄存器
    LOAD x1, 1
    # 恢复 x3 至 x31
    .set n, 3
    .rept 29
        LOAD_N %n
        .set n, n + 1
    .endr

    # 恢复 sp（又名 x2）这里最后恢复是为了上面可以正常使用 LOAD 宏
    LOAD x2, 2
    sret
