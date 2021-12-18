/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "Scheduler.h"
#include "DrvSys.h"

/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Main Function--------------------------*/
int core0_main(void)
{
    /*System Init*/
    DrvSys();

    /*Scheduler Init*/
    Scheduler_Init();
    
    /*Global Interrupt Enable*/
    IfxCpu_enableInterrupts();

    while(1)
    {
        Scheduler();
    }
    return (1);
}

