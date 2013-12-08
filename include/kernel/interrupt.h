#ifndef _KERNEL_INTERRUPT_H
#define _KERNEL_INTERRUPT_H

int register_irq(unsigned int irq, void (*handler)(int));

#endif
