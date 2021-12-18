/*----------------------------------------------------------------*/
/*                        Include Header File                     */
/*----------------------------------------------------------------*/
#include "DrvStm.h"
#include "IfxStm.h"
#include "IfxCpu_Irq.h"
#include "DrvSys.h"

/*----------------------------------------------------------------*/
/*                        Define                                  */
/*----------------------------------------------------------------*/
#define STM_TIME_1MS                100000u


/*----------------------------------------------------------------*/
/*                        Typedefs                                */
/*----------------------------------------------------------------*/
typedef struct stm_info
{
    Ifx_STM             *stmSfr;            /**< \brief Pointer to Stm register base */
    IfxStm_CompareConfig stmConfig;         /**< \brief Stm Configuration structure */
}STM_INFO;


/*----------------------------------------------------------------*/
/*                        Static Function Prototype               */
/*----------------------------------------------------------------*/
static void DrvStm0Init(void);



/*----------------------------------------------------------------*/
/*                        Variables                               */
/*----------------------------------------------------------------*/
STM_INFO gstnuStmInfo;
unsigned long ulnuStmCnt = 0u;

void (*DrvStm0CallbackFnc)(void);
/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/
IFX_INTERRUPT(STM_Int0Handler, 0, ISR_PRIORITY_STM_INT0);

/*---------------------Interrupt Service Routine--------------------------*/
void STM_Int0Handler(void)
{
    IfxStm_clearCompareFlag(gstnuStmInfo.stmSfr, gstnuStmInfo.stmConfig.comparator);
    IfxStm_increaseCompare(gstnuStmInfo.stmSfr, gstnuStmInfo.stmConfig.comparator, STM_TIME_1MS);

    /*Stm Collback Function*/
    DrvStm0CallbackFnc();
}

/*---------------------Callback Function--------------------------*/
void DrvRegStm0CallbackFnc(void (*pDrvRegCallbackFnc)(void))
{
    DrvStm0CallbackFnc = pDrvRegCallbackFnc;
}

/*---------------------Init Function--------------------------*/
void DrvStmInit(void)
{
    DrvStm0Init();
}

static void DrvStm0Init(void)
{
    IfxStm_enableOcdsSuspend(&MODULE_STM0);

    gstnuStmInfo.stmSfr = &MODULE_STM0;
    IfxStm_initCompareConfig(&gstnuStmInfo.stmConfig);

    gstnuStmInfo.stmConfig.triggerPriority = ISR_PRIORITY_STM_INT0;
    gstnuStmInfo.stmConfig.typeOfService   = IfxSrc_Tos_cpu0;
    gstnuStmInfo.stmConfig.ticks           = STM_TIME_1MS*10u;            /*1ms*10 = 10ms*/

    IfxStm_initCompare(gstnuStmInfo.stmSfr, &gstnuStmInfo.stmConfig);
}
