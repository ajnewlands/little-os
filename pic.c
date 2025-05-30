#include "io.h"
#include "pic.h"

void pic_remap(int offset1, int offset2)
{
    outb(PIC_1_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4); // starts the initialization sequence (in cascade mode)
    outb(PIC_2_COMMAND, PIC_ICW1_INIT + PIC_ICW1_ICW4);
    outb(PIC_1_DATA, offset1); // ICW2: Master PIC vector offset
    outb(PIC_2_DATA, offset2); // ICW2: Slave PIC vector offset
    outb(PIC_1_DATA, 4);       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    outb(PIC_2_DATA, 2);       // ICW3: tell Slave PIC its cascade identity (0000 0010)

    outb(PIC_1_DATA, PIC_ICW4_8086);
    outb(PIC_2_DATA, PIC_ICW4_8086);

    // Setup Interrupt Mask Register (IMR)
    outb(PIC_1_DATA, 0xFD); // 1111 1101 - Enable IRQ 1 only (keyboard).
    outb(PIC_2_DATA, 0xFF);

    asm("sti"); // Enable interrupts.
}