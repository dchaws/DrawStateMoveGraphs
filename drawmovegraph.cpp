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
///  This program reads sets of strings, e.g. "12341 14213 13423" and outputs 
///  pstricks code which draws the individual move graphs and the combined move
///  graph. S and T must be specified on the command line.  There are two
///  parameters:  -H will print out latex document and pstricks headers.  /  -P
///  will print out just pstricks headers.
///  We expect there to be an even number of strings.

///  Usage: drawmovegraph 3 4 -H < (file with strings)
///     eg: drawmovegraph 3 4 -P < <(echo 1231 1212) 

#include <iostream>
#include <math.h>
#include <list>
#include <string>

using namespace std;


double timeSpaceSeparation = 1.125;
double stateSpaceSeparation = 1.125;

double gridSizex = 10.0;
double gridSizey = 10.0;

double nodeSize = 0.05;

double chainTextX = 1.0;
double chainTextY = 0.5;

double lineThickness = 0.9;
double dashDim = 1.5;

double labelX=0.5*stateSpaceSeparation - 0.125 - 0.125;
double labelY=(4)*timeSpaceSeparation + 0.5 + 0.125 + 0.125;

string plusColor = "black";
string minusColor = "black";
string countColor = "black"; 
string minusStyle = "dashed";

double xOffset = 0.0;
double yOffset = -0.25;

double edgeLabelOffsetX =  0.0;
double edgeLabelOffsetY =  0.0;

int     gridOn = 0;

int     plusMinusLabel = 1;


int main(int argc, char **argv)
{
    int outputLatexHeader = 0;
    int outputpstricksHeader = 0;

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
        }
    }
    gridSizex = (T+0.25)*(timeSpaceSeparation);
    gridSizey = (S+0.95)*(stateSpaceSeparation);

    if (outputLatexHeader == 1)
    {
        cout << "\\documentclass{article}" << endl;
        cout << "\\usepackage{pstricks,pstricks-add,pst-node}" << endl;
        cout << "\\usepackage{color}" << endl;
        cout << "\\begin{document}" << endl;
        cout << "\\begin{flushleft}" << endl;
    }

    // Read off strings of states
    string inputString;
    list <list <int> > listOfChains;
    list <int> tempChain;

    int stringNumber = 0;
    while ( cin >> inputString)
    {
        tempChain.clear();
        //cout << inputString << endl;
        for(int i=0; i < inputString.size();i++)
        {
            int sOne, sTwo;

            sOne = atoi(inputString.substr(i,1).c_str());
            //sTwo = atoi(inputString.substr(i+1,1).c_str());
            if (sOne < 1)
            {
                cout << "State less than 1." << endl;
                exit(0);
            }
            //cout << sOne << " " << sTwo << endl;
            tempChain.push_back(sOne);
        }
        listOfChains.push_back(tempChain);

        stringNumber++;
    }

    if ((stringNumber % 2) != 0)
    {
        cerr << "The number of strings(chains) is not even." << endl;
        exit(0);
    }


    int combinedMoveGraph[T-1][S][S];
    for (int i=0;i<T-1;i++)
    {
        for (int j=0;j<S;j++)
        {
            for (int k=0;k<S;k++)
            {
                combinedMoveGraph[i][j][k] = 0;
            }
        }
    }

    list <list <int> >::const_iterator lliit = listOfChains.begin();
    int tempT = 0;    
//    labelX=0.5*stateSpaceSeparation - 0.125 - 0.125;
//    labelY=(S)*timeSpaceSeparation + 0.5 + 0.125 + 0.125;

    labelX=0.5*stateSpaceSeparation ;
    labelY=(S)*timeSpaceSeparation + 0.75;
    chainTextX = T/2 + 1.0;

    int curChain = 0; 
    lliit = listOfChains.begin();
    for (;lliit != listOfChains.end();lliit++)
    {
        //tempChain = *lliit;

        if (outputpstricksHeader == 1)
        {
            cout << "\\begin{pspicture}(" << gridSizex << "," << gridSizey << ")" << endl;
            if (gridOn == 1)
            {
                cout << "\\psgrid" << endl;
            }
        }

        // Draw points for the states and time.
        cout << "\\psline[linewidth=";
        cout << 0.8;
        cout << "pt](";
        cout << labelX + xOffset;
        cout << ",";
        cout << labelY + yOffset;
        cout << ")(";
        cout << labelX + 0.25 + xOffset;
        cout << ",";
        cout << labelY - 0.25 + yOffset;
        cout << ")" << endl;

        cout << "\\rput(";
        cout << labelX - 0.0; + xOffset;
        cout << ",";
        cout << labelY - 0.25 + yOffset;
        cout << "){";
        cout << "S";
        cout << "}" << endl;

        cout << "\\rput(";
        cout << labelX + 0.25 + xOffset;
        cout << ",";
        cout << labelY + 0.0 + yOffset;
        cout << "){";
        cout << "T";
        cout << "}" << endl;


        for (int i=0;i<S;i++)
        {
            cout << "\\rput(";
            cout << 0.5*stateSpaceSeparation + xOffset;
            cout << ",";
            cout << (S - i)*timeSpaceSeparation + yOffset;
            cout << "){";
            cout << i+1;
            cout << "}" << endl;

             
            for (int j=0;j<T;j++)
            {
                if (i == 0)
                {
                    cout << "\\rput(";
                    cout << (j+1)*stateSpaceSeparation + xOffset;
                    cout << ",";
                    cout << (S)*timeSpaceSeparation + 0.75 + yOffset;
                    cout << "){";
                    cout << j+1;
                    cout << "}" << endl;


                }
                cout << "\\pscircle*[linecolor=black](";
                cout << (j+1)*stateSpaceSeparation + xOffset;
                cout << ",";
                cout << (i+1)*timeSpaceSeparation + yOffset;
                cout << "){";
                cout << nodeSize;
                cout << "}" << endl;
            }
        }


        tempT = 0;
        list <int>::const_iterator chainIterator = (*lliit).begin();
        list <int>::const_iterator tempChainIterator = (*lliit).begin();
        string tempString;

        tempString.clear();
        char    tempStr[80];

        sprintf(tempStr,"%d",*tempChainIterator);
        tempString.push_back(tempStr[0]);

        tempChainIterator++;
        while (tempChainIterator!=(*lliit).end())
        {
            sprintf(tempStr,"%d",*tempChainIterator);
            tempString.push_back(tempStr[0]);
            if (curChain < stringNumber/2)
            {
                combinedMoveGraph[tempT][*chainIterator-1][*tempChainIterator-1]++;
            }
            else
            {
                combinedMoveGraph[tempT][*chainIterator-1][*tempChainIterator-1]--;
            }
            cout << "\\psline[linewidth=";
            cout << lineThickness;
            cout << "pt";
            if (curChain < stringNumber/2)
            {
                cout << ",linecolor=";
                cout << plusColor;
                cout << "](";
            }
            else
            {
                cout << ",linecolor=";
                cout << minusColor;
                cout << ",linestyle=";
                cout << minusStyle;
                cout << ",dash=";
                cout << dashDim;
                cout << "pt](";
            }
            cout << (tempT + 1)*stateSpaceSeparation + xOffset;
            cout << ",";
            cout << (S + 1 - *chainIterator)*timeSpaceSeparation + yOffset;
            tempChainIterator++;
            chainIterator++;
            tempT++;
            cout << ")(";
            cout << (tempT + 1)*stateSpaceSeparation + xOffset;
            cout << ",";
            cout << (S + 1 - *chainIterator)*timeSpaceSeparation + yOffset;
            cout << ")" << endl;

        }
        // Print the chain text
        if(plusMinusLabel == 1 )
        {
            if (curChain < stringNumber/2)
            {
                tempString = "+" + tempString;
            }
            else
            {
                tempString = "-" + tempString;
            }
        }
        cout << "\\rput(";
        cout << chainTextX + xOffset;
        cout << ",";
        cout << chainTextY + yOffset;
        cout << "){";
        cout << tempString;
        cout << "}" << endl;

        cout << endl;
        if (outputpstricksHeader == 1)
        {
            cout << "\\end{pspicture}" << endl;
        }
//        cout << "Page Break.\\\\" << endl;
//        cout << "\\vskip 20pt" << endl;
//        cout << "\\pagebreak" << endl;
        curChain++;
    }


    // Now print the combined move graph.
    if (outputpstricksHeader == 1)
    {
        cout << "\\begin{pspicture}(" << gridSizex << "," << gridSizey << ")" << endl;
        if (gridOn == 1)
        {
            cout << "\\psgrid" << endl;
        }
//            cout << "\\psgrid" << endl;
    }

    // Draw points for the states and time.
    cout << "\\psline[linewidth=";
    cout << 0.8;
    cout << "pt](";
    cout << labelX + xOffset;
    cout << ",";
    cout << labelY + yOffset;
    cout << ")(";
    cout << labelX + 0.25 + xOffset;
    cout << ",";
    cout << labelY - 0.25 + yOffset;
    cout << ")" << endl;

    cout << "\\rput(";
    cout << labelX - 0.0 + xOffset;
    cout << ",";
    cout << labelY - 0.25 + yOffset;
    cout << "){";
    cout << "S";
    cout << "}" << endl;

    cout << "\\rput(";
    cout << labelX + 0.25 + xOffset;
    cout << ",";
    cout << labelY + 0.0 + yOffset;
    cout << "){";
    cout << "T";
    cout << "}" << endl;


    for (int i=0;i<S;i++)
    {
        cout << "\\rput(";
        cout << 0.5*stateSpaceSeparation + xOffset;
        cout << ",";
        cout << (S - i)*timeSpaceSeparation + yOffset;
        cout << "){";
        cout << i+1;
        cout << "}" << endl;

         
        for (int j=0;j<T;j++)
        {
            if (i == 0)
            {
                cout << "\\rput(";
                cout << (j+1)*stateSpaceSeparation + xOffset;
                cout << ",";
                cout << (S)*timeSpaceSeparation + 0.75 + yOffset;
                cout << "){";
                cout << j+1;
                cout << "}" << endl;


            }
            cout << "\\pscircle*[linecolor=black](";
            cout << (j+1)*stateSpaceSeparation + xOffset;
            cout << ",";
            cout << (i+1)*timeSpaceSeparation + yOffset;
            cout << "){";
            cout << nodeSize;
            cout << "}" << endl;
        }
    }

    cout << "\\rput(";
    cout << chainTextX + xOffset;
    cout << ",";
    cout << chainTextY + yOffset;
    cout << "){";
    cout << "Move Graph";
    cout << "}" << endl;

    for (int i=0;i<T-1;i++)
    {
        for (int j=0;j<S;j++)
        {
            for (int k=0;k<S;k++)
            {
                if (combinedMoveGraph[i][j][k] != 0)
                {
                    cout << "\\pcline[linewidth=";
                    cout << lineThickness;
                    if (combinedMoveGraph[i][j][k] > 0)
                    {
                        cout << "pt](";
                    }
                    else
                    {
                        cout << "pt,linestyle=dashed,";
                        cout << "dash=";
                        cout << dashDim;
                        cout << "pt](";
                    }
                    cout << (i + 1)*stateSpaceSeparation + xOffset;
                    cout << ",";
                    cout << (S - j)*timeSpaceSeparation + yOffset;
                    cout << ")(";
                    cout << (i + 1 + 1)*stateSpaceSeparation + xOffset;
                    cout << ",";
                    cout << (S - k)*timeSpaceSeparation + yOffset;
                    cout << ")" << endl;
                    // Draw edge label if combinedMoveGraph[i][j][k] \notin -1,0,1
                    if (combinedMoveGraph[i][j][k] < -1 || combinedMoveGraph[i][j][k] > 1)
                    {
                        cout << "\\lput*{:U}(0.25){\\textcolor{";
                        cout << countColor; 
                        cout << "}{\\small";
                        cout << combinedMoveGraph[i][j][k];
                        cout << "}}" << endl;

//                        cout << "\\rput(";
//                        cout << (i + 1*0.35 + 2*0.85)*stateSpaceSeparation + edgeLabelOffsetX + xOffset;
//                        cout << ",";
//                        cout << (S - j*0.35 - k*0.85)*timeSpaceSeparation + edgeLabelOffsetY + yOffset;
//                        cout << "){";
//                        cout << combinedMoveGraph[i][j][k];
//                        cout << "}" << endl;

                    }
                }
            }
            
        }
    }

    if (outputpstricksHeader == 1)
    {
        cout << "\\end{pspicture}" << endl;
    }
    
    // End printing combined move graph.

    if (outputLatexHeader == 1)
    {
        cout << "\\end{flushleft}" << endl;
        cout << "\\end{document}" << endl;
    }

}
