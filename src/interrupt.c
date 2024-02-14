#include "lib-header/stdtype.h"
#include "lib-header/interrupt.h"
#include "lib-header/portio.h"
#include "lib-header/keyboard.h"

void io_wait(void){
    out(0x80, 0);
}

void pic_ack(uint8_t irq){
    if(irq >= 8)
		out(PIC2_COMMAND,PIC_ACK);
 
	out(PIC1_COMMAND,PIC_ACK);
}

void pic_remap(void){
    uint8_t a1, a2;
 
	a1 = in(PIC1_DATA);                        // save masks
	a2 = in(PIC2_DATA);
 
	out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	out(PIC1_DATA, PIC1_OFFSET);                 // ICW2: Master PIC vector offset
	io_wait();
	out(PIC2_DATA, PIC2_OFFSET);                 // ICW2: Slave PIC vector offset
	io_wait();
	out(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	out(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	out(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	out(PIC2_DATA, ICW4_8086);
	io_wait();
 
	out(PIC1_DATA, a1);   // restore saved masks.
	out(PIC2_DATA, a2);
}

void main_interrupt_handler(struct CPURegister cpu, uint32_t int_number, struct InterruptStack info){
    switch(int_number){
        case PAGE_FAULT:
            __asm__("hlt");
            break;
        // case PIC1_OFFSET + IRQ_KEYBOARD:
        //     keyboard_isr();
        //     break;
        // case 0x30:
        //     syscall_kernel(cpu, info);
        //     break;
        default:
            break;
    }
}