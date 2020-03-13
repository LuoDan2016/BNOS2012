/*
*********************************************************************************************************
*                                                BNOS 2012
*                                          The Real-Time Kernel
*
*                          (c) Copyright 2011-2012, BOOLESION.NET,NETC
*                                           All Rights Reserved
*
* File : BNOS.C
* By   : BOOLESION.NET,NETC
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include "source\includes.h"


#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
#include ".\ucosii\os_core.c"
#include ".\ucosii\os_flag.c"
#include ".\ucosii\os_mbox.c"
#include ".\ucosii\os_mem.c"
#include ".\ucosii\os_mutex.c"
#include ".\ucosii\os_q.c"
#include ".\ucosii\os_sem.c"
#include ".\ucosii\os_task.c"
#include ".\ucosii\os_time.c"
