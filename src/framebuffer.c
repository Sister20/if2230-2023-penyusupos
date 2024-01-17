#include "lib-header/framebuffer.h"
#include "lib-header/stdtype.h"
#include "lib-header/stdmem.h"
#include "lib-header/portio.h"
void framebuffer_set_cursor(uint8_t r, uint8_t c) {
    // TODO : Implement
    uint8_t pos = r * 80 + c;
    out(CURSOR_PORT_CMD, 0x0E);
    out(CURSOR_PORT_DATA, ((pos >> 8) & 0x00FF));
    out(CURSOR_PORT_CMD, 0x0F);
    out(CURSOR_PORT_DATA, pos & 0x00FF);
}
void framebuffer_write(uint8_t row, uint8_t col, char c, uint8_t fg, uint8_t bg) {
    // TODO : Implement
    
    uint16_t colourBit = (bg << 4) | fg ;
    uint16_t fullBit = (colourBit << 8) | c ;

    // Assign the character 2 byte into the memory
    volatile uint16_t* where = (volatile uint16_t*) MEMORY_FRAMEBUFFER + (row*80 + col) ;
    *where = fullBit;
}
void framebuffer_clear(void) {
    // TODO : Implement
}