
extern "C"
{

void console_putchar(char c);

void cpp_main()
{
    console_putchar('O');
    console_putchar('K');
    console_putchar('\n');

    while (1)
    {
        /* code */
    }
    
}
 
void console_putchar(char c)
{
    register unsigned long a0 asm ("a0") = (unsigned long)c;
    register unsigned long a1 asm ("a1") = (unsigned long)0;
    register unsigned long a2 asm ("a2") = (unsigned long)0;
    register unsigned long a7 asm ("a7") = (unsigned long)1;
    asm volatile ("ecall"
        : "+r" (a0)
        : "r" (a1), "r" (a2), "r" (a7)
        : "memory"
    );
}

asm(
".include \"entry.asm\""
);

}
