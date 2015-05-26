#include "stm32f4xx.h"
#include "printk.h"
#include "task.h"

void dump_stack(int stack[])
{
	printk("r0:  0x%08x  ", stack[0]);
	printk("r1:  0x%08x\n", stack[1]);
	printk("r2:  0x%08x  ", stack[2]);
	printk("r12: 0x%08x\n", stack[3]);
	printk("lr:  0x%08x  ", stack[4]);
	printk("pc:  0x%08x\n", stack[5]);
	printk("psr: 0x%08x\n", stack[6]);
	printk("current task: '%s' stack: 0x%08x\n", current.name, stack);
}

void __attribute (( naked )) HardFault_Handler(void)
{
	asm volatile ("mrs r0, msp\n\t"
		      "bl hardfault_handler_c\n\t");
}

void hardfault_handler_c(int stack[])
{
	printk("HardFault");
	if ((SCB->HFSR & (1 << 30)) != 0) {
		printk (" FORCED (0x%08x)\n", SCB->HFSR);
		if ((SCB->CFSR & SCB_CFSR_USGFAULTSR_Msk) != 0) {
			printk("Usage fault (0x%08x)\n", SCB->CFSR);
		}
		if ((SCB->CFSR & SCB_CFSR_BUSFAULTSR_Msk) != 0) {
			printk("bus fault (0x%08x)\n", SCB->CFSR);
		}
		if ((SCB->CFSR & SCB_CFSR_MEMFAULTSR_Msk) != 0) {
			printk("mem fault (0x%08x)\n", SCB->CFSR);
		}
	}
	if ((SCB->HFSR & (1 << 31)) != 0) {
		printk(" DEBUGEVT (0x%08x)\n", SCB->HFSR);
	}
	if ((SCB->HFSR & (1 << 1)) != 0) {
		printk(" VECTTBL (0x%08x)\n", SCB->HFSR);
	}
	/* _dl_addr(stack); */
	dump_stack(stack);
	asm volatile ("bkpt #01");
	while (1);
}
