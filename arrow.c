/* arrow.c -- implementation of arrowhead library functions */

#define INCL_GPIPRIMATIVES
#include <os2.h>

#include <math.h>

#include "arrow.h"

static double pi = 3.14159265358;      /* what it is */

static POINTL findArrowLinePoint(LONG length, double dAngle, POINTL point)
{
   double dYprime, dXprime;            /* arrowhead points in cartesian coords */
   POINTL rpoint;                      /* point of end of line                 */

   if (0 <= dAngle && dAngle <= pi / 2.0)
      {
      dYprime = point.y - length * sin(dAngle);
      dXprime = point.x + length * cos(dAngle);
      }
   else if (pi / 2.0 < dAngle && dAngle <= pi)
      {
      dYprime = point.y - length * sin(pi - dAngle);
      dXprime = point.x - length * cos(pi - dAngle);
      }
   else if (pi < dAngle && dAngle <= 3.0 / 2.0 * pi)
      {
      dYprime = point.y + length * sin(dAngle - pi);
      dXprime = point.x - length * cos(dAngle - pi);
      }
   else
      {
      dYprime = point.y + length * sin(2.0 * pi - dAngle);
      dXprime = point.x + length * cos(2.0 * pi - dAngle);
      }

   rpoint.x = dXprime;
   rpoint.y = dYprime;
   return rpoint;

}  /* findArrowLinePoint */

/* ArrowHead
   draw an arrow head from the start to the end point in the given PS */
void ArrowHead(HPS hps, POINTL ptStart, POINTL ptEnd, LONG lLength, double dAngle, BOOL bFill)
{
   /* now draw an arrowhead at the end */
   double dTheta;                      /* angle of line with x axis        */
   POINTL arrow1, arrow2;              /* points of end of arrowhead lines */
   double omega1, omega2;              /* angle of arrowhead lines         */
   double dAngleRad = dAngle / 180.0 * pi;   /* desired angle in radians   */

   /* calculate the angle of the line */
   if (ptStart.x < ptEnd.x && ptStart.y < ptEnd.y)
      {
      double deltaY = ptEnd.y - ptStart.y;
      double deltaX = ptEnd.x - ptStart.x;
      dTheta = pi - atan(deltaY / deltaX);
      }
   else if  (ptStart.x > ptEnd.x && ptStart.y < ptEnd.y)
      {
      double deltaY = ptEnd.y - ptStart.y;
      double deltaX = ptStart.x - ptEnd.x;
      dTheta = atan(deltaY / deltaX);
      }
   else if  (ptStart.x > ptEnd.x && ptStart.y > ptEnd.y)
      {
      double deltaY = ptStart.y - ptEnd.y;
      double deltaX = ptStart.x - ptEnd.x;
      dTheta = 2.0 * pi - atan(deltaY / deltaX);
      }
   else if  (ptStart.x < ptEnd.x && ptStart.y > ptEnd.y)
      {
      double deltaY = ptStart.y - ptEnd.y;
      double deltaX = ptEnd.x - ptStart.x;
      dTheta = pi + atan(deltaY / deltaX);
      }
   else if (ptStart.x > ptEnd.x && ptStart.y == ptEnd.y)
      dTheta = 0;
   else if (ptStart.x < ptEnd.x && ptStart.y == ptEnd.y)
      dTheta = pi;
   else if (ptStart.y < ptEnd.y && ptStart.x == ptEnd.x)
      dTheta = pi / 2.0;
   else if (ptStart.y > ptEnd.y && ptStart.x == ptEnd.x)
      dTheta = 3.0 * pi / 2.0;

   /* now calculate the two arrowhead angles */
   omega1 = dTheta - dAngleRad;
   omega2 = dTheta + dAngleRad;

   /* make sure values are between 0 and 2 pi */
   if (omega1 < 0)
      omega1 = omega1 + 2.0 * pi;
   if (omega2 > 2.0 * pi)
      omega2 = omega2 - 2.0 * pi;

   arrow1 = findArrowLinePoint(lLength, omega1, ptEnd);
   arrow2 = findArrowLinePoint(lLength, omega2, ptEnd);

   if (bFill)
      GpiBeginArea(hps, 0UL);

   GpiMove(hps, &arrow1);
   GpiLine(hps, &ptEnd);
   GpiLine(hps, &arrow2);

   if (bFill)
      GpiEndArea(hps);

}  /* ArrowHead */
