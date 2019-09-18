#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "uart.h"

extern int xmodemReceive(unsigned char*, int);

typedef void (*p_func)(void);

void delay(unsigned int t)
{
	volatile uint32_t i, j;
	for(i = 0; i < t; i++)
		for(j = 0; j < 1024; j++);
}

int main(void)
{
    int st;
	volatile int num;
    p_func boot_main=(p_func)(DRAM_BASE);

    // GPIO
	*((volatile uint32_t *)(GPIO_BASE)) = 0xaa;

    // UART 115200 8N1
    uart_init(434);
    uart_puts("PicoRV32 CPU Boot ...\r\n");
    uart_puts("Receive Program by Xmodem in 10s ...\r\n");
    delay(10000);

    st = xmodemReceive((unsigned char *)(DRAM_BASE), 8192);

	*((volatile uint32_t *)(GPIO_BASE)) = 0x55;

    if(st < 0) {
        uart_puts("Xmodem Receive FAIL.\r\n");
    	while(1) {
    		*((volatile uint32_t *)(DRAM_BASE + 0x10)) = 0xaa;
    		num = *((volatile uint32_t *)(DRAM_BASE + 0x10));
    		*((volatile uint32_t *)(GPIO_BASE)) = num;
    		delay(1000);
    		*((volatile uint32_t *)(DRAM_BASE + 0x10)) = 0x55;
    		num = *((volatile uint32_t *)(DRAM_BASE + 0x10));
            *((volatile uint32_t *)(GPIO_BASE)) = num;
    		delay(1000);
    	}
    } else {
        uart_puts("Start from DRAM_BASE ...\r\n");
        boot_main();
    }

	return 0;
}
