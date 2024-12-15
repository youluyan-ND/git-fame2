/*-----------------------------------------------------------------------
|                            FILE DESCRIPTION                           |
-----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
  - File name     : init.c
  - Author        : zeweni
  - Update date   : 2020.01.11
  -	Copyright(C)  : 2020-2021 zeweni. All rights reserved.
-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
|                               INCLUDES                                |
-----------------------------------------------------------------------*/
#include "main.h"
/*-----------------------------------------------------------------------
|                                 DATA                                  |
-----------------------------------------------------------------------*/

/*--------------------------------------------------------
| @Description: MCU peripheral initialization function   |
--------------------------------------------------------*/

static void STC8x_SYSCLK_Config(void);
static void STC8x_UART_Config(void);
static void STC8x_GPIO_Config(void);
static void STC8x_TIMER_Config(void);

/*-----------------------------------------------------------------------
|                               FUNCTION                                |
-----------------------------------------------------------------------*/

/**
  * @name    STC8x_System_Init
  * @brief   MCU initialization function
  * @param   None
  * @return  None
***/
void STC8x_System_Init(void)
{
	
	DELAY_POS(); /* Power on stability delay */	
	STC8x_SYSCLK_Config(); /* Initialize system clock */
    NVIC_GLOBAL_ENABLE();	
    delay_init();
	
	STC8x_GPIO_Config();
	STC8x_UART_Config();
	STC8x_TIMER_Config();
	
	/*
		Add hardware driver initialization code here.
	*/
	
	
}

/**
  * @name    STC8x_SYSCLK_Config
  * @brief   MCU SYSCLK initialization function
  * @param   None
  * @return  None
***/
static void STC8x_SYSCLK_Config(void)
{
	SYSCLK_InitType SYSCLK_InitStruct={0}; /* Declare structure */

	SYSCLK_InitStruct.MCLKSrc = AUTO;
	// SYSCLK_InitStruct.IRCBand = IRC_Band_20MHz;
	// SYSCLK_InitStruct.IRCTRIM = 150;
    // SYSCLK_InitStruct.LIRCTRIM = TRIM1;
	// SYSCLK_InitStruct.MCLKDiv = 0;
	SYSCLK_InitStruct.SCLKDiv = 0; /* if SCLKDiv = 0, Not output */
	SYSCLK_InitStruct.SCLKOutPin = SCLK_OUT_P16;
	SYSCLK_Init(&SYSCLK_InitStruct);
	
}

/**
  * @name    STC8x_GPIO_Config
  * @brief   MCU GPIO initialization function
  * @param   None
  * @return  None
***/
static void STC8x_GPIO_Config(void)
{
    /* Run lamp */
	GPIO_MODE_OUT_PP(GPIO_P5,Pin_5);  //P55
    P55 = 1;
}

/**
  * @name    STC8x_TIMER_Config
  * @brief   MCU TIMER initialization function
  * @param   None
  * @return  None
***/
static void STC8x_TIMER_Config(void)
{
	TIMER_InitType TIMER_InitStruct={0};
	
	TIMER_InitStruct.Mode = TIMER_16BitAutoReload;
	TIMER_InitStruct.Value = 1000;     //1ms
	TIMER_InitStruct.Run = ENABLE;
	TIMER0_Init(&TIMER_InitStruct);
	NVIC_TIMER0_Init(NVIC_PR0,ENABLE);
}

/**
  * @name    STC8x_UART_Config
  * @brief   MCU UART initialization function
  * @param   None
  * @return  None
***/
static void STC8x_UART_Config(void)
{
	UART_InitType UART_InitStruct = {0};
	
	/* UART1 TXD */
	GPIO_MODE_OUT_PP(GPIO_P3,Pin_1);
	/* UART1 RXD */
	GPIO_MODE_IN_FLOATING(GPIO_P3,Pin_0); 

	UART_InitStruct.Mode = UART_8bit_BRTx;
	UART_InitStruct.BRTGen = UART_BRT_TIM1;
	UART_InitStruct.BRTMode = UART_BRT_1T;
	UART_InitStruct.BaudRate = 115200;
	UART_InitStruct.RxEnable = ENABLE;
	UART1_Init(&UART_InitStruct);
	NVIC_UART1_Init(NVIC_PR0,ENABLE);
}


/*-----------------------------------------------------------------------
|                   END OF FLIE.  (C) COPYRIGHT zeweni                  |
-----------------------------------------------------------------------*/
