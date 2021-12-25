/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "MotorControl.h"
#include "MidDio.h"
#include "DrvGtm.h"
#include "MidAdc.h"

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
extern uint32_t gu32nuAscRxData;
uint8_t u8nuTestInput = 0u;
float32_t fSenseMotorRpm;

uint8_t gulUltraStartFlag = 0u;
extern float32_t fUltraDistance;
/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/
void Unit_UltraSenseTrig(void)
{
    static uint32_t ulUltraSenseCnt = 0u;

    if(ulUltraSenseCnt == 0u)
    {
        gulUltraStartFlag = 1u;
        MidDio_SetUltraTrig(1u);
    }
    else if(ulUltraSenseCnt == 1u)
    {
        MidDio_SetUltraTrig(0u);
    }
    else
    {
        /*No Code*/
    }

    ulUltraSenseCnt++;
   
    if(ulUltraSenseCnt >= 100u)
    {
        ulUltraSenseCnt = 0u;
        gulUltraStartFlag = 0u;
    }
}


void Unit_UltraTest(void)
{
    uint8_t u8nuWirelessCmd = 0u;
    float32_t fDuty =0.5f;
    
    if(fUltraDistance > 50.0f)
    {
        fDuty = 0.5f;
    }
    else if(fUltraDistance > 30.0f)
    {
    fDuty = 0.2f;

    }
    else if(fUltraDistance > 10.0f)
    {
    fDuty = 0.1f;

    }
    else if(fUltraDistance > 5.0f)
    {
    fDuty = 0.1f;

    }
    else
    {
        fDuty = 0.0f;
        gu32nuAscRxData = 's';
    }

    DrvGtmPwmTest(fDuty,fDuty,fDuty,fDuty);

    u8nuWirelessCmd = (uint8_t)gu32nuAscRxData;
    
    if(u8nuWirelessCmd == 'w')    /*Forward*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_FWD);
        Unit_MotorRearDirectionCtl(MOTOR_FWD);
    }
    else if(u8nuWirelessCmd == 'd') /*TurnRight*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_RIGHT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_RIGHT);
    }
    else if(u8nuWirelessCmd == 'a') /*TurnLeft*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_LEFT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_LEFT);
    }
    else if(u8nuWirelessCmd == 'x') /*Reverse*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_REVERSE);    
        Unit_MotorRearDirectionCtl(MOTOR_REVERSE);
    }    
    else if(u8nuWirelessCmd == 's') /*Stop*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_STOP);    
        Unit_MotorRearDirectionCtl(MOTOR_STOP);
    }
    else
    {
        /*No Code*/
    }  

}

void Unit_WirelessControl(void)
{
    uint8_t u8nuWirelessCmd = 0u;
    SensorAdcRaw* pstSensorAdcRaw = MidAdc_GetAdcGroup0SenseRaw();
    static uint8_t ucWarningFlag = 0u;
    static uint8_t ucWarningUltraFlag = 0u;
    static uint8_t ucFirstDetectionFlag = 0u;
    static uint8_t ucFirstUltraDetectionFlag = 0u;
    float32_t fDuty =0.35f;      

    if(pstSensorAdcRaw->InfRaySense1_Raw >= 2200u || pstSensorAdcRaw->InfRaySense2_Raw >= 2200u)
    {
        if(ucFirstDetectionFlag == 0u)
        {
            if(pstSensorAdcRaw->InfRaySense1_Raw > pstSensorAdcRaw->InfRaySense2_Raw) 
            {
                u8nuWirelessCmd = 'a'; /*TurnLeft*/
            }
            else
            {
                u8nuWirelessCmd = 'd'; /*TurnRight*/
            }
            ucFirstDetectionFlag = 1u;
            ucWarningFlag = 1u;
        }
    }
    else if(fUltraDistance < 5.0f) /*Distance < 5Cm*/
    {
        if(ucFirstUltraDetectionFlag == 0u)
        {
            u8nuWirelessCmd = 'x'; /*Reverse*/
            ucFirstUltraDetectionFlag = 1u;
            ucWarningUltraFlag = 1u;
        }
    }
    else
    {    
        if(ucWarningFlag == 1u)
        {
            gu32nuAscRxData = 'w';
            ucWarningFlag = 0u;
            ucFirstDetectionFlag = 0u;
        }

        if(ucWarningUltraFlag == 1u)
        {
            gu32nuAscRxData = 'w';
            ucWarningUltraFlag = 0u;
            ucFirstUltraDetectionFlag = 0u;
        }
        
        u8nuWirelessCmd = (uint8_t)gu32nuAscRxData;
    }
      
    if(u8nuWirelessCmd == 'w')    /*Forward*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_FWD);
        Unit_MotorRearDirectionCtl(MOTOR_FWD);
    }
    else if(u8nuWirelessCmd == 'd') /*TurnRight*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_RIGHT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_RIGHT);
    }
    else if(u8nuWirelessCmd == 'a') /*TurnLeft*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_LEFT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_LEFT);
    }
    else if(u8nuWirelessCmd == 'x') /*Reverse*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_REVERSE);    
        Unit_MotorRearDirectionCtl(MOTOR_REVERSE);
    }    
    else if(u8nuWirelessCmd == 's') /*Stop*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_STOP);    
        Unit_MotorRearDirectionCtl(MOTOR_STOP);
    }
    else
    {
        /*No Code*/
    }  

    /*Setting Duty*/ 
    DrvGtmPwmTest(fDuty,fDuty,fDuty,fDuty);
}


#if 0
void Unit_WirelessControl(void)
{
    uint8_t u8nuWirelessCmd = 0u;
    SensorAdcRaw* pstSensorAdcRaw = MidAdc_GetAdcGroup0SenseRaw();
    static uint8_t ucWarningFlag = 0u;
    static uint8_t ucFirstDetectionFlag = 0u;
    
    if(pstSensorAdcRaw->InfRaySense1_Raw >= 2200u || pstSensorAdcRaw->InfRaySense2_Raw >= 2200u)
    {
        if(ucFirstDetectionFlag == 0u)
        {
            if(pstSensorAdcRaw->InfRaySense1_Raw > pstSensorAdcRaw->InfRaySense2_Raw) 
            {
                u8nuWirelessCmd = 'a'; /*TurnLeft*/
            }
            else
            {
                u8nuWirelessCmd = 'd'; /*TurnRight*/
            }
            ucFirstDetectionFlag = 1u;
            ucWarningFlag = 1u;
        }
    }
    else
    {    
        if(ucWarningFlag == 1u)
        {
            gu32nuAscRxData = 'w';
            ucWarningFlag = 0u;
            ucFirstDetectionFlag = 0u;
        }
        u8nuWirelessCmd = (uint8_t)gu32nuAscRxData;
    }
      
    if(u8nuWirelessCmd == 'w')    /*Forward*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_FWD);
        Unit_MotorRearDirectionCtl(MOTOR_FWD);
    }
    else if(u8nuWirelessCmd == 'd') /*TurnRight*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_RIGHT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_RIGHT);
    }
    else if(u8nuWirelessCmd == 'a') /*TurnLeft*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_LEFT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_LEFT);
    }
    else if(u8nuWirelessCmd == 'x') /*Reverse*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_REVERSE);    
        Unit_MotorRearDirectionCtl(MOTOR_REVERSE);
    }    
    else if(u8nuWirelessCmd == 's') /*Stop*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_STOP);    
        Unit_MotorRearDirectionCtl(MOTOR_STOP);
    }
    else
    {
        /*No Code*/
    }  
}
#endif

void Unit_MotorFrontDirectionCtl(MOTOR_CMD_TYPE param_DirectionType)
{
    switch(param_DirectionType)
    {
        case MOTOR_STOP: /*Stop*/
        {
            MidDio_SetFrontIn1(0u);
            MidDio_SetFrontIn2(0u);
            MidDio_SetFrontIn3(0u);
            MidDio_SetFrontIn4(0u);    
            break;
        }
        case MOTOR_FWD: /*Forward*/
        {
            MidDio_SetFrontIn1(1u);
            MidDio_SetFrontIn2(0u);
            MidDio_SetFrontIn3(1u);
            MidDio_SetFrontIn4(0u);            
            break;           
        }
        case MOTOR_TURN_RIGHT: /*TurnRight*/
        {
            MidDio_SetFrontIn1(1u);
            MidDio_SetFrontIn2(0u);
            MidDio_SetFrontIn3(0u);
            MidDio_SetFrontIn4(1u);    
            break;            
        }
        case MOTOR_TURN_LEFT: /*TurnLeft*/
        {
            MidDio_SetFrontIn1(0u);
            MidDio_SetFrontIn2(1u);
            MidDio_SetFrontIn3(1u);
            MidDio_SetFrontIn4(0u);            
            break;            
        }
        case MOTOR_REVERSE: /*Reverse*/
        {
            MidDio_SetFrontIn1(0u);
            MidDio_SetFrontIn2(1u);
            MidDio_SetFrontIn3(0u);
            MidDio_SetFrontIn4(1u);            
            break;            
        }
        default:
        break;
    }
}


void Unit_MotorRearDirectionCtl(MOTOR_CMD_TYPE param_DirectionType)
{
    switch(param_DirectionType)
    {
        case MOTOR_STOP: /*Stop*/
        {
            MidDio_SetRearIn1(0u);
            MidDio_SetRearIn2(0u);
            MidDio_SetRearIn3(0u);
            MidDio_SetRearIn4(0u);    
            break;
        }
        case MOTOR_FWD: /*Forward*/
        {
            MidDio_SetRearIn1(1u);
            MidDio_SetRearIn2(0u);
            MidDio_SetRearIn3(1u);
            MidDio_SetRearIn4(0u);    
            break;
        }        
        case MOTOR_TURN_RIGHT: /*TurnRight*/
        {
            MidDio_SetRearIn1(1u);
            MidDio_SetRearIn2(0u);
            MidDio_SetRearIn3(0u);
            MidDio_SetRearIn4(1u);    
            break;
        }
        case MOTOR_TURN_LEFT: /*TurnLeft*/
        {
            MidDio_SetRearIn1(0u);
            MidDio_SetRearIn2(1u);
            MidDio_SetRearIn3(1u);
            MidDio_SetRearIn4(0u);     
            break;
        }
        case MOTOR_REVERSE: /*Reverse*/
        {
            MidDio_SetRearIn1(0u);
            MidDio_SetRearIn2(1u);
            MidDio_SetRearIn3(0u);
            MidDio_SetRearIn4(1u);    
            break;
        }
        default:
        break;
    }
}

void Unit_TestControl(void)
{       
    if(u8nuTestInput == 1u)    /*Forward*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_FWD);
        Unit_MotorRearDirectionCtl(MOTOR_FWD);
    }
    else if(u8nuTestInput == 2u) /*TurnRight*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_RIGHT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_RIGHT);
    }
    else if(u8nuTestInput == 3u) /*TurnLeft*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_TURN_LEFT);    
        Unit_MotorRearDirectionCtl(MOTOR_TURN_LEFT);
    }
    else if(u8nuTestInput == 4u) /*Reverse*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_REVERSE);    
        Unit_MotorRearDirectionCtl(MOTOR_REVERSE);
    }    
    else if(u8nuTestInput == 5u) /*Stop*/
    {
        Unit_MotorFrontDirectionCtl(MOTOR_STOP);    
        Unit_MotorRearDirectionCtl(MOTOR_STOP);
    }
    else
    {
        /*No Code*/
    }  
}

