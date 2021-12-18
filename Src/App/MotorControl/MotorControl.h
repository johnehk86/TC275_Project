#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

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
typedef enum t_MOTOR_CMD_TYPE
{
    MOTOR_STOP = 0u,
    MOTOR_FWD,
    MOTOR_TURN_RIGHT,
    MOTOR_TURN_LEFT,
    MOTOR_REVERSE,
    MOTOR_CMD_MAX
}MOTOR_CMD_TYPE;


/*----------------------------------------------------------------*/
/*                        Variables                                    */
/*----------------------------------------------------------------*/


/*----------------------------------------------------------------*/
/*                        Global Function Prototype                  */
/*----------------------------------------------------------------*/
extern void MotorFeedbackController(void);
extern void Unit_WirelessControl(void);
extern void Unit_MotorFrontDirectionCtl(MOTOR_CMD_TYPE param_DirectionType);
extern void Unit_MotorRearDirectionCtl(MOTOR_CMD_TYPE param_DirectionType);
extern void Unit_TestControl(void);



#endif

