#include "stm32f4_discovery.h"
#include "misc.h"

extern void _estack;

void __attribute__((weak)) Reset_Handler(void);                 /* Reset Handler */
void __attribute__((weak)) NMI_Handler(void);                   /* NMI Handler */
void __attribute__((weak)) HardFault_Handler(void);             /* Hard Fault Handler */
void __attribute__((weak)) MemManage_Handler(void);             /* MPU Fault Handler */
void __attribute__((weak)) BusFault_Handler(void);              /* Bus Fault Handler */
void __attribute__((weak)) UsageFault_Handler(void);            /* Usage Fault Handler */
void __attribute__((weak)) SVC_Handler(void);                   /* SVCall Handler */
void __attribute__((weak)) DebugMon_Handler(void);              /* Debug Monitor Handler */
void __attribute__((weak)) PendSV_Handler(void);                /* PendSV Handler */
void __attribute__((weak)) SysTick_Handler(void);               /* SysTick Handler */
void __attribute__((weak)) WWDG_IRQHandler(void);               /* Window WatchDog              */
void __attribute__((weak)) PVD_IRQHandler(void);                /* PVD through EXTI Line detection */
void __attribute__((weak)) TAMP_STAMP_IRQHandler(void);         /* Tamper and TimeStamps through the EXTI line */
void __attribute__((weak)) RTC_WKUP_IRQHandler(void);           /* RTC Wakeup through the EXTI line */
void __attribute__((weak)) FLASH_IRQHandler(void);              /* FLASH                        */
void __attribute__((weak)) RCC_IRQHandler(void);                /* RCC                          */
void __attribute__((weak)) EXTI0_IRQHandler(void);              /* EXTI Line0                   */
void __attribute__((weak)) EXTI1_IRQHandler(void);              /* EXTI Line1                   */
void __attribute__((weak)) EXTI2_IRQHandler(void);              /* EXTI Line2                   */
void __attribute__((weak)) EXTI3_IRQHandler(void);              /* EXTI Line3                   */
void __attribute__((weak)) EXTI4_IRQHandler(void);              /* EXTI Line4                   */
void __attribute__((weak)) DMA1_Stream0_IRQHandler(void);       /* DMA1 Stream 0                */
void __attribute__((weak)) DMA1_Stream1_IRQHandler(void);       /* DMA1 Stream 1                */
void __attribute__((weak)) DMA1_Stream2_IRQHandler(void);       /* DMA1 Stream 2                */
void __attribute__((weak)) DMA1_Stream3_IRQHandler(void);       /* DMA1 Stream 3                */
void __attribute__((weak)) DMA1_Stream4_IRQHandler(void);       /* DMA1 Stream 4                */
void __attribute__((weak)) DMA1_Stream5_IRQHandler(void);       /* DMA1 Stream 5                */
void __attribute__((weak)) DMA1_Stream6_IRQHandler(void);       /* DMA1 Stream 6                */
void __attribute__((weak)) ADC_IRQHandler(void);                /* ADC1(void); ADC2 and ADC3s         */
void __attribute__((weak)) CAN1_TX_IRQHandler(void);            /* CAN1 TX                      */
void __attribute__((weak)) CAN1_RX0_IRQHandler(void);           /* CAN1 RX0                     */
void __attribute__((weak)) CAN1_RX1_IRQHandler(void);           /* CAN1 RX1                     */
void __attribute__((weak)) CAN1_SCE_IRQHandler(void);           /* CAN1 SCE                     */
void __attribute__((weak)) EXTI9_5_IRQHandler(void);            /* External Line[9:5]s          */
void __attribute__((weak)) TIM1_BRK_TIM9_IRQHandler(void);      /* TIM1 Break and TIM9          */
void __attribute__((weak)) TIM1_UP_TIM10_IRQHandler(void);      /* TIM1 Update and TIM10        */
void __attribute__((weak)) TIM1_TRG_COM_TIM11_IRQHandler(void); /* TIM1 Trigger and Commutation and TIM11 */
void __attribute__((weak)) TIM1_CC_IRQHandler(void);            /* TIM1 Capture Compare         */
void __attribute__((weak)) TIM2_IRQHandler(void);               /* TIM2                         */
void __attribute__((weak)) TIM3_IRQHandler(void);               /* TIM3                         */
void __attribute__((weak)) TIM4_IRQHandler(void);               /* TIM4                         */
void __attribute__((weak)) I2C1_EV_IRQHandler(void);            /* I2C1 Event                   */
void __attribute__((weak)) I2C1_ER_IRQHandler(void);            /* I2C1 Error                   */
void __attribute__((weak)) I2C2_EV_IRQHandler(void);            /* I2C2 Event                   */
void __attribute__((weak)) I2C2_ER_IRQHandler(void);            /* I2C2 Error                   */
void __attribute__((weak)) SPI1_IRQHandler(void);               /* SPI1                         */
void __attribute__((weak)) SPI2_IRQHandler(void);               /* SPI2                         */
void __attribute__((weak)) USART1_IRQHandler(void);             /* USART1                       */
void __attribute__((weak)) USART2_IRQHandler(void);             /* USART2                       */
void __attribute__((weak)) USART3_IRQHandler(void);             /* USART3                       */
void __attribute__((weak)) EXTI15_10_IRQHandler(void);          /* External Line[15:10]s        */
void __attribute__((weak)) RTC_Alarm_IRQHandler(void);          /* RTC Alarm (A and B) through EXTI Line */
void __attribute__((weak)) OTG_FS_WKUP_IRQHandler(void);        /* USB OTG FS Wakeup through EXTI line */
void __attribute__((weak)) TIM8_BRK_TIM12_IRQHandler(void);     /* TIM8 Break and TIM12         */
void __attribute__((weak)) TIM8_UP_TIM13_IRQHandler(void);      /* TIM8 Update and TIM13        */
void __attribute__((weak)) TIM8_TRG_COM_TIM14_IRQHandler(void); /* TIM8 Trigger and Commutation and TIM14 */
void __attribute__((weak)) TIM8_CC_IRQHandler(void);            /* TIM8 Capture Compare         */
void __attribute__((weak)) DMA1_Stream7_IRQHandler(void);       /* DMA1 Stream7                 */
void __attribute__((weak)) FSMC_IRQHandler(void);               /* FSMC                         */
void __attribute__((weak)) SDIO_IRQHandler(void);               /* SDIO                         */
void __attribute__((weak)) TIM5_IRQHandler(void);               /* TIM5                         */
void __attribute__((weak)) SPI3_IRQHandler(void);               /* SPI3                         */
void __attribute__((weak)) UART4_IRQHandler(void);              /* UART4                        */
void __attribute__((weak)) UART5_IRQHandler(void);              /* UART5                        */
void __attribute__((weak)) TIM6_DAC_IRQHandler(void);           /* TIM6 and DAC1&2 underrun errors */
void __attribute__((weak)) TIM7_IRQHandler(void);               /* TIM7                         */
void __attribute__((weak)) DMA2_Stream0_IRQHandler(void);       /* DMA2 Stream 0                */
void __attribute__((weak)) DMA2_Stream1_IRQHandler(void);       /* DMA2 Stream 1                */
void __attribute__((weak)) DMA2_Stream2_IRQHandler(void);       /* DMA2 Stream 2                */
void __attribute__((weak)) DMA2_Stream3_IRQHandler(void);       /* DMA2 Stream 3                */
void __attribute__((weak)) DMA2_Stream4_IRQHandler(void);       /* DMA2 Stream 4                */
void __attribute__((weak)) ETH_IRQHandler(void);                /* Ethernet                     */
void __attribute__((weak)) ETH_WKUP_IRQHandler(void);           /* Ethernet Wakeup through EXTI line */
void __attribute__((weak)) CAN2_TX_IRQHandler(void);            /* CAN2 TX                      */
void __attribute__((weak)) CAN2_RX0_IRQHandler(void);           /* CAN2 RX0                     */
void __attribute__((weak)) CAN2_RX1_IRQHandler(void);           /* CAN2 RX1                     */
void __attribute__((weak)) CAN2_SCE_IRQHandler(void);           /* CAN2 SCE                     */
void __attribute__((weak)) OTG_FS_IRQHandler(void);             /* USB OTG FS                   */
void __attribute__((weak)) DMA2_Stream5_IRQHandler(void);       /* DMA2 Stream 5                */
void __attribute__((weak)) DMA2_Stream6_IRQHandler(void);       /* DMA2 Stream 6                */
void __attribute__((weak)) DMA2_Stream7_IRQHandler(void);       /* DMA2 Stream 7                */
void __attribute__((weak)) USART6_IRQHandler(void);             /* USART6                       */
void __attribute__((weak)) I2C3_EV_IRQHandler(void);            /* I2C3 event                   */
void __attribute__((weak)) I2C3_ER_IRQHandler(void);            /* I2C3 error                   */
void __attribute__((weak)) OTG_HS_EP1_OUT_IRQHandler(void);     /* USB OTG HS End Point 1 Out   */
void __attribute__((weak)) OTG_HS_EP1_IN_IRQHandler(void);      /* USB OTG HS End Point 1 In    */
void __attribute__((weak)) OTG_HS_WKUP_IRQHandler(void);        /* USB OTG HS Wakeup through EXTI */
void __attribute__((weak)) OTG_HS_IRQHandler(void);             /* USB OTG HS                   */
void __attribute__((weak)) DCMI_IRQHandler(void);               /* DCMI                         */
void __attribute__((weak)) CRYP_IRQHandler(void);               /* CRYP crypto                  */
void __attribute__((weak)) HASH_RNG_IRQHandler(void);           /* Hash and Rng                 */
void __attribute__((weak)) FPU_IRQHandler(void);                /* FPU                          */

__attribute__ ((section(".isr_vector")))
void (* const isr_vector[])(void) = {
	&_estack,                         /* The initial stack pointer    */
	Reset_Handler,                    /* The reset handler            */
	NMI_Handler,                      /* The NMI handler              */
	HardFault_Handler,                /* The hard fault handler       */
	MemManage_Handler,                /* The MPU fault handler        */
	BusFault_Handler,                 /* The bus fault handler        */
	UsageFault_Handler,               /* The usage fault handler      */
	0,                                /* Reserved                     */
	0,                                /* Reserved                     */
	0,                                /* Reserved                     */
	0,                                /* Reserved                     */
	SVC_Handler,                      /* SVCall handler               */
	DebugMon_Handler,                 /* Debug monitor handler        */
	0,                                /* Reserved                     */
	PendSV_Handler,                   /* The PendSV handler           */
	SysTick_Handler,                  /* The SysTick handler          */
	/* External Interrupts */
	WWDG_IRQHandler,                  /* Window WatchDog              */
	PVD_IRQHandler,                   /* PVD through EXTI Line detection */
	TAMP_STAMP_IRQHandler,            /* Tamper and TimeStamps through the EXTI line */
	RTC_WKUP_IRQHandler,              /* RTC Wakeup through the EXTI line */
	FLASH_IRQHandler,                 /* FLASH                        */
	RCC_IRQHandler,                   /* RCC                          */
	EXTI0_IRQHandler,                 /* EXTI Line0                   */
	EXTI1_IRQHandler,                 /* EXTI Line1                   */
	EXTI2_IRQHandler,                 /* EXTI Line2                   */
	EXTI3_IRQHandler,                 /* EXTI Line3                   */
	EXTI4_IRQHandler,                 /* EXTI Line4                   */
	DMA1_Stream0_IRQHandler,          /* DMA1 Stream 0                */
	DMA1_Stream1_IRQHandler,          /* DMA1 Stream 1                */
	DMA1_Stream2_IRQHandler,          /* DMA1 Stream 2                */
	DMA1_Stream3_IRQHandler,          /* DMA1 Stream 3                */
	DMA1_Stream4_IRQHandler,          /* DMA1 Stream 4                */
	DMA1_Stream5_IRQHandler,          /* DMA1 Stream 5                */
	DMA1_Stream6_IRQHandler,          /* DMA1 Stream 6                */
	ADC_IRQHandler,                   /* ADC1, ADC2 and ADC3s         */
	CAN1_TX_IRQHandler,               /* CAN1 TX                      */
	CAN1_RX0_IRQHandler,              /* CAN1 RX0                     */
	CAN1_RX1_IRQHandler,              /* CAN1 RX1                     */
	CAN1_SCE_IRQHandler,              /* CAN1 SCE                     */
	EXTI9_5_IRQHandler,               /* External Line[9:5]s          */
	TIM1_BRK_TIM9_IRQHandler,         /* TIM1 Break and TIM9          */
	TIM1_UP_TIM10_IRQHandler,         /* TIM1 Update and TIM10        */
	TIM1_TRG_COM_TIM11_IRQHandler,    /* TIM1 Trigger and Commutation and TIM11 */
	TIM1_CC_IRQHandler,               /* TIM1 Capture Compare         */
	TIM2_IRQHandler,                  /* TIM2                         */
	TIM3_IRQHandler,                  /* TIM3                         */
	TIM4_IRQHandler,                  /* TIM4                         */
	I2C1_EV_IRQHandler,               /* I2C1 Event                   */
	I2C1_ER_IRQHandler,               /* I2C1 Error                   */
	I2C2_EV_IRQHandler,               /* I2C2 Event                   */
	I2C2_ER_IRQHandler,               /* I2C2 Error                   */
	SPI1_IRQHandler,                  /* SPI1                         */
	SPI2_IRQHandler,                  /* SPI2                         */
	USART1_IRQHandler,                /* USART1                       */
	USART2_IRQHandler,                /* USART2                       */
	USART3_IRQHandler,                /* USART3                       */
	EXTI15_10_IRQHandler,             /* External Line[15:10]s        */
	RTC_Alarm_IRQHandler,             /* RTC Alarm (A and B) through EXTI Line */
	OTG_FS_WKUP_IRQHandler,           /* USB OTG FS Wakeup through EXTI line */
	TIM8_BRK_TIM12_IRQHandler,        /* TIM8 Break and TIM12         */
	TIM8_UP_TIM13_IRQHandler,         /* TIM8 Update and TIM13        */
	TIM8_TRG_COM_TIM14_IRQHandler,    /* TIM8 Trigger and Commutation and TIM14 */
	TIM8_CC_IRQHandler,               /* TIM8 Capture Compare         */
	DMA1_Stream7_IRQHandler,          /* DMA1 Stream7                 */
	FSMC_IRQHandler,                  /* FSMC                         */
	SDIO_IRQHandler,                  /* SDIO                         */
	TIM5_IRQHandler,                  /* TIM5                         */
	SPI3_IRQHandler,                  /* SPI3                         */
	UART4_IRQHandler,                 /* UART4                        */
	UART5_IRQHandler,                 /* UART5                        */
	TIM6_DAC_IRQHandler,              /* TIM6 and DAC1&2 underrun errors */
	TIM7_IRQHandler,                  /* TIM7                         */
	DMA2_Stream0_IRQHandler,          /* DMA2 Stream 0                */
	DMA2_Stream1_IRQHandler,          /* DMA2 Stream 1                */
	DMA2_Stream2_IRQHandler,          /* DMA2 Stream 2                */
	DMA2_Stream3_IRQHandler,          /* DMA2 Stream 3                */
	DMA2_Stream4_IRQHandler,          /* DMA2 Stream 4                */
	ETH_IRQHandler,                   /* Ethernet                     */
	ETH_WKUP_IRQHandler,              /* Ethernet Wakeup through EXTI line */
	CAN2_TX_IRQHandler,               /* CAN2 TX                      */
	CAN2_RX0_IRQHandler,              /* CAN2 RX0                     */
	CAN2_RX1_IRQHandler,              /* CAN2 RX1                     */
	CAN2_SCE_IRQHandler,              /* CAN2 SCE                     */
	OTG_FS_IRQHandler,                /* USB OTG FS                   */
	DMA2_Stream5_IRQHandler,          /* DMA2 Stream 5                */
	DMA2_Stream6_IRQHandler,          /* DMA2 Stream 6                */
	DMA2_Stream7_IRQHandler,          /* DMA2 Stream 7                */
	USART6_IRQHandler,                /* USART6                       */
	I2C3_EV_IRQHandler,               /* I2C3 event                   */
	I2C3_ER_IRQHandler,               /* I2C3 error                   */
	OTG_HS_EP1_OUT_IRQHandler,        /* USB OTG HS End Point 1 Out   */
	OTG_HS_EP1_IN_IRQHandler,         /* USB OTG HS End Point 1 In    */
	OTG_HS_WKUP_IRQHandler,           /* USB OTG HS Wakeup through EXTI */
	OTG_HS_IRQHandler,                /* USB OTG HS                   */
	DCMI_IRQHandler,                  /* DCMI                         */
	CRYP_IRQHandler,                  /* CRYP crypto                  */
	HASH_RNG_IRQHandler,              /* Hash and Rng                 */
	FPU_IRQHandler,                   /* FPU                          */
};

/* Here's how to alias multiple functions into single function
 */
static void handle_irq(void);
#pragma weak NMI_Handler                   = handle_irq /* NMI handler                  */
#pragma weak HardFault_Handler             = handle_irq /* Hard Fault handler           */
#pragma weak MemManage_Handler             = handle_irq /* MPU Fault Handler            */
#pragma weak BusFault_Handler              = handle_irq /* Bus Fault Handler            */
#pragma weak UsageFault_Handler            = handle_irq /* Usage Fault Handler          */
#pragma weak SVC_Handler                   = handle_irq /* SVCall Handler               */
#pragma weak DebugMon_Handler              = handle_irq /* Debug Monitor Handler        */
#pragma weak PendSV_Handler                = handle_irq /* PendSV Handler               */
#pragma weak SysTick_Handler               = handle_irq /* SysTick Handler              */
#pragma weak WWDG_IRQHandler               = handle_irq /* Window WatchDog              */
#pragma weak PVD_IRQHandler                = handle_irq /* PVD through EXTI Line detection */
#pragma weak TAMP_STAMP_IRQHandler         = handle_irq /* Tamper and TimeStamps through the EXTI line */
#pragma weak RTC_WKUP_IRQHandler           = handle_irq /* RTC Wakeup through the EXTI line */
#pragma weak FLASH_IRQHandler              = handle_irq /* FLASH                        */
#pragma weak RCC_IRQHandler                = handle_irq /* RCC                          */
#pragma weak EXTI0_IRQHandler              = handle_irq /* EXTI Line0                   */
#pragma weak EXTI1_IRQHandler              = handle_irq /* EXTI Line1                   */
#pragma weak EXTI2_IRQHandler              = handle_irq /* EXTI Line2                   */
#pragma weak EXTI3_IRQHandler              = handle_irq /* EXTI Line3                   */
#pragma weak EXTI4_IRQHandler              = handle_irq /* EXTI Line4                   */
#pragma weak DMA1_Stream0_IRQHandler       = handle_irq /* DMA1 Stream 0                */
#pragma weak DMA1_Stream1_IRQHandler       = handle_irq /* DMA1 Stream 1                */
#pragma weak DMA1_Stream2_IRQHandler       = handle_irq /* DMA1 Stream 2                */
#pragma weak DMA1_Stream3_IRQHandler       = handle_irq /* DMA1 Stream 3                */
#pragma weak DMA1_Stream4_IRQHandler       = handle_irq /* DMA1 Stream 4                */
#pragma weak DMA1_Stream5_IRQHandler       = handle_irq /* DMA1 Stream 5                */
#pragma weak DMA1_Stream6_IRQHandler       = handle_irq /* DMA1 Stream 6                */
#pragma weak ADC_IRQHandler                = handle_irq /* ADC1(void); ADC2 and ADC3s         */
#pragma weak CAN1_TX_IRQHandler            = handle_irq /* CAN1 TX                      */
#pragma weak CAN1_RX0_IRQHandler           = handle_irq /* CAN1 RX0                     */
#pragma weak CAN1_RX1_IRQHandler           = handle_irq /* CAN1 RX1                     */
#pragma weak CAN1_SCE_IRQHandler           = handle_irq /* CAN1 SCE                     */
#pragma weak EXTI9_5_IRQHandler            = handle_irq /* External Line[9:5]s          */
#pragma weak TIM1_BRK_TIM9_IRQHandler      = handle_irq /* TIM1 Break and TIM9          */
#pragma weak TIM1_UP_TIM10_IRQHandler      = handle_irq /* TIM1 Update and TIM10        */
#pragma weak TIM1_TRG_COM_TIM11_IRQHandler = handle_irq /* TIM1 Trigger and Commutation and TIM11 */
#pragma weak TIM1_CC_IRQHandler            = handle_irq /* TIM1 Capture Compare         */
#pragma weak TIM2_IRQHandler               = handle_irq /* TIM2                         */
#pragma weak TIM3_IRQHandler               = handle_irq /* TIM3                         */
#pragma weak TIM4_IRQHandler               = handle_irq /* TIM4                         */
#pragma weak I2C1_EV_IRQHandler            = handle_irq /* I2C1 Event                   */
#pragma weak I2C1_ER_IRQHandler            = handle_irq /* I2C1 Error                   */
#pragma weak I2C2_EV_IRQHandler            = handle_irq /* I2C2 Event                   */
#pragma weak I2C2_ER_IRQHandler            = handle_irq /* I2C2 Error                   */
#pragma weak SPI1_IRQHandler               = handle_irq /* SPI1                         */
#pragma weak SPI2_IRQHandler               = handle_irq /* SPI2                         */
#pragma weak USART1_IRQHandler             = handle_irq /* USART1                       */
#pragma weak USART2_IRQHandler             = handle_irq /* USART2                       */
#pragma weak USART3_IRQHandler             = handle_irq /* USART3                       */
#pragma weak EXTI15_10_IRQHandler          = handle_irq /* External Line[15:10]s        */
#pragma weak RTC_Alarm_IRQHandler          = handle_irq /* RTC Alarm (A and B) through EXTI Line */
#pragma weak OTG_FS_WKUP_IRQHandler        = handle_irq /* USB OTG FS Wakeup through EXTI line */
#pragma weak TIM8_BRK_TIM12_IRQHandler     = handle_irq /* TIM8 Break and TIM12         */
#pragma weak TIM8_UP_TIM13_IRQHandler      = handle_irq /* TIM8 Update and TIM13        */
#pragma weak TIM8_TRG_COM_TIM14_IRQHandler = handle_irq /* TIM8 Trigger and Commutation and TIM14 */
#pragma weak TIM8_CC_IRQHandler            = handle_irq /* TIM8 Capture Compare         */
#pragma weak DMA1_Stream7_IRQHandler       = handle_irq /* DMA1 Stream7                 */
#pragma weak FSMC_IRQHandler               = handle_irq /* FSMC                         */
#pragma weak SDIO_IRQHandler               = handle_irq /* SDIO                         */
#pragma weak TIM5_IRQHandler               = handle_irq /* TIM5                         */
#pragma weak SPI3_IRQHandler               = handle_irq /* SPI3                         */
#pragma weak UART4_IRQHandler              = handle_irq /* UART4                        */
#pragma weak UART5_IRQHandler              = handle_irq /* UART5                        */
#pragma weak TIM6_DAC_IRQHandler           = handle_irq /* TIM6 and DAC1&2 underrun errors */
#pragma weak TIM7_IRQHandler               = handle_irq /* TIM7                         */
#pragma weak DMA2_Stream0_IRQHandler       = handle_irq /* DMA2 Stream 0                */
#pragma weak DMA2_Stream1_IRQHandler       = handle_irq /* DMA2 Stream 1                */
#pragma weak DMA2_Stream2_IRQHandler       = handle_irq /* DMA2 Stream 2                */
#pragma weak DMA2_Stream3_IRQHandler       = handle_irq /* DMA2 Stream 3                */
#pragma weak DMA2_Stream4_IRQHandler       = handle_irq /* DMA2 Stream 4                */
#pragma weak ETH_IRQHandler                = handle_irq /* Ethernet                     */
#pragma weak ETH_WKUP_IRQHandler           = handle_irq /* Ethernet Wakeup through EXTI line */
#pragma weak CAN2_TX_IRQHandler            = handle_irq /* CAN2 TX                      */
#pragma weak CAN2_RX0_IRQHandler           = handle_irq /* CAN2 RX0                     */
#pragma weak CAN2_RX1_IRQHandler           = handle_irq /* CAN2 RX1                     */
#pragma weak CAN2_SCE_IRQHandler           = handle_irq /* CAN2 SCE                     */
#pragma weak OTG_FS_IRQHandler             = handle_irq /* USB OTG FS                   */
#pragma weak DMA2_Stream5_IRQHandler       = handle_irq /* DMA2 Stream 5                */
#pragma weak DMA2_Stream6_IRQHandler       = handle_irq /* DMA2 Stream 6                */
#pragma weak DMA2_Stream7_IRQHandler       = handle_irq /* DMA2 Stream 7                */
#pragma weak USART6_IRQHandler             = handle_irq /* USART6                       */
#pragma weak I2C3_EV_IRQHandler            = handle_irq /* I2C3 event                   */
#pragma weak I2C3_ER_IRQHandler            = handle_irq /* I2C3 error                   */
#pragma weak OTG_HS_EP1_OUT_IRQHandler     = handle_irq /* USB OTG HS End Point 1 Out   */
#pragma weak OTG_HS_EP1_IN_IRQHandler      = handle_irq /* USB OTG HS End Point 1 In    */
#pragma weak OTG_HS_WKUP_IRQHandler        = handle_irq /* USB OTG HS Wakeup through EXTI */
#pragma weak OTG_HS_IRQHandler             = handle_irq /* USB OTG HS                   */
#pragma weak DCMI_IRQHandler               = handle_irq /* DCMI                         */
#pragma weak CRYP_IRQHandler               = handle_irq /* CRYP crypto                  */
#pragma weak HASH_RNG_IRQHandler           = handle_irq /* Hash and Rng                 */
#pragma weak FPU_IRQHandler                = handle_irq /* FPU                          */

void (*irq_handlers[98])(int);	/* TODO: Get define fore # interrupts */

static void handle_irq(void)
{
	int irq = SCB->ICSR & 0x000000ff;

	if (irq_handlers[irq]) {
		(*irq_handlers[irq])(irq);
	}
}

int register_irq(unsigned int irq, void (*handler)(int))
{
	NVIC_InitTypeDef nvicStructure;

	if (irq > 98) {
		return -1;	/* TOOD: add errnos? */
	}

	irq_handlers[irq] = handler;

	nvicStructure.NVIC_IRQChannel = irq - 16;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 1;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	return 0;
}

void unregister_irg(unsigned int irq)
{
	NVIC_InitTypeDef nvicStructure;

	if (irq > 98) {
		return;
	}

	nvicStructure.NVIC_IRQChannel = irq - 16;
	NVIC_Init(&nvicStructure);

	irq_handlers[irq] = 0;
}
