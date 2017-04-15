/*
*********************************************************************************************************
*                                                MinOS
*                                          The Real-Time Kernel
*                                             CORE FUNCTIONS
*
*                              (c) Copyright 2015-2020, ZH, Windy Albert
*                                           All Rights Reserved
*
* File    : MINOS.h
* By      : Windy Albert & Jean J. Labrosse
* Version : V1.00 [From.V2.86]
*
*********************************************************************************************************
*/

#ifndef   _MINOS_H
#define   _MINOS_H

#include <minos_cfg.h>

/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide                    */
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register (PSR = 32 bits) */

/*
*********************************************************************************************************
*                                              Cortex-M1
*                                      Critical Section Management
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define  OS_CRITICAL_METHOD   3

#define  OS_STK_GROWTH        1                   /* Stack grows from HIGH to LOW memory on ARM        */

#if OS_CRITICAL_METHOD == 3                       /* See OS_CPU_A.ASM                                  */
OS_CPU_SR  OS_CPU_SR_Save(void);
void       OS_CPU_SR_Restore(OS_CPU_SR cpu_sr);

#define  OS_ENTER_CRITICAL()  {cpu_sr = OS_CPU_SR_Save();}
#define  OS_EXIT_CRITICAL()   {OS_CPU_SR_Restore(cpu_sr);}

#endif

void       OSCtxSw(void);
void       OSStartHighRdy(void);

/*
*********************************************************************************************************
*                                             MISCELLANEOUS
*********************************************************************************************************
*/

#ifdef   OS_GLOBALS
#define  OS_EXT
#else
#define  OS_EXT  extern
#endif

#define  OS_FALSE                     0u
#define  OS_TRUE                      1u

#define OS_MAX_TASKS  		 OS_LOWEST_PRIO    /* Max. number of tasks in your application, MUST be >= 1 */
#define OS_TASK_IDLE_STK_SIZE    		  80    /* Idle  task stack size (# of OS_STK wide entries)        */

#define  OS_PRIO_SELF              0xFFu                /* Indicate SELF priority                      */
#define  OS_N_SYS_TASKS               1u
#define  OS_TASK_IDLE_PRIO  (OS_LOWEST_PRIO)            /* IDLE      task priority                     */
#define  OS_RDY_TBL_SIZE   ((OS_LOWEST_PRIO) / 8 + 1)   /* Size of ready table                         */

#define  OS_TCB_RESERVED        ((OS_TCB *)1)

/*$PAGE*/
/*
*********************************************************************************************************
*                              TASK STATUS (Bit definition for OSTCBStat)
*********************************************************************************************************
*/
#define  OS_STAT_RDY               0x00u    /* Ready to run                                            */
#define  OS_STAT_PEND_Q            0x04u    /* Pending on queue                                        */
#define  OS_STAT_SUSPEND           0x08u    /* Task is suspended                                       */

#define  OS_STAT_PEND_OK              0u    /* Pending status OK, not pending, or pending complete     */
#define  OS_STAT_PEND_TO              1u    /* Pending timed out                                       */
#define  OS_STAT_PEND_ABORT           2u    /* Pending aborted                                         */


/*
*********************************************************************************************************
*                                             ERROR CODES
*********************************************************************************************************
*/
#define OS_ERR_NONE                   0u
#define OS_ERR_PEND_ISR               2u
#define OS_ERR_TIMEOUT               10u
#define OS_ERR_PEND_ABORT            14u
#define OS_ERR_Q_FULL                30u
#define OS_ERR_Q_EMPTY               31u
#define OS_ERR_PRIO_EXIST            40u
#define OS_ERR_TASK_NO_MORE_TCB      66u
#define OS_ERR_TASK_NOT_EXIST        67u

#define  OS_EVENT_TBL_SIZE ((OS_LOWEST_PRIO) / 8 + 1)   /* Size of event table                         */
/*$PAGE*/
/*
*********************************************************************************************************
*                                          EVENT CONTROL BLOCK
*********************************************************************************************************
*/

#if OS_Q_EN > 0
typedef struct os_event {
    void    *OSEventPtr;                     /* Pointer to message or queue structure                   */
    INT8U    OSEventGrp;                     /* Group corresponding to tasks waiting for event to occur */
    INT8U    OSEventTbl[OS_EVENT_TBL_SIZE];  /* List of tasks waiting for event to occur                */

} OS_EVENT;
#endif


/*$PAGE*/
/*
*********************************************************************************************************
*                                          TASK CONTROL BLOCK
*********************************************************************************************************
*/

typedef struct os_tcb {
    OS_STK          *OSTCBStkPtr;           /* Pointer to current top of stack                         */
    struct os_tcb   *OSTCBNext;             /* Pointer to next     TCB in the TCB list                 */
    struct os_tcb   *OSTCBPrev;             /* Pointer to previous TCB in the TCB list                 */

#if OS_Q_EN > 0
    OS_EVENT        *OSTCBEventPtr;         /* Pointer to          event control block                 */
    void            *OSTCBMsg;              /* Message received from OSMboxPost() or OSQPost()         */
#endif

    INT16U           OSTCBDly;              /* Nbr ticks to delay task or, timeout waiting for event   */
    INT8U            OSTCBStat;             /* Task      status                                        */
    INT8U            OSTCBStatPend;         /* Task PEND status                                        */
    INT8U            OSTCBPrio;             /* Task priority (0 == highest)                            */
    INT8U            OSTCBX;                /* Bit position in group  corresponding to task priority   */
    INT8U            OSTCBY;                /* Index into ready table corresponding to task priority   */
    INT8U            OSTCBBitX;             /* Bit mask to access bit position in ready table          */
    INT8U            OSTCBBitY;             /* Bit mask to access bit position in ready group          */
} OS_TCB;



/*$PAGE*/
/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

OS_EXT  INT8U  const  		OSUnMapTbl[256];

OS_EXT  INT8U             OSIntNesting;             /* Interrupt nesting level                         */

OS_EXT  INT8U             OSPrioCur;                /* Priority of current task                        */
OS_EXT  INT8U             OSPrioHighRdy;            /* Priority of highest priority task               */

OS_EXT  INT8U             OSRdyGrp;                        /* Ready list group                         */
OS_EXT  INT8U             OSRdyTbl[OS_RDY_TBL_SIZE];       /* Table of tasks which are ready to run    */

OS_EXT  OS_STK            OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE];      /* Idle task stack                */

OS_EXT  OS_TCB           *OSTCBCur;                        /* Pointer to currently running TCB         */
OS_EXT  OS_TCB           *OSTCBFreeList;                   /* Pointer to list of free TCBs             */
OS_EXT  OS_TCB           *OSTCBHighRdy;                    /* Pointer to highest priority TCB R-to-R   */
OS_EXT  OS_TCB           *OSTCBList;                       /* Pointer to doubly linked list of TCBs    */
OS_EXT  OS_TCB           *OSTCBPrioTbl[OS_LOWEST_PRIO + 1];/* Table of pointers to created TCBs        */
OS_EXT  OS_TCB            OSTCBTbl[OS_MAX_TASKS + OS_N_SYS_TASKS];   /* Table of TCBs                  */


/*$PAGE*/
/*
*********************************************************************************************************
*                                            TASK MANAGEMENT
*********************************************************************************************************
*/

INT8U         OSTaskCreate            (void           (*task)(void *p_arg),
                                       void            *p_arg,
                                       OS_STK          *ptos,
                                       INT8U            prio);

void          OSTimeDly               (INT16U           ticks);
void          OSTimeTick              (void);

void          OSInit                  (void);
void          OSIntEnter              (void);
void          OSIntExit               (void);
void          OSStart                 (void);




/*
*********************************************************************************************************
*                                          MESSAGE QUEUE DATA
*********************************************************************************************************
*/

#if OS_Q_EN > 0
typedef struct os_q {                   /* QUEUE CONTROL BLOCK                                         */
    struct os_q   *OSQPtr;              /* Link to next queue control block in list of free blocks     */
    void         **OSQStart;            /* Pointer to start of queue data                              */
    void         **OSQEnd;              /* Pointer to end   of queue data                              */
    void         **OSQIn;               /* Pointer to where next message will be inserted  in   the Q  */
    void         **OSQOut;              /* Pointer to where next message will be extracted from the Q  */
    INT16U         OSQSize;             /* Size of queue (maximum number of entries)                   */
    INT16U         OSQEntries;          /* Current number of entries in the queue                      */
} OS_Q;


typedef struct os_q_data {
    void          *OSMsg;               /* Pointer to next message to be extracted from queue          */
    INT16U         OSNMsgs;             /* Number of messages in message queue                         */
    INT16U         OSQSize;             /* Size of message queue                                       */
    INT8U          OSEventTbl[OS_EVENT_TBL_SIZE];  /* List of tasks waiting for event to occur         */
    INT8U          OSEventGrp;          /* Group corresponding to tasks waiting for event to occur     */
} OS_Q_DATA;

OS_EXT  OS_EVENT         *OSEventFreeList;          /* Pointer to list of free EVENT control blocks    */
OS_EXT  OS_EVENT          OSEventTbl[OS_MAX_QS];		/* Table of EVENT control blocks                   */

OS_EXT  OS_Q             *OSQFreeList;              /* Pointer to list of free QUEUE control blocks    */
OS_EXT  OS_Q              OSQTbl[OS_MAX_QS];        /* Table of QUEUE control blocks                   */



/*$PAGE*/
/*
*********************************************************************************************************
*                                         MESSAGE QUEUE MANAGEMENT
*********************************************************************************************************
*/

OS_EVENT   *OSQCreate (void **start,  INT16U size);
void 			 *OSQPend (OS_EVENT *pevent, INT16U timeout, INT8U *perr);
INT8U 		  OSQPost (OS_EVENT *pevent, void *pmsg);


#endif

#endif


/********************* (C) COPYRIGHT 2015 Windy Albert **************************** END OF FILE ********/

