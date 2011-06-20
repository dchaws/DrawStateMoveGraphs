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
#ifndef GETPOINTONBISECTOR_H
#define GETPOINTONBISECTOR_H 1

#include <math.h>

/// This takes in two points (x1,y1) and (x2,y2) and outputs a point on the line
/// perpedicular to the mid point, out a distances of dist. Sign controls which side.
void getPointOnBisector(double x1, double y1,double x2, double y2, double dist, double &x3, double &y3);

#endif
