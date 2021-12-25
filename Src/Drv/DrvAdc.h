#ifndef DRVADC_H
#define DRVADC_H

/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Ifx_Types.h"

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef enum
{
  ADC_GROUP0_CH0 = 0u,
  ADC_GROUP0_CH1,
  ADC_GROUP0_CH2,
  ADC_GROUP0_CH3,
  ADC_GROUP0_CH4,
  ADC_GROUP0_CH5,
  ADC_GROUP0_CH6,
  ADC_GROUP0_CH7,
  ADC_GROUP0_MAX
}ADC_GROUP0;
  
typedef struct
{
    uint32_t InfRaySense1_Raw;
    uint32_t InfRaySense2_Raw;
}SensorAdcRaw;
/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/
extern SensorAdcRaw stSensorAdcRaw;

/*----------------------------------------------------------------*/
/*                        Global Function Prototype                  */
/*----------------------------------------------------------------*/
extern void DrvAdcInit(void);
extern void DrvAdc_GetAdcRawGroup0(void);


#endif


