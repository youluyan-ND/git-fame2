/*-----------------------------------------------------------------------
|                            FILE DESCRIPTION                           |
-----------------------------------------------------------------------*/
/*----------------------------------------------------------------------
  - File name     : example_mpwm.c
  - Author        : slipperstree
  - Update date   : 2022.07.03
-----------------------------------------------------------------------*/
/*------------------------------------------------------------------------
|                            COPYRIGHT NOTICE                            |
------------------------------------------------------------------------*/
/*
 * Copyright (C) 2022, slipperstree (https://gitee.com/slipperstree)

 * This file is part of 8051 ELL low-layer libraries.

 * 8051 ELL low-layer libraries is free software: you can redistribute 
 * it and/or modify it under the terms of the Apache-2.0 License.

 * 8051 ELL low-layer libraries is distributed in the hope that it will 
 * be useful,but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * Apache-2.0 License for more details.

 * You should have received a copy of the Apache-2.0 License.8051 ELL 
 * low-layer libraries. If not, see <http://www.apache.org/licenses/>.
**/
/*-----------------------------------------------------------------------
|                               INCLUDES                                |
-----------------------------------------------------------------------*/
#include "example_mpwm.h"
#include "ELL_LIB.h"

/*-----------------------------------------------------------------------
|                                 DATA                                  |
-----------------------------------------------------------------------*/
/* None. */
/*-----------------------------------------------------------------------
|                               FUNCTION                                |
-----------------------------------------------------------------------*/

/**
 * @brief      MPWM����ʾ�������ʼ����
 * @details    Example code for MPWM peripherals initialized.
 * @param      None.
 * @return     None.
 * @note       ÿ�����̣�ֻ�ܵ���һ����ʼ�����������к�����������֮�䲢�����ݡ�
 *             Each routine can only call an initialization function and a run function, 
 *             and the routines are not compatible with each other.
**/
void Example_MPWM_Init(void)
{
	GPIO_MODE_OUT_PP(GPIO_P0,Pin_4);
	GPIO_MODE_OUT_PP(GPIO_P0,Pin_5);
	GPIO_MODE_OUT_PP(GPIO_P4,Pin_7);

	/* Init PWM port 0 */
	UART1_Isr_Send_String("Init PWM port 0 \r\n");
	MPWMn_Port_Init(MPWM_Port_0, MPWM_SCLK_DIV_16, 0x1000);	

	/* Init PWM channel P04 */
	UART1_Isr_Send_String("Init PWM channel P04 \r\n");
	MPWMn_Channel_Init(MPWM_Port_0, MPWM_Channel_4, MPWM_Start_Low_Level, 0x0000, 0x0200, ENABLE);

	/* Init PWM channel P05 but output is disabled */
	UART1_Isr_Send_String("Init PWM channel P05 but output is disabled \r\n");
	MPWMn_Channel_Init(MPWM_Port_0, MPWM_Channel_5, MPWM_Start_Low_Level, 0x0000, 0x0500, DISABLE);

	/* Init PWM channel P47 while PWM port 4 hasn't initalized yet */
	UART1_Isr_Send_String("Init PWM channel P47 while PWM port 4 hasn't initalized yet \r\n");
	MPWMn_Channel_Init(MPWM_Port_4, MPWM_Channel_7, MPWM_Start_Low_Level, 0x0100, 0x0500, ENABLE);

	/* Init PWM port 4 */
	UART1_Isr_Send_String("Init PWM port 4 \r\n");
	MPWMn_Port_Init(MPWM_Port_4, MPWM_SCLK_DIV_16, 0x1000);
}


/**
 * @brief      ����MPWM����ʾ�����롣
 * @details    Run the MPWM peripheral sample code.
 * @param      None.
 * @return     None.
 * @note       ÿ�����̣�ֻ�ܵ���һ����ʼ�����������к�����������֮�䲢�����ݡ�
 *             Each routine can only call an initialization function and a run function, 
 *             and the routines are not compatible with each other.
**/
void Example_MPWM_Run(void)
{
	/* Run PWM port 0 */
	/* ���� PWM port 0 */
	MPWMn_Run(MPWM_Port_0);

	/* Run PWM port 4 */
	/* ���� PWM port 4 */
	MPWMn_Run(MPWM_Port_4);

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	// Now, P04 is working. ���� P04�Ѿ������ˣ���Init�������Ѿ���ʼ����P04����OutPut����ΪENABLE��
	//      P05 is not work cause output is disabled P05��û�п�ʼ������Ϊ��Init��P05��OutPut����ΪDisable
	//      P47 is not work cause PORT MUST BE INITALIZED FIRST BEFORE CHANNEL P07Ҳû�й�����ΪPORT������ͨ��֮ǰ��ʼ����˳���ܷ���
	// 

	/* Enable P05 Output by Set Register [PWMnCR]'s bit [ENO[7:7]] to 1 directly ����ͨ�����üĴ����ķ�ʽ��P05��output����Ϊenable */
	/* (Or you can just call MPWMn_Channel_Init() again by pass ENABLE to last param [run]) ��Ҳ�������µ���һ�γ�ʼ������ MPWMn_Channel_Init ������ΪENABLE*/
	EAXFR_ENABLE();
	setBitPWMniEnableOut(MPWM_Port_0, MPWM_Channel_5);
	EAXFR_DISABLE();

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	// 
	// P05 is now working. fine. ����P05��ʼ������
	// 

	/* Like P05, let's try enable P47 Output by Set Register [PWMnCR]'s bit [ENO[7:7]] to 1 directly ��P05һ������ͨ�����üĴ����ķ�ʽ��P47��output����Ϊenable */
	EAXFR_ENABLE();
	setBitPWMniEnableOut(MPWM_Port_4, MPWM_Channel_7);
	EAXFR_DISABLE();

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	//
	// Oh no! P47 is still sleeping cause initalized values(StartLevel/T1/T2) hasn't been affected at all. ��ʱP47��Ȼû�п�ʼ����
	// 

	/* So you need init P47 by call MPWMn_Channel_Init() again ����Ҫ����MPWMn_Channel_Init���³�ʼ��һ��P47 */
	MPWMn_Channel_Init(MPWM_Port_4, MPWM_Channel_7, MPWM_Start_Low_Level, 0x0100, 0x0500, ENABLE);

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	//
	// P47 is running now! P47��������������
	// PORT MUST BE INITALIZED FIRST BEFORE CHANNEL. PORT������ͨ��֮ǰ��ʼ������Ҫ������һ��
	// Don't forget it.
	// 

	/* Stop PWM port 0 ֹͣPORT0��PWM */
	MPWMn_Stop(MPWM_Port_0);

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	//
	// Now, P04/P05 stoped. P04��P05ֹͣ������
	// 
	
	/* Stop PWM port 4 ֹͣPORT4��PWM  */
	UART1_Isr_Send_String("Stop PWM port 4 \r\n");
	MPWMn_Stop(MPWM_Port_4);

	DELAY_Set_Ms(3000);  // Wait a while to see what happening �ȴ�һ��۲�����
	//
	// Now, P47 stoped as well. P47Ҳֹͣ������
	//

	DELAY_Set_Ms(5000);  // Wait a while to see what happening
}

/*-----------------------------------------------------------------------
|                   END OF FLIE.  (C) COPYRIGHT slipperstree            |
-----------------------------------------------------------------------*/



