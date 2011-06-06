#include "circlefromthreepoints.h" 

void circleFromThreePoints( double x1, double y1, 
                            double x2, double y2, 
                            double x3, double y3, 
                            double &cx, double &cy, double &r)
{
    double ma,mb;
    double x,y;

    ma = (y2 - y1)/(x2 - x1);
    mb = (y3 - y2)/(x3 - x2);
    //cout << ma << " " << mb << endl;

    x = (ma*mb*(y1 - y3) + mb*(x1 + x2) - ma*(x2 + x3))/(2*(mb - ma));
    //cout << x << endl;

    y = -(1.0/mb)*(x - (x2+x3)/2) + (y2 + y3)/2;
    //cout << y << endl;

    cx = x;
    cy = y;

    r = sqrt( (cx - x1)*(cx - x1) + (cy - y1)*(cy - y1));
}

