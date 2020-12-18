/***************************************************************************\
*                                                                           *
*   Programmer(s):      Dominic Avery, Jan C. Depner                        *
*                                                                           *
*   Date Written:       April 1992                                          *
*                                                                           *
*   Module Name:        corner                                              *
*                                                                           *
*   Module Security                                                         *
*   Classification:     Unclassified                                        *
*                                                                           *
*   Data Security                                                           *
*   Classification:     Unknown                                             *
*                                                                           *
*   Purpose:            Compute a weighted value based on nine adjacent     *
*                       points for each of the corner points of the working *
*			grid.						    *
*                                                                           *
*   Inputs:             *memblock1      -   pointer to regional data        *
*                       *mergeblock     -   pointer to original sparse data *
*                       *x              -   pointer to output data          *
*                       start_row       -   starting row                    *
*                       x_pos           -   starting x position             *
*                       x_pos2          -   ending x position               *
*                       rownum1         -   row position in memblock1       *
*                       final_height    -   height of subarea               *
*                       final_width     -   width of subarea                *
*                       weight_factor   -   weighting factor, final to      *
*                                           regional                        *
*                                                                           *
*   Outputs:            None                                                *
*                                                                           *
*   Calling Routines:   merge_grid                                          *
*                                                                           * 
*   Glossary:           average     -   average value                       *
*                       good_count  -   number of non_null points of the 9  *
*                                       adjacent points                     *
*                       increment   -   directional increment for the x     *
*                                       loop                                *
*                       index1      -   utility integer                     *
*                       index2      -   utility integer                     *
*                       rownum2     -   row index into memblock1            *
*                                                                           *
\***************************************************************************/

#include <stdio.h>
#include <math.h>
#include "misp.h"

void corner (float *memblock1, float *mergeblock, float *x, 
    int32_t start_row, int32_t x_pos, int32_t x_pos2, int32_t rownum1, 
    int32_t final_height, int32_t final_width, int32_t weight_factor)
{
    float        average;
    int32_t      good_count, increment, index1, index2, rownum2;
   
  
    good_count  = 0;
    increment  = 1;
    if (x_pos > x_pos2) increment = -1;

    /*  Go through the nine points looking for non-null data.           */
    
    for (index1 = 0; index1 < 3; index1++)
    {
        for (index2 = x_pos; index2 != (x_pos2 + increment);
            index2 += increment)
        {
            if (*(mergeblock + (index1 * final_width) + index2) < MISPNULL)
                good_count++;
        }
    }

    /*  If there are no non-null points pass back the unweighted        */
    /*  value.                                                          */
    
    if (good_count <= 0)
    {
        *(x + x_pos) = *(memblock1 + (x_pos * final_height) + rownum1);
    }

    /*  Otherwise, calculate the weighted value.                        */
    
    else
    {
        average = 0.0;
        for (index1 = 0; index1 < 3; index1++)
        {
            rownum2 = rownum1 + index1;
            if (rownum1 > 0) rownum2 = rownum1 - 3 + index1;

            /*  Loop through the points and get the sum of the good     */
            /*  points.                                                 */
            
            for (index2 = x_pos; index2 != (x_pos2 + increment);
                index2 += increment)
            {
                if (*(mergeblock + (index1 * final_width) + index2) < MISPNULL)
                {
                    average += *(mergeblock + (index1 * final_width) + index2) -
                        *(memblock1 + (index2 * final_height) + rownum2);
                }
            }
        }

        /*  Compute the average.                                        */
        
        average = average / (float) good_count;
     	if ((*(mergeblock + (start_row * final_width) + x_pos) <= MISPNULL) || 
            (good_count != 1))
        {
            good_count *= abs (weight_factor);
            if (good_count > 9) good_count = 9;

            if (*(mergeblock + (start_row * final_width) + x_pos) < MISPNULL)
            {
                average = *(mergeblock + (start_row * final_width) + x_pos) - 
                    *(memblock1 + (x_pos * final_height) + rownum1);
            }
        }

        /*  Compute the weighted value.                                 */

        if ((*(mergeblock + (start_row * final_width) + x_pos) < MISPNULL) && 
            (weight_factor < 0))
        {
            *(x + x_pos) = *(mergeblock + (start_row * final_width) + x_pos);
        }
        else
        {
            *(x + x_pos) = *(memblock1 + (x_pos * final_height) + rownum1) +
                ((float) good_count / 10.0) * average;
        }
    }
    return;
}
