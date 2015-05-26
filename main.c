#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include <kernel/interrupt.h>

#include <string.h>

#define GREEN  LED4_PIN
#define ORANGE LED3_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN
#define ALL_LEDS (GREEN | ORANGE | RED | BLUE)

#define LEDS_GPIO_PORT (GPIOD)

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
	.buf_len = 255,
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
#if 0
			switch (st_term.rx_len) {
			case 1:
				st_puts("1: ", 3);
				break;
			case 2:
				st_puts("2: ", 3);
				break;
			case 3:
				st_puts("3: ", 3);
				break;
			case 4:
				st_puts("4: ", 3);
				break;
			case 5:
				st_puts("5: ", 3);
				break;
			default:
				st_puts("more: ", 6);
				break;
			};
			switch (st_term.rx_buf[0]) {
			case 97:
				st_puts("a\n", 2);
				break;
			default:
				st_puts("else\n", 5);
				break;
			};
#endif
			st_term.rx_len = 0;
			GPIO_ResetBits(LEDS_GPIO_PORT, RED);
		}
	}
}

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
	register_irq(TIM2_IRQn+16, tim2_irq);
}

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

static void flash_led(void)
{
	GPIO_SetBits(LEDS_GPIO_PORT, BLUE);
	/* GPIO_ResetBits(LEDS_GPIO_PORT, BLUE); */
}

int main(void)
{
	setup_leds();
	setup_timer();
	flash_led();

	st_puts("Hello World\n", 12);

	/* this will cause a hard fault */
#if 0
	__asm (
		"movs r0, #1\n\t"
		"ldm  r0,{r1-r2}\n\t"
		"bx   LR\n\t"
		);
#endif
	/* while(1) { */
	/* 	__asm("nop"); */
	/* } */

	while(1) {
		if (st_term.rx_len != 0) {
			GPIO_SetBits(LEDS_GPIO_PORT, RED);
			/* st_puts("edelage", 7); */
			/* st_puts(st_term.rx_buf, 1); */
			/* st_term.rx_len = 0; */
		}
	}

#if 0
	for (;;) {
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		}
#if 0
		int timer_value = TIM_GetCounter(TIM2);
		if (timer_value == 400) {
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
		} else if (timer_value == 500) {
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
		}
#endif
	}
#endif

	return 0;
}
