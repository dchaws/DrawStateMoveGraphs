#include "calcangle.h"

double calcangle(double cx, double cy, double x, double y)
{
    double tx, ty, r, angle;

    r = sqrt( (cx - x)*(cx - x) + (cy - y)*(cy - y));

    tx = (x - cx)/r;
    ty = (y - cy)/r;

    //cout << r << " " << tx << " " << ty << endl;

    angle = acos(tx);
    //cout << angle << endl;

    if (ty >= 0)
    {
        return angle;
    }
    else {
        return 2*M_PI - angle;
    }
}
