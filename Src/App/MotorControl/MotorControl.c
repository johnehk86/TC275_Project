/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "MotorControl.h"
#include "MidDio.h"
#include "DrvGtm.h"

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


/*----------------------------------------------------------------*/
/*                        Functions                                    */
/*----------------------------------------------------------------*/
#if 0
float32_t fPwmDuty = 0.5f;    
float32_t fSenseMotorRpm = 0.0f;
uint32_t ulRpmRef =50u;
uint32_t ulPGain = 3u; 
uint32_t ulIGain = 12u;

extern uint32_t gu32nuAscRxData;
extern uint32_t ulPulseCnt;
extern uint32_t gu32nuRxFlag;

void MotorFeedbackController(void)
{            
    static int32_t lProportionalControlInput = 0;
    static int32_t lIntegralControlInput = 0;
    static int32_t lIntegralControlOld = 0;
    static uint32_t ulSamplingFrequency = 10u; /*100ms*/

    int32_t g_nError = 0;
    int32_t g_nControlInput = 0;

    fSenseMotorRpm = ((float32_t)ulPulseCnt*60.0f*10.0f)/(8.0f*120.0f);
    ulPulseCnt = 0u;

    /*PID Contorller*/
    g_nError =((int32_t)ulRpmRef- (int32_t)fSenseMotorRpm); 		    
    lProportionalControlInput = (int32_t)ulPGain*g_nError/10;	// Not to express the gain as float -> g_nPGain/10						

    lIntegralControlInput = lIntegralControlOld + ((int32_t)ulIGain*g_nError/(int32_t)ulSamplingFrequency/10);	
    g_nControlInput = (lProportionalControlInput + lIntegralControlInput);  //PID control input	 
    lIntegralControlOld = lIntegralControlInput;								

    if(lIntegralControlOld > 80u) 
    {
        lIntegralControlOld = 80u; //Limit accumulated value by I gain
    }     

    if(g_nControlInput >= 80u)
    {
        g_nControlInput =80u;  //Limit control input (0<=contorl input<100)  
    }    
    else if(g_nControlInput <= 0u)
    {
        g_nControlInput = 0u;    
    }
    else
    {
        /*No Code*/
    }

    /*Gtm PWM Test*/
    fPwmDuty = (float32_t)g_nControlInput/100.0f;
    DrvGtmPwmTest(fPwmDuty,fPwmDuty,fPwmDuty,fPwmDuty);  	    	  
}
#endif

void Unit_WirelessControl(void)
{
    uint8_t u8nuWirelessCmd = 0u;
    
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

