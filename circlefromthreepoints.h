#ifndef CIRCLEFROMTHREEPOINTS_H
#define CIRCLEFROMTHREEPOINTS_H 1

#include <math.h>
#include <iostream>

using namespace std;

/// This calculates the center and radius of the circle given by the three
/// points (x1,y1), (x2,y2), and (x3,y3). It assumes they lay in that order
/// on the circle. For a picture and equations, see 
/// http://local.wasp.uwa.edu.au/~pbourke/geometry/circlefrom3/
void circleFromThreePoints( double x1, double y1, 
                            double x2, double y2, 
                            double x3, double y3, 
                            double &cx, double &cy, double &r);

#endif
