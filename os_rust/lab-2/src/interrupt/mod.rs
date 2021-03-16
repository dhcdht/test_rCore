
//! 中断模块
//!
//!

mod handler;
mod context;
mod timer;

/// 初始化中断相关的子模块
///
/// - [`handler::init`]
/// - [`timer::init`]
pub fn init() {
    handler::init();
    timer::init();
    println!("mod interrupt initialized");
}

pub fn test() {
    println!("Mod interrupt test start");

    unsafe {
        llvm_asm!("ebreak"::::"volatile");
    };

    println!("Mod interrupt test passed");
}
