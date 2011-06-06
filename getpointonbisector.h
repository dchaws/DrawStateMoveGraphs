#ifndef GETPOINTONBISECTOR_H
#define GETPOINTONBISECTOR_H 1

#include <math.h>

/// This takes in two points (x1,y1) and (x2,y2) and outputs a point on the line
/// perpedicular to the mid point, out a distances of dist. Sign controls which side.
void getPointOnBisector(double x1, double y1,double x2, double y2, double dist, double &x3, double &y3);

#endif
