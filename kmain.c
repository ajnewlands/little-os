#include "io.h"
#include "interrupts.h"
#define FB_GREEN 2
#define FB_DARK_GREY 8

/** pic_acknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 *  @param num The number of the interrupt
 */
void pic_acknowledge(int interrupt)
{
	if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT)
	{
		return;
	}

	if (interrupt < PIC2_START_INTERRUPT)
	{
		outb(PIC1_PORT_A, PIC_ACK);
	}
	else
	{
		outb(PIC2_PORT_A, PIC_ACK);
	}
}

int kmain(void)
{
	fb_write_cell(0, 'H', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(2, 'E', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(4, 'L', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(6, 'L', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(8, 'O', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(10, ' ', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(12, 'W', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(14, 'O', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(16, 'R', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(18, 'L', FB_GREEN, FB_DARK_GREY);
	fb_write_cell(20, 'D', FB_GREEN, FB_DARK_GREY);

	fb_move_cursor(0);

	interrupts_install_idt();
	return 0;
}
