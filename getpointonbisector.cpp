#include "getpointonbisector.h"

void getPointOnBisector(double x1, double y1,double x2, double y2, double dist, double &x3, double &y3)
{
    double m, midx,midy,T,V,U,W,midConst;

    midx = (x1 + x2)/2;
    midy = (y1 + y2)/2;

    m = (y1 - y2)/(x1 - x2);


    T = (y1 - y2);
    V = -(x1 - x2);

    midConst = sqrt(T*T + V*V);

    x3 = T*dist/midConst + midx;
    y3 = V*dist/midConst + midy;

}

