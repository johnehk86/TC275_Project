/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvDio.h"
#include "IfxPort.h"
#include "IfxPort_PinMap.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Driver API--------------------------*/
void DrvDio_SetPinLow(IfxPort_Pin param_PortPin)
{
    IfxPort_setPinLow(param_PortPin.port, param_PortPin.pinIndex);
}

void DrvDio_SetPinHigh(IfxPort_Pin param_PortPin)
{
    IfxPort_setPinHigh(param_PortPin.port, param_PortPin.pinIndex);
}

/*---------------------Init Function--------------------------*/
void DrvDioInit(void)
{
    /*P00_0    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P00_0.port, IfxPort_P00_0.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P00_0.port, IfxPort_P00_0.pinIndex);

    /*P00_1    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P00_1.port, IfxPort_P00_1.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P00_1.port, IfxPort_P00_1.pinIndex);

    /*P00_2    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P00_2.port, IfxPort_P00_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P00_2.port, IfxPort_P00_2.pinIndex);

    /*P00_3    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P00_3.port, IfxPort_P00_3.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P00_3.port, IfxPort_P00_3.pinIndex);

    /*P11_2    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P11_2.port, IfxPort_P11_2.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P11_2.port, IfxPort_P11_2.pinIndex);

    /*P11_3    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P11_3.port, IfxPort_P11_3.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P11_3.port, IfxPort_P11_3.pinIndex);

    /*P11_6    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P11_6.port, IfxPort_P11_6.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P11_6.port, IfxPort_P11_6.pinIndex);

    /*P11_9    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P11_9.port, IfxPort_P11_9.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P11_9.port, IfxPort_P11_9.pinIndex);

    /*P33_7    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P33_7.port, IfxPort_P33_7.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P33_7.port, IfxPort_P33_7.pinIndex);
}
