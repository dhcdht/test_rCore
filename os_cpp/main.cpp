
#include "sbi.h"
#include "console.h"


extern "C"
{

void cpp_main()
{
    console::puts("Hello rCore-Tutorial!");

    sbi::shutdown();
}

asm(
".include \"entry.asm\""
);

}
