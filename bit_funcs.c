#include "nvutility.h"

/***************************************************************************\
*                                                                           *
*   Programmer(s):      Dominic Avery, Jan C. Depner                        *
*                                                                           *
*   Date Written:       April 1992                                          *
*                                                                           *
*   Module Name:        bit_set                                             *
*                                                                           *
*   Module Security                                                         *
*   Classification:     Unclassified                                        *
*                                                                           *
*   Data Security                                                           *
*   Classification:     Unknown                                             *
*                                                                           *
*   Purpose:            Set the specified bit of a given floating-point     *
*                       value to one or zero.                               *
*                                                                           *
*   Inputs:             *value  -   floating point value                    *
*                       bit     -   bit to be set                           *
*                       binary  -   0 or 1                                  *
*                                                                           *
*   Outputs:            None                                                *
*                                                                           *
*   Calling Routines:   Utility routine                                     *
*                                                                           * 
*   Glossary:           data    -   union of an int32_t and float          *
*                                                                           *
*   Method:             The floating point value input is stored in a       *
*                       floating point variable that is in a union with an  *
*                       integer.  The bit in the integer is set or unset    *
*                       and then the float from the union is placed in the  *
*                       input float variable.                               *
*                                                                           *
\***************************************************************************/
                                                                            
void bit_set (float *value, int32_t bit, int32_t binary)
{
    union
    {
        uint32_t             intvalue;
        float                fltvalue;
    } data;

    data.fltvalue = *value;
    if (binary)
    {
        data.intvalue |= binary << bit;
    }
    else
    {
        data.intvalue &= ~(1 << bit);
    }
    *value = data.fltvalue;

    return;
}


/***************************************************************************\
*                                                                           *
*   Programmer(s):      Dominic Avery, Jan C. Depner                        *
*                                                                           *
*   Date Written:       April 1992                                          *
*                                                                           *
*   Module Name:        bit_test                                            *
*                                                                           *
*   Module Security                                                         *
*   Classification:     Unclassified                                        *
*                                                                           *
*   Data Security                                                           *
*   Classification:     Unknown                                             *
*                                                                           *
*   Purpose:            Test the specified bit of a given floating-point    *
*                       value.                                              *
*                                                                           *
*   Inputs:             value   -   floating point value                    *
*                       bit     -   bit to be tested                        *
*                                                                           *
*   Outputs:            int32_t      -   1 if bit is set, otherwise 0       *
*                                                                           *
*   Calling Routines:   Utility routine                                     *
*                                                                           * 
*   Glossary:           data    -   union of an int32_t and float          *
*                                                                           *
*   Method:             The floating point value input is stored in a       *
*                       floating point variable that is in a union with an  *
*                       integer.  The bit in the integer is tested and the  *
*                       result is returned.                                 *
*                                                                           *
\***************************************************************************/
                                                                            
int32_t bit_test (float value, int32_t bit)
{
    union
    {
        uint32_t             intvalue;
        float                fltvalue;
    } data;

    data.fltvalue = value;

    return ((data.intvalue & (1 << bit)));
}
