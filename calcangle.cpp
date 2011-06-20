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
