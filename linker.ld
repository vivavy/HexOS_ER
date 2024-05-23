ENTRY(_start)

SECTIONS
{
    /* Начало файла по адресу 1МБ (0x100000) */
    . = 1M;

    /* Секция заголовка Multiboot должна быть первой */
    .multiboot :
    {
        KEEP(*(.multiboot))
    }

    /* Секция для кода */
    .text :
    {
        *(.text)
    }

    /* Read-only data */
    .rodata :
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data :
    {
        *(.data)
    }

    /* Read-write data (uninitialized) и стек */
    .bss :
    {
        *(COMMON)
        *(.bss)
    }
}
