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

// David Haws
// 6/20/11
// www.davidhaws.net
// https://github.com/dchaws

//  This program reads sets of strings, e.g. "12341 14213 13423" and outputs
///  pstricks code which draws the state graph. S and T must be specified on the
///  command line. 
///  
///  There are two parameters: 
///  -H will print out latex document and pstricks headers.
///  -P will print out just pstricks headers.
///  -I will draw a symbol for the initial state.
///  -C will read in the counts instead of a path
///  -L will assume loopless when reading in counts
///  -D will print the degree counts.
///  -A <num> will be arrowSep

///  Usage: drawstategraph 3 4 -H < (file with strings)
///     eg: drawstategraph 3 4 -P < <(echo 1231 1212) 
///     eg: drawstategraph 3 4 -C < <(echo 1 0 1 0 2 0 1 0 2)
///     eg: drawstategraph 3 4 -C -L < <(echo 0 1 0 2 1 0 )


#include "circlefromthreepoints.h"
#include "calcangle.h"
#include "getpointonbisector.h"
#include <iostream>
#include <math.h>
#include <list>

double arrowSep = 0.17;
double stateGraphRadius = 1.5;
double labelRadiusEpsilon = 0.5;
double degreeCountRadiusEpsilon = labelRadiusEpsilon + 0.4;
double nodeSize = 0.1;
double initialNodeSize = nodeSize + 0.0;
double initialNodeSizeEpsilon = 0.05;
double angleEpsilon = 5;

double gridSizex = (stateGraphRadius + labelRadiusEpsilon)*2 + 1.0;
double gridSizey = (stateGraphRadius + labelRadiusEpsilon)*2 + 1.0;

double xOffset = gridSizex/2;
double yOffset = gridSizey/2;

string arrowDrawColor="black";
int numArrowDrawColors = 4;
string arrowDrawColors[] = {"red","blue", "green", "yellow"};


using namespace std;

int main(int argc, char **argv)
{
    int outputLatexHeader = 0;
    int outputpstricksHeader = 0;
    int drawInitialStates = 0;
    int printDegreeCounts = 0; // 0 means do not print degree count, 1 means print degree counts
    int readCounts = 0; // 0 means read in the word, 1 means in the counts
    int loopless = 0; // 0 means loops, 1 means loopless

    if (argc <= 2) {
        cout << "Error message goes here." << endl;
        exit(0);

    }
    int S,T;

    S = atoi(argv[1]);
    T = atoi(argv[2]);

    if (argc > 3 )
    {
        for (int i=3;i<argc;i++)
        {
            string tempS = argv[i];
            //cout << argv[i] << endl;
            if (tempS == "-H")
            {
                outputLatexHeader = 1;
                outputpstricksHeader = 1;
            }
            if (tempS == "-P")
            {
                outputpstricksHeader = 1;
            }
            if (tempS == "-I")
            {
                drawInitialStates = 1;
            }
            if (tempS == "-C")
            {
                readCounts = 1;
            }
            if (tempS == "-L")
            {
                loopless = 1;
            }
            if (tempS == "-D")
            {
                printDegreeCounts = 1;
            }
            if (tempS == "-A")
            {
                sscanf(argv[i+1],"%f",arrowSep);
                i++;
            }
        }
    }
    if (readCounts == 1 && drawInitialStates == 1)
    {
        cerr << "Can not read in counts and draw initial states." << endl;
        exit(0);
    }

    if (outputLatexHeader == 1)
    {
        cout << "\\documentclass{article}" << endl;
        cout << "\\usepackage{pstricks}" << endl;
        cout << "\\usepackage{color}" << endl;
        cout << "\\begin{document}" << endl;
    }
    if (outputpstricksHeader == 1)
    {
        cout << "\\begin{pspicture}(" << gridSizex << "," << gridSizey << ")" << endl;
//        cout << "\\psgrid" << endl;
    }


    double xStates[S];
    double yStates[S];
    for (int i=0;i<S;i++)
    {
        xStates[i] = stateGraphRadius*cos(2*i*M_PI/(double)S) + xOffset;
        yStates[i] = stateGraphRadius*sin(2*i*M_PI/(double)S) + yOffset;

    }

    int vertexAdjacency[S][S];
    list <int> vertexColors[S][S];

    list <int> initialStates;
    list <int> initialStatesColors;

    for (int i=0;i<S;i++)
    {
        for (int j=0;j<S;j++)
        {
            vertexAdjacency[i][j] = 0;
        }
    }




    if (readCounts == 0) // Assume we are reading in something like 1231 1424
    {
        // Read off strings of states
        string inputString;
        int stringNumber = 0;
        while ( cin >> inputString)
        {
            initialStates.push_back(atoi(inputString.substr(0,1).c_str()));
            initialStatesColors.push_back(stringNumber % numArrowDrawColors);
            //cout << inputString << endl;
            for(int i=0; i < inputString.size() - 1;i++)
            {
                int sOne, sTwo;

                sOne = atoi(inputString.substr(i,1).c_str());
                sTwo = atoi(inputString.substr(i+1,1).c_str());
                if (sOne < 1 || sTwo < 1)
                {
                    cout << "State less than 1." << endl;
                    exit(0);
                }
                //cout << sOne << " " << sTwo << endl;
                //vertexAdjacency[sTwo-1][sOne-1]++;
                vertexAdjacency[sOne-1][sTwo-1]++;
                //vertexColors[sTwo-1][sOne-1].push_front(stringNumber % numArrowDrawColors);
                vertexColors[sOne-1][sTwo-1].push_front(stringNumber % numArrowDrawColors);
            }

            stringNumber++;
        }
    }
    else if (readCounts != 0)
    {
        // For now, read in T chars. That is, expect only one path
        int inputState;
        int fromState=0; //Index lexicographically. We expect loops.
        int toState;
        if (loopless == 0)
        {
            toState=0;
        }
        else {
            toState=1;
        }

        initialStatesColors.push_back(0 % numArrowDrawColors);
        while (cin >> inputState)
        {
            //cout << inputState << ":" << fromState << " " << toState << endl;
            if (inputState > 0)
            {
                vertexAdjacency[fromState][toState]=inputState;
                for (int i=0;i<inputState;i++)
                {
                    vertexColors[fromState][toState].push_front(0 % numArrowDrawColors);
                }
            }

            toState++;
            if (loopless == 1 && toState == fromState)
            {
                toState++;
            }
            if(toState >= S)
            {
                fromState++;
                toState=0;
            }
        }
    }

    int degreeCounts[S];
    for (int i=0;i<S;i++)
    {
        degreeCounts[i] = 0;
    }

    for (int i=0;i<S;i++)
    {
        for (int j=0;j<S;j++)
        {
            if (vertexAdjacency[i][j] != 0)
            {
                //cout << "vertexAdjacency[" << i+1 << "][" << j+1 << "] = " << vertexAdjacency[i][j] << endl;
                // Need to take into account the number of directed edges.
//                cout << "degreeCounts[" << i+1 << "] = " << degreeCounts[i] << endl;
//                cout << "degreeCounts[" << j+1 << "] = " << degreeCounts[j] << endl;
                degreeCounts[i]-= vertexAdjacency[i][j];
                degreeCounts[j]+= vertexAdjacency[i][j];
//                cout << "After." << endl;
//                cout << "degreeCounts[" << i+1 << "] = " << degreeCounts[i] << endl;
//                cout << "degreeCounts[" << j+1 << "] = " << degreeCounts[j] << endl;
            }
        }
    }
//    for (int i=0;i<S;i++)
//    {
//                cout << "   degreeCounts[" << i+1 << "] = " << degreeCounts[i] << endl;
//    }

    for (int i=0;i<S;i++)
    {
        for (int j=0;j<S;j++)
        {
            if( i != j && vertexAdjacency[i][j] > 0)
            {
                //Draw arrows from i to j
                double x3,y3;
                double cx,cy,r;
                double angleOne,angleTwo,angleThree;

                for (int k=0;k<vertexAdjacency[i][j];k++)
                {
                    getPointOnBisector(xStates[j],yStates[j],xStates[i],yStates[i],(k+1)*arrowSep,x3,y3);
//                    cout << "\\pscircle*[linecolor=red](";
//                    cout << x3;
//                    cout << ",";
//                    cout << y3;
//                    cout << "){" << nodeSize << "}" << endl;
                    circleFromThreePoints(xStates[j],yStates[j],x3,y3,xStates[i],yStates[i],cx,cy,r);
//                    cout << "\\pscircle[linecolor=red](" << cx << ", " << cy << "){" << r << "}" << endl;
                    angleOne = calcangle(cx,cy,xStates[j],yStates[j])*180/M_PI;
                    angleTwo = calcangle(cx,cy,x3,y3)*180/M_PI;
                    angleThree = calcangle(cx,cy,xStates[i],yStates[i])*180/M_PI;
                    arrowDrawColor = arrowDrawColors[*(vertexColors[i][j].begin())];
                    vertexColors[i][j].pop_front();
                    cout << "\% Edge " << i+1 << " -> " << j+1 << endl;
                    cout << "\\psarc[linecolor=" << arrowDrawColor << "](" << cx << "," << cy << "){" << r << "}{" << angleTwo - angleEpsilon << "}{" << angleOne << "}" << endl;
                    cout << "\\psarc[linecolor=" << arrowDrawColor << ",arrowsize=6pt]{->}(" << cx << "," << cy << "){" << r << "}{" << angleThree << "}{" << angleTwo << "}" << endl;

                }
            }
        }
    }

    for (int i=0;i<S;i++)
    {
        cout << "\% Node " << i+1 << endl;
        cout << "\\pscircle*[linecolor=black](";
        cout << xStates[i];
        cout << ",";
        cout << yStates[i];
        cout << "){" << nodeSize << "}" << endl;


        cout << "\\rput(";
        cout << (stateGraphRadius + labelRadiusEpsilon)*cos(2*i*M_PI/(double)S) + xOffset;
        cout << ",";
        cout << (stateGraphRadius + labelRadiusEpsilon)*sin(2*i*M_PI/(double)S) + yOffset;
        //cout << "){\\psframebox*{" << i << "}}" << endl;
        cout << "){" << i+1 << "}" << endl;


        if (printDegreeCounts == 1)
        {
            cout << "\\rput(";
            cout << (stateGraphRadius + degreeCountRadiusEpsilon)*cos(2*i*M_PI/(double)S) + xOffset;
            cout << ",";
            cout << (stateGraphRadius + degreeCountRadiusEpsilon)*sin(2*i*M_PI/(double)S) + yOffset;
            //cout << "){\\psframebox*{" << i << "}}" << endl;
            cout << "){" << "\\color{green} " << degreeCounts[i] << "}" << endl;
        }

    }

    if (drawInitialStates == 1)
    {
        list <int>::const_iterator lit = initialStates.begin();
        list <int>::const_iterator lit_colors = initialStatesColors.begin();
        int initialCounter = 0;
        for (;lit!= initialStates.end() && lit_colors != initialStatesColors.end();lit++)
        {
            cout << "\\pscircle*[linecolor=";
            cout << arrowDrawColors[*lit_colors]; 
            cout << "](";
            cout << xStates[*lit-1];
            cout << ",";
            cout << yStates[*lit-1];
            cout << "){" << initialNodeSize + (initialStates.size() - 1 - initialCounter)*initialNodeSizeEpsilon << "}" << endl;

            lit_colors++;
            initialCounter++;
        }
    }



    if (outputpstricksHeader == 1)
    {
        cout << "\\end{pspicture}" << endl;
    }
    if (outputLatexHeader == 1)
    {
        cout << "\\end{document}" << endl;
    }

}
