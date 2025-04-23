#define FB_GREEN     2
#define FB_DARK_GREY 8

/** fb_write_cell:
*  Writes a character with the given foreground and background to position i
*  in the framebuffer.
*
*  @param i  The location in the framebuffer
*  @param c  The character
*  @param fg The foreground color
*  @param bg The background color
*/
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	char * fb = (char*) 0x000B8000;
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

int kmain(void) {
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
	return 0;
}
