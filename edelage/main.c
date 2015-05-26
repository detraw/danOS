#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "syscalls.h"
#include "task.h"
#include "scheduler.h"
#include "usart.h"
#include "dev.h"
#include "printk.h"
#include "console.h"
#include "init.h"

/* Temp */
#include "file.h"

#include <kernel/interrupt.h>

#include <string.h>


#define GREEN  LED4_PIN
#define ORANGE LED3_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN
#define ALL_LEDS (GREEN | ORANGE | RED | BLUE)

#define LEDS_GPIO_PORT (GPIOD)

struct led_info {
	int led;
	int delay;
	int blinks;
};


struct term {
	unsigned int magic;
	unsigned char buf_len;
	unsigned char tx_len;
	unsigned char rx_len;
	unsigned char reserved;
	char tx_buf[252];
	char rx_buf[252];
} st_term = {
	.magic = 0xdeadf00d,
	.buf_len = 252,
};

void st_puts(char *str, unsigned int len)
{
	memcpy(st_term.tx_buf, str, len);
	st_term.tx_len = len;
}

void st_gets(char *buf, unsigned int len)
{
	memcpy(buf, st_term.rx_buf, len);
}

#if 0
static void tim2_irq(int irq)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		char buf[255];
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);

		/* st_puts("." , 1); */
		if (st_term.rx_len != 0) {
			st_gets(buf, st_term.rx_len);
			st_puts(buf, st_term.rx_len);
			st_term.rx_len = 0;
			GPIO_ResetBits(LEDS_GPIO_PORT, RED);
		}
	}
}
#endif

#if 0
static void setup_timer(void)
{
	TIM_TimeBaseInitTypeDef timerInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	timerInitStructure.TIM_Prescaler = 40000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* enable and setup timer interrupt */
	/* register_irq(TIM2_IRQn+16, tim2_irq); */
}
#endif


static void setup_leds(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable the GPIOD pripheral clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* select which pins to use */
	GPIO_InitStructure.GPIO_Pin   = ALL_LEDS;
	/* set mode to out */
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	/* high clock speed, see stm32f4xx.gpio.h for speeds */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	/* PP = push/pull, OD = open drain */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	/* operating pull-up/pull-down for pins */
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	/* write the data into memory at the address
	 * mapped to GPIO device port D (for leds */
	GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);
}

#if 0
static void flash_led(void)
{
	GPIO_SetBits(LEDS_GPIO_PORT, BLUE);
}
#endif


void *blink_led(void *ptr)
{
	struct led_info *info = (struct led_info *)ptr;
	int blinks = 0;

	while (1) {
		GPIO_ToggleBits(GPIOD, info->led);

		blinks++;
		if ((info->blinks != -1) && (blinks > info->blinks)) {
			break;
		}

		/* write(USART1, "blinking led\r\n"); */
		sleep(info->delay);
	}
	return (void *)0;
}

void *busy_blink(void *ptr)
{
	struct led_info *info = (struct led_info *)ptr;
	int blinks = 0;

	while (1) {
		unsigned int tick = system_ticks + info->delay;
		GPIO_ToggleBits(GPIOD, info->led);

		blinks++;
		if ((info->blinks != -1) && blinks > info->blinks) {
			break;
		}

		/* Busy wait */
		while (system_ticks < tick);
	}
	return (void *)0;
}




static char green_stack[1024];
static char orange_stack[1024];
static char red_stack[1024];
static char blue_stack[1024];
int main(void)
{
	/* int usart_fd; */
	struct led_info red = { RED, 500, 10 };
	struct led_info green = { GREEN, 700, -1 };
	struct led_info orange = { ORANGE, 100, -1 };
	struct led_info blue = { BLUE, 1000, -1 };

	/* init_usart(); */
	init_console();
	init_printk();
	init_scheduler();

	setup_leds();

	new_task("green_led", blink_led, &green, green_stack+sizeof(green_stack), sizeof(green_stack));
	new_task("orange_led", blink_led, &orange, orange_stack+sizeof(orange_stack), sizeof(orange_stack));
	new_task("red_led", blink_led, &red, red_stack+sizeof(red_stack), sizeof(red_stack));
	new_task("blue_led", busy_blink, &blue, blue_stack+sizeof(blue_stack), sizeof(blue_stack));

	/* setup init task, this task will also be the idle task */
	init_start();

	return 0;		/* will never return, hopefully... */
}
