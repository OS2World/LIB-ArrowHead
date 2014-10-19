/* arrow.h -- definition of functions in the arrowhead library */

#ifndef __ARROW_HEAD
#define __ARROW_HEAD

/*
Name:  ArrowHead
Purpose:  Draw an arrowhead into the given PS for a line running from ptStart to ptEnd.
          Arrow head has length lLength, and each arrowhead line is angle dAngle degrees
          one either side of given line
Input:   hps -- presentation space,
         ptStart -- starting point of line
         ptEnd -- end point of line
         lLength -- length of arrowhead in units
         dAngle -- offset angle in degrees
         bFill -- TRUE if
*/

#ifdef __cplusplus
   extern "C" {
#endif

void ArrowHead(HPS hps, POINTL ptStart, POINTL ptEnd, LONG lLength, double dAngle, BOOL bFill);

#ifdef __cplusplus
   }
#endif

#endif
