/**
  ******************************************************************************
  * @file    stm32f4xx_Init.c 
  * @author  Windy Albert
  * @version V1.0
  * @date    26-August-2015
  * @brief   Initialize the STM32 peripherals
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/******************************************************************************/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief  STM32_Init program.
  * @param  None
  * @retval None
  */
void STM32_Init(void){
    GPIO_InitTypeDef            GPIO_InitStructure;
    NVIC_InitTypeDef            NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_InitStructure;		
	
/******************************************************************************/
/*                         Peripheral Registers Configurations                */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/
	

    /* GPIOA0 TIM2_ETR */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIOA->AFR[0]  |= 0x00000001;											//GPIO_PinAFConfig()
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure the GPIO_LED pin */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		NVIC_SetVectorTable (NVIC_VectTab_FLASH, 0x00004000);
    
		/* Configure TIM2 to use TIM2_CH1_ETR */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		
    TIM_InitStructure.TIM_Period = 0x0FFFF;
    TIM_InitStructure.TIM_Prescaler = 0x00;
    TIM_InitStructure.TIM_ClockDivision = 0x0;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);  // Time base configuration
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0); 
    TIM_SetCounter(TIM2, 0);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //允许定时中断
    TIM_Cmd(TIM2, ENABLE);
	
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
//	
//    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;			/* IN,OUT,AF,AN   */
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		/* 2,10,50,100 	  */
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			/* PP,OD 				  */
//		GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;   /* NOPULL,UP,DOWN */
//				
//    GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	

/******************************************************* \GPIOE Configuration */
	
}
/* End of STM32 configuration ------------------------------------------------*/
