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
