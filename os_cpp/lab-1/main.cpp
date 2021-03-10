
#include "sbi.h"
#include "console.h"
//#include "interrupt/context.h"
#include "interrupt/handler.h"


extern "C"
{

void cpp_main()
{
    console::puts("Hello cpp rCore-Tutorial!");

//    int size = sizeof(Context);
//    char str[3];
//    str[2] = '0' + size % 10;
//    size /= 10;
//    str[1] = '0' + size % 10;
//    size /= 10;
//    str[0] = '0' + size % 10;
//    str[3] = '\0';
//    console::puts(str);
    // 初始化各种模块
    interrupt::init();

    asm volatile ("ebreak");

    sbi::shutdown();
}

asm(
".include \"entry.asm\""
);

}
