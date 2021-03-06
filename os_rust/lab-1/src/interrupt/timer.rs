
//! 预约和处理时钟中断

use crate::sbi::set_timer;
use riscv::register::{time, sie, sstatus};

/// 初始化时钟中断
///
/// 开启时钟中断使能，并且预约第一次时钟中断
pub fn init() {
    unsafe {
        // 开启 STIE，允许时钟中断
        sie::set_stimer();
        // = sie::set_stimer();
        // let mut bits: usize = 1 << 5;
        // llvm_asm!("csrw $1, $0"
        //     :
        //     : "r" (bits), "i" (0x104)
        // );
        // 开启 SIE（不是 sie 寄存器），允许内核态被中断打断
        sstatus::set_sie();
        // = sstatus::set_sie();
        // bits = 1 << 1;
        // llvm_asm!("csrw $1, $0"
        //     :
        //     : "r" (bits), "i" (0x100)
        // );
    }

    // 设置下一次时钟中断
    set_next_timeout();
}

/// 时钟中断的间隔，单位是 CPU 指令
static INTERVAL: usize = 5000000;
/// 设置下一次时钟中断
///
/// 获取当前时间，加上中断间隔，通过 SBI 调用预约下一次中断
fn set_next_timeout() {
    // let mut time: usize;
    // unsafe {
    //     llvm_asm!("csrr $0, $1"
    //         : "=r" (time)
    //         : "i" (0xC01)
    //         : "volatile"
    //     );
    // }

    set_timer(time::read() + INTERVAL);
    // set_timer(time + INTERVAL);
}

/// 触发时钟中断计数
pub static mut TICKS: usize = 0;
pub fn tick() {
    set_next_timeout();
    unsafe {
        TICKS += 1;
        if TICKS % 3 == 0 {
            println!("{} tick", TICKS);
        }
    }
}
