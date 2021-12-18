/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Scheduler.h"
#include "DrvStm.h"
#include "Common.h"
#include "DrvGtm.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"
#include "MotorControl.h"
#include "DrvAdc.h"
/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    uint8_t ucScheduler1msFlag;
    uint8_t ucScheduler5msFlag;
    uint8_t ucScheduler10msFlag;
    uint8_t ucScheduler50msFlag;
    uint8_t ucScheduler100msFlag;
    uint8_t ucScheduler200msFlag;
    uint8_t ucScheduler500msFlag;
    uint8_t ucScheduler1sFlag;    
}AppTask;


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void AppNoTimeTask(void);
static void AppTask1ms(void);
static void AppTask5ms(void);
static void AppTask10ms(void);
static void AppTask50ms(void);
static void AppTask100ms(void);
static void AppTask200ms(void);
static void AppTask500ms(void);
static void AppTask1s(void);

static void TaskSchedulerCallbackFnc(void);


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
AppTask stAppTaskInfo;
uint32_t ulScheduler1msCounter = 0u;

extern uint32_t ulPulseCnt;
extern uint32_t gu32nuAscRxData;

/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Application Task Function--------------------------*/
/*NoTime Taksing*/
static void AppNoTimeTask(void)
{

}

/*AppTask 1ms*/
static void AppTask1ms(void)
{

}


/*AppTask 5ms*/
static void AppTask5ms(void)
{

}


/*AppTask 10ms*/
static void AppTask10ms(void)
{
    float32_t fDuty = 0.5f;
    DrvGtmPwmTest(fDuty,fDuty,fDuty,fDuty);
    //Unit_TestControl();    
    Unit_WirelessControl();
}

/*AppTask 50ms*/
static void AppTask50ms(void)
{

}

/*AppTask 100ms*/
static void AppTask100ms(void)
{
    VadcAutoScanDemo_run();
    VadcBackgroundScanDemo_run();
}

/*AppTask 200ms*/
static void AppTask200ms(void)
{

}

/*AppTask 500ms*/
static void AppTask500ms(void)
{

}

/*AppTask 1s*/
static void AppTask1s(void)
{    
    IfxPort_togglePin(IfxPort_P00_5.port, IfxPort_P00_5.pinIndex);
}


/*---------------------CallbackFunc--------------------------*/
static void TaskSchedulerCallbackFnc(void)
{
    ulScheduler1msCounter++;

    stAppTaskInfo.ucScheduler1msFlag = ON;

    if((ulScheduler1msCounter % 1u) == 0u)
    {
        stAppTaskInfo.ucScheduler1msFlag = ON;
    }

    if((ulScheduler1msCounter % 5u) == 0u)
    {
        stAppTaskInfo.ucScheduler5msFlag = ON;
    }

    if((ulScheduler1msCounter % 10u) == 0u)
    {
        stAppTaskInfo.ucScheduler10msFlag = ON;
    }

    if((ulScheduler1msCounter % 50u) == 0u)
    {
        stAppTaskInfo.ucScheduler50msFlag = ON;
    }

    if((ulScheduler1msCounter % 100u) == 0u)
    {
        stAppTaskInfo.ucScheduler100msFlag = ON;
    }

    if((ulScheduler1msCounter % 200u) == 0u)
    {
        stAppTaskInfo.ucScheduler200msFlag = ON;
    }

    if((ulScheduler1msCounter % 500u) == 0u)
    {
        stAppTaskInfo.ucScheduler500msFlag = ON;
    }

    if((ulScheduler1msCounter % 1000u) == 0u)
    {
        stAppTaskInfo.ucScheduler1sFlag = ON;        
    }

    if(ulScheduler1msCounter >= 3000u) /*Reset at 3Sec*/ 
    {
        ulScheduler1msCounter = 0u;
    }
}
/*---------------------Register CallbackFunc--------------------------*/
void Scheduler_Init(void)
{
    DrvRegStm0CallbackFnc(TaskSchedulerCallbackFnc);
}

/*---------------------Scheduler--------------------------*/
void Scheduler(void)
{
    AppNoTimeTask();
    
    if(stAppTaskInfo.ucScheduler1msFlag == ON)
    {
        stAppTaskInfo.ucScheduler1msFlag = OFF;
        AppTask1ms();

        if(stAppTaskInfo.ucScheduler5msFlag == ON)
        {
            stAppTaskInfo.ucScheduler5msFlag = OFF;
            AppTask5ms();
        }

        if(stAppTaskInfo.ucScheduler10msFlag == ON)
        {
            stAppTaskInfo.ucScheduler10msFlag = OFF;
            AppTask10ms();
        }

        if(stAppTaskInfo.ucScheduler50msFlag == ON)
        {
            stAppTaskInfo.ucScheduler50msFlag = OFF;
            AppTask50ms();
        }

        if(stAppTaskInfo.ucScheduler100msFlag == ON)
        {
            stAppTaskInfo.ucScheduler100msFlag = OFF;
            AppTask100ms();
        }

        if(stAppTaskInfo.ucScheduler200msFlag == ON)
        {
            stAppTaskInfo.ucScheduler200msFlag = OFF;
            AppTask200ms();            
        }

        if(stAppTaskInfo.ucScheduler500msFlag == ON)
        {
            stAppTaskInfo.ucScheduler500msFlag = OFF;
            AppTask500ms();
        }

        if(stAppTaskInfo.ucScheduler1sFlag == ON)
        {
            stAppTaskInfo.ucScheduler1sFlag = OFF;
            AppTask1s();
        }
    }
}
