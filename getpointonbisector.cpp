// DrawStateMoveGraphs is for drawing state and move graphs of Markov chains.
// Copyright (C) 2011 David C. Haws

//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// See LICENSE
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

