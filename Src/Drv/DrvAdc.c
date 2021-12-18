/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "DrvAdc.h"
#include "IfxVadc.h"
#include "IfxVadc_Adc.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    IfxVadc_Adc vadc; /* VADC handle */
    IfxVadc_Adc_Group adcGroup;
} App_VadcAutoScan;

typedef struct
{
    IfxVadc_Adc vadc;   /* VADC handle*/
    IfxVadc_Adc_Group adcGroup;
} App_VadcBackgroundScan;


/*----------------------------------------------------------------*/
/*                        Static Function Prototype                  */
/*----------------------------------------------------------------*/
static void DrvAdc0Init(void);
static void DrvAdc1Init(void);

/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
App_VadcAutoScan g_VadcAutoScan;
App_VadcBackgroundScan g_VadcBackgroundScan;

IfxVadc_Adc_Channel adc0Channel[5];
IfxVadc_Adc_Channel adc1Channel[2];

uint32_t g_Vadc0Result[5] = {0u,};
uint32_t g_Vadc1Result[2] = {0u,};

/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/

/*---------------------Interrupt Define--------------------------*/



/*---------------------Test Code--------------------------*/
void VadcAutoScanDemo_run(void)
{
    uint32    chnIx;

    for (chnIx = 0; chnIx < 5; ++chnIx)
    {
        /* wait for valid result */
        Ifx_VADC_RES conversionResult;

        do
        {
            conversionResult = IfxVadc_Adc_getResult(&adc0Channel[chnIx]);
        } while (!conversionResult.B.VF);

        g_Vadc0Result[chnIx] = conversionResult.B.RESULT;
    }

    /* start autoscan */
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}

void VadcBackgroundScanDemo_run(void)
{
    uint32    chnIx;

    /* check results */
    for (chnIx = 0; chnIx < 2; ++chnIx)
    {
        /* wait for valid result */
        Ifx_VADC_RES conversionResult;

        do
        {
            conversionResult = IfxVadc_Adc_getResult(&adc1Channel[chnIx]);
        } while (!conversionResult.B.VF);

         g_Vadc1Result[chnIx] = conversionResult.B.RESULT;
    }
}

/*---------------------Init Function--------------------------*/
void DrvAdcInit(void)
{
    DrvAdc0Init();
    DrvAdc1Init();
}

static void DrvAdc0Init(void)
{
    uint32    chnIx;
    IfxVadc_Adc_ChannelConfig adcChannelConfig[5];    /* create channel config */

    /* VADC Configuration */

    /* create configuration */
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    /* initialize module */
    IfxVadc_Adc_initModule(&g_VadcAutoScan.vadc, &adcConfig);

    /* create group config */
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcAutoScan.vadc);

    /* with group 0 */
    adcGroupConfig.groupId = IfxVadc_GroupId_0;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    /* enable scan source */
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;

    /* enable auto scan */
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;

    /* enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    /* initialize the group */
    /*IfxVadc_Adc_Group adcGroup;*/    //declared globally
    IfxVadc_Adc_initGroup(&g_VadcAutoScan.adcGroup, &adcGroupConfig);

    for (chnIx = 0; chnIx < 5; ++chnIx)
    {
        IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &g_VadcAutoScan.adcGroup);

        adcChannelConfig[chnIx].channelId      = (IfxVadc_ChannelId)(chnIx);
        adcChannelConfig[chnIx].resultRegister = (IfxVadc_ChannelResult)(chnIx);  /* use dedicated result register */

        /* initialize the channel */
        IfxVadc_Adc_initChannel(&adc0Channel[chnIx], &adcChannelConfig[chnIx]);

        /* add to scan */
        unsigned channels = (1 << adcChannelConfig[chnIx].channelId);
        unsigned mask     = channels;
        IfxVadc_Adc_setScan(&g_VadcAutoScan.adcGroup, channels, mask);
    }

    /* start autoscan */
    IfxVadc_Adc_startScan(&g_VadcAutoScan.adcGroup);
}

static void DrvAdc1Init(void)
{
    uint32    chnIx;
    IfxVadc_Adc_ChannelConfig adcChannelConfig[2];     /* create channel config */

    /* VADC Configuration */

    /* create configuration */
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    /* initialize module */
    IfxVadc_Adc_initModule(&g_VadcBackgroundScan.vadc, &adcConfig);

    /* create group config */
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &g_VadcBackgroundScan.vadc);

    /* with group 1 */
    adcGroupConfig.groupId = IfxVadc_GroupId_1;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    /* enable background scan source */
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;

    /* enable background auto scan */
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;

    /* enable all gates in "always" mode (no edge detection) */
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    /* initialize the group */
    IfxVadc_Adc_initGroup(&g_VadcBackgroundScan.adcGroup, &adcGroupConfig);

   for (chnIx = 0; chnIx < 2; ++chnIx)
    {
        IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &g_VadcBackgroundScan.adcGroup);

        adcChannelConfig[chnIx].channelId         = (IfxVadc_ChannelId)(chnIx + 3);
        adcChannelConfig[chnIx].resultRegister    = (IfxVadc_ChannelResult)(3 + chnIx); // use register #5 and 6 for results
        adcChannelConfig[chnIx].backgroundChannel = TRUE;

        /* initialize the channel */
        IfxVadc_Adc_initChannel(&adc1Channel[chnIx], &adcChannelConfig[chnIx]);

        /* add to background scan */
        unsigned channels = (1 << adcChannelConfig[chnIx].channelId);
        unsigned mask     = channels;
        IfxVadc_Adc_setBackgroundScan(&g_VadcBackgroundScan.vadc, &g_VadcBackgroundScan.adcGroup, channels, mask);
    }

    /* start scan */
    IfxVadc_Adc_startBackgroundScan(&g_VadcBackgroundScan.vadc);
}
