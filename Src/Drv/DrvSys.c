/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvSys.h"
#include "IfxScuCcu.h"
#include "DrvWatchdog.h"
#include "DrvStm.h"
#include "DrvDio.h"
#include "DrvGtm.h"
#include "DrvAsc.h"
#include "DrvAdc.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    float fPllFreq;

    float fSourceFreq;

    float fSriFreq;
    float fSpbFreq;

    float fCpu0Freq;
    float fCpu1Freq;
    float fCpu2Freq;
    
    float fFsiFreq;
    float fFsi2Freq;

    float fStmFreq;
    float fGtmFreq;

    float fCanFreq;   
}ClockSetting;

ClockSetting ClockSettingInfo;


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void GetClockInfo(void);


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/
void DrvSys(void)
{
    /*Get Clock Information*/
    GetClockInfo();
    /*Watchdog Init*/
    DrvWatchdogInit();
    /*System Timer Moudle Init*/
    DrvStmInit();
    /*Digital Input Output Init*/    
    DrvDioInit();
    /*GTM Init*/
    DrvGtmInit();
    /*ASC Init*/
    DrvAscInit();
    /*ADC Init*/
    DrvAdcInit();
}



static void GetClockInfo(void)
{
    ClockSettingInfo.fPllFreq = IfxScuCcu_getPllFrequency();
    ClockSettingInfo.fSourceFreq = IfxScuCcu_getSourceFrequency();

    ClockSettingInfo.fSriFreq = IfxScuCcu_getSriFrequency(); 
    ClockSettingInfo.fSpbFreq = IfxScuCcu_getSpbFrequency(); 

    ClockSettingInfo.fCpu0Freq = IfxScuCcu_getCpuFrequency(0); 
    ClockSettingInfo.fCpu1Freq = IfxScuCcu_getCpuFrequency(1); 
    ClockSettingInfo.fCpu2Freq = IfxScuCcu_getCpuFrequency(2); 
    
    ClockSettingInfo.fFsiFreq = IfxScuCcu_getFsiFrequency(); 
    ClockSettingInfo.fFsi2Freq = IfxScuCcu_getFsi2Frequency(); 

    ClockSettingInfo.fStmFreq = IfxScuCcu_getStmFrequency(); 
    ClockSettingInfo.fGtmFreq = IfxScuCcu_getGtmFrequency(); 

    ClockSettingInfo.fCanFreq = IfxScuCcu_getCanFrequency(); 
}

