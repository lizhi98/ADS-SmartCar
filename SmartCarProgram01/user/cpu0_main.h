
#ifndef CPU0_MAIN_H
#define CPU0_MAIN_H

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/

#include "zf_common_headfile.h"

#include"pid.h"
#include"steer.h"
#include"motor.h"
#include"encoder.h"
#include "image.h"

#include<stdio.h>

/******************************************************************************/
#include "Cpu/Std/Ifx_Types.h"
/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Type Definitions------------------------------*/
/******************************************************************************/

typedef struct
{
    float32 sysFreq;                /**< \brief Actual SPB frequency */
    float32 cpuFreq;                /**< \brief Actual CPU frequency */
    float32 pllFreq;                /**< \brief Actual PLL frequency */
    float32 stmFreq;                /**< \brief Actual STM frequency */
} AppInfo;

/** \brief Application information */
typedef struct
{
    AppInfo info;                               /**< \brief Info object */
} App_Cpu0;

/******************************************************************************/
/*------------------------------Global variables------------------------------*/

extern int16 motorLeftSetSpeed;
extern int16 motorRightSetSpeed;

extern int16 motorLeftSpeed;
extern int16 motorRightSpeed;

extern double angle;
extern ElementType element_type;
/******************************************************************************/

IFX_EXTERN App_Cpu0 g_AppCpu0;

#endif
