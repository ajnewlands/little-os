#ifndef INCLUDE_INTERRUPTS
#define INCLUDE_INTERRUPTS

#define INTERRUPT_KEYBOARD 33

struct IDT
{
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

struct IDTDescriptor
{
    /* The lowest 32 bits */
    unsigned short offset_low;       // offset bits 0..15
    unsigned short segment_selector; // a code segment selector in GDT or LDT

    /* The highest 32 bits */
    unsigned char reserved;      // Just 0.
    unsigned char type_and_attr; // type and attributes
    unsigned short offset_high;  // offset bits 16..31
} __attribute__((packed));

void interrupts_install_idt();

// Wrappers around ASM.
void load_idt(unsigned int idt_address);
void interrupt_handler_33();
void interrupt_handler_14();

struct cpu_state
{
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
} __attribute__((packed));

typedef struct cpu_state cpu_state_s;

struct stack_state
{
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed));
typedef struct stack_state stack_state_s;

void interrupt_handler(__attribute__((unused)) cpu_state_s cpu, unsigned int interrupt, __attribute__((unused)) stack_state_s stack);

#endif /* INCLUDE_INTERRUPTS */