#ifndef __MISP_H__
#define __MISP_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "nvutility.h"

#ifdef  __cplusplus
extern "C" {
#endif


#define MULT        3
#define FILELENGTH  132
#define MISPNULL    10000000000000000.0
#define OFFSET      0x10000000
#define SPLINE_COL  53
#define SPLINE_ROW  3

typedef struct
{
    int32_t        grid_cols;
    int32_t        grid_rows;
    float          x_min;
    float          y_min;
    float          x_max;
    float          y_max;
    int32_t        width;
    int32_t        height;
} MISP_HEADER;

  int32_t misp_init (double x_interval, double y_interval, float dlta, int32_t reg_mfact, 
                      float srch_rad, int32_t err_cont, float maxz, float minz, 
                      int32_t weight, NV_F64_XYMBR mbr);
  int32_t misp_load (NV_F64_COORD3 xyz);
  uint8_t misp_proc ();
  int32_t misp_rtrv (float *array);
  uint8_t misp_progress_callback_registered ();
  void misp_progress (char *info);


typedef void (*MISP_PROGRESS_CALLBACK) (char *info);

void misp_register_progress_callback (MISP_PROGRESS_CALLBACK progressCB);


#ifdef  __cplusplus
}
#endif

#endif
