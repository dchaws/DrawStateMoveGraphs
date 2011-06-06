all: drawstategraph drawmovegraph

drawmovegraph: drawmovegraph.cpp 
	g++ -o drawmovegraph drawmovegraph.cpp

drawstategraph: drawstategraph.cpp calcangle.o circlefromthreepoints.o getpointonbisector.o
	g++ -o drawstategraph drawstategraph.cpp calcangle.o circlefromthreepoints.o getpointonbisector.o

calcangle.o: calcangle.h calcangle.cpp
	g++ -c calcangle.cpp

circlefromthreepoints.o: circlefromthreepoints.cpp circlefromthreepoints.h
	g++ -c circlefromthreepoints.cpp

getpointonbisector.o: getpointonbisector.cpp getpointonbisector.h
	g++ -c getpointonbisector.cpp

clean:
	rm -f drawmovegraph drawstategraph *.o
