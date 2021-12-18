#ifndef DRVASCTYPES_H
#define DRVASCTYPES_H

/*----------------------------------------------------------------*/
/*                        Include Header File                          */
/*----------------------------------------------------------------*/
#include "Ifx_Types.h"
#include <Asclin/Asc/IfxAsclin_Asc.h>

/*----------------------------------------------------------------*/
/*                        Define                                        */
/*----------------------------------------------------------------*/
#define ASC_TX_BUFFER_SIZE 64
#define ASC_RX_BUFFER_SIZE 64

/*----------------------------------------------------------------*/
/*                        Typedefs                                    */
/*----------------------------------------------------------------*/
typedef struct
{
    uint8 tx[ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
    uint8 rx[ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
} AppAscBuffer;

typedef struct
{
    AppAscBuffer ascBuffer;                     /**< \brief ASC interface buffer */
    struct
    {
        IfxAsclin_Asc asc0;                     /**< \brief ASC interface */
    }         drivers;

    uint8     txData[17];
    uint8     rxData[17];
    Ifx_SizeT count;
} App_AsclinAsc;

#endif


