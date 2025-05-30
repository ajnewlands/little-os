#include "interrupts.h"
#include "pic.h"
#include "io.h"

#define FB_GREEN 2
#define FB_DARK_GREY 8

#define INTERRUPTS_DESCRIPTOR_COUNT 256
#define INTERRUPTS_KEYBOARD 33
#define INTERRUPTS_PAGING 14

struct IDTDescriptor idt_descriptors[INTERRUPTS_DESCRIPTOR_COUNT];
struct IDT idt;

void interrupts_init_descriptor(int index, unsigned int address)
{
    idt_descriptors[index].offset_high = (address >> 16) & 0xFFFF; // offset bits 0..15
    idt_descriptors[index].offset_low = (address & 0xFFFF);        // offset bits 16..31

    idt_descriptors[index].segment_selector = 0x08; // The second (code) segment selector in GDT: one segment is 64b.
    idt_descriptors[index].reserved = 0x00;         // Reserved.

    /*
       Bit:     | 31              16 | 15 | 14 13 | 12 | 11     10 9 8   | 7 6 5 | 4 3 2 1 0 |
       Content: | offset high        | P  | DPL   | S  | D and  GateType | 0 0 0 | reserved

        P	If the handler is present in memory or not (1 = present, 0 = not present). Set to 0 for unused interrupts or for Paging.
        DPL	Descriptor Privilige Level, the privilege level the handler can be called from (0, 1, 2, 3).
        S	Storage Segment. Set to 0 for interrupt gates.
        D	Size of gate, (1 = 32 bits, 0 = 16 bits).
    */
    idt_descriptors[index].type_and_attr = (0x01 << 7) |               // P
                                           (0x00 << 6) | (0x00 << 5) | // DPL
                                           0xe;                        // 0b1110=0xE 32-bit interrupt gate
}

void interrupts_install_idt()
{
    interrupts_init_descriptor(INTERRUPTS_KEYBOARD, (unsigned int)interrupt_handler_33);
    interrupts_init_descriptor(INTERRUPTS_PAGING, (unsigned int)interrupt_handler_14);

    idt.address = (int)&idt_descriptors;
    idt.size = sizeof(struct IDTDescriptor) * INTERRUPTS_DESCRIPTOR_COUNT;
    load_idt((int)&idt);

    /*pic_remap(PIC_PIC1_OFFSET, PIC_PIC2_OFFSET);*/
    pic_remap(PIC_1_OFFSET, PIC_2_OFFSET);
}

void interrupt_handler(__attribute__((unused)) cpu_state_s cpu, __attribute__((unused)) unsigned int interrupt, __attribute__((unused)) stack_state_s stack)
{
    // Assuming an 80 character terminal, so print K to the second line (under 'HELLO WORLD') when a key is pressed.
    if (interrupt == INTERRUPT_KEYBOARD)
    {
        fb_write_cell(160, 'K', FB_GREEN, FB_DARK_GREY);
    }
    return;
}