#include "stm32f4_discovery.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include <kernel/interrupt.h>

#define GREEN  LED4_PIN
#define ORANGE LED3_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN
#define ALL_LEDS (GREEN | ORANGE | RED | BLUE)

#define LEDS_GPIO_PORT (GPIOD)

static void tim2_irq(int irq)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
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


	/* this will cause a hard fault */
#if 0
	__asm (
		"movs r0, #1\n\t"
		"ldm  r0,{r1-r2}\n\t"
		"bx   LR\n\t"
		);
#endif
	while(1) {
		__asm("nop");
	}

	while(1) {
		flash_led();
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
