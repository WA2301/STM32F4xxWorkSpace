/*
*********************************************************************************************************
*                                                MinOS
*                                          The Real-Time Kernel
*                                             CORE FUNCTIONS
*
*                              (c) Copyright 2015-2020, ZH, Windy Albert
*                                           All Rights Reserved
*
* File    : MINOS_CFG.h
* By      : Windy Albert & Jean J. Labrosse
* Version : V1.00 [From.V2.86]
*
*********************************************************************************************************
*/

#ifndef OS_CFG_H
#define OS_CFG_H      

#define OS_LOWEST_PRIO            15   /* Defines the lowest priority that can be assigned ...         */
                                       /* ... MUST NEVER be higher than 63 and MUST be >= 1            */
																			 /* App use: 0,1,2....[OS_LOWEST_PRIO-1]												 */

#define OS_Q_EN                   1    /* Enable (1) or Disable (0) code generation for QUEUES         */
#define OS_MAX_QS                 4    /* Max. number of queue control blocks in your application      */


#endif
