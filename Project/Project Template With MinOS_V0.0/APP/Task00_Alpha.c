/**
  ******************************************************************************
  * @author  Windy Albert
  * @date    08-April-2017
  * @brief   Task to ...
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_app.h"
#include "minos.h"																	 /* Header file for MinOS */


/* Private functions ---------------------------------------------------------*/



/**
  * @function  	None
  * @RunPeriod 	None
	*/

void Task00(void *p_arg)
{
	/* Tast Init stuff */
	
	for(;;) {
		//TODO:
		
		RED_OFF;
		//GREEN_ON;
		OSTimeDly(1000);
		RED_ON;
		//GREEN_OFF;		
		OSTimeDly(1000);
	}//for
}


/******************* (C) COPYRIGHT 2017 Windy Albert ***********END OF FILE****/
