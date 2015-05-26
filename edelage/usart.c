#include "stm32f4xx_usart.h"

#include "file.h"
#include "dev.h"
#include "console.h"

/* usart interrupt handlers */
#define MAX_STRLEN 128
volatile char received_string[MAX_STRLEN+1];

static void (*irq_handler)(const char);

static void usart_puts(USART_TypeDef *usart, volatile char *s)
{
	while (*s) {
		/* wait for data register to be empty */
		while (!(usart->SR & 0x00000040));

		USART_SendData(usart, *s);
		s++;
	}
}

void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
		/* static uint8_t cnt = 0; */
		char t = USART1->DR; /* data register for usart1 */

		irq_handler(t);
	}
}

static void usart_open(void)
{

}

static void usart_close()
{

}

int usart_write(const char *s)
{
	usart_puts(USART1, (char *)s);

	return 0;
}

static struct file_ops usart_ops = {
	.open = usart_open,
	.close = usart_close,
	.write = usart_write
};

void init_usart(USART_TypeDef *usart, void (*cb)(const char))
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	irq_handler = cb;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* RCC->AHB1ENR |= RCC_AHB1Periph_GPIOB; */
	/* RCC->AHB2ENR |= RCC_APB2Periph_USART1; */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); /* Receive interrupt */

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1, ENABLE);

	register_device(1, "usart1", &usart_ops);
}
