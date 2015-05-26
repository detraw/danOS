#include "stm32f4xx_usart.h"

#include "usart.h"

#define MAX_CMD 256
volatile char received_cmd[MAX_CMD];

static void console_irq_handler(const char c)
{
	static int cnt = 0;
	char s[2];
	s[0] = c;
	s[1] = '\0';

	/* printk("received: %s\n", received_cmd); */

	if (c == '\r') {
		usart_write("\r\n");
		received_cmd[cnt] = '\0';
		if (cnt > 1) {
			if (strcmp(received_cmd, "ps") == 0) {
				usart_write("you want ps?\r\n");
			} else if (strcmp(received_cmd, "help") == 0) {
				usart_write("you want help? looser...\r\n");
			} else if (strcmp(received_cmd, "dump") == 0) {
				void (*c)(void) = (void *)0;
				c();
			} else {
				usart_write("unknown command.\r\n");
			}
		}
		usart_write("# ");
		cnt = 0;
	} else {
		if (cnt < MAX_CMD) {
			usart_write(s);
			received_cmd[cnt++] = c;
		}
	}
}

void init_console(void)
{
	init_usart(USART1, console_irq_handler);
}

void console_open(void)
{

}

void console_write(const char *s)
{
	usart_write(s);
	usart_write("\r");
}

void console_read()
{

}
