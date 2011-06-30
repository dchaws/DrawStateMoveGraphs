A sample from a Markov chain on N states is simply a sequence(word) of numbers
from 1,...,N. Under the time homogeneous model the sufficient statistics are
given by the number of transitions from i to j. So, given a word 1231121, the
sufficient statistics would be

11  1
12  2
13  0
21  1
22  0
23  1
31  1
32  0
33  0


The sufficient statistics of a word w can naturally be represented by the state
graph which is a multi graph on N nodes with x directed arcs from i to j if
there are x transition from i to j in the word w.


The program drawstategraph reads in words, or the sufficient statistics, and
draws the state graph in latex using the pstricks package.

  To run, type the following 
	./drawstategraph S T < input.file  > output.file

  where S and T are integer numbers and the input file
 contains an even amount of words of length T in S letters

 Here S is the number of nodes (N above) and T is the length of the word. By
 default if the program reads in m words, then the first m/2 words are drawn in
 red and the last m/2 words are drawn in blue. The reason for this is we were
 studying Markov bases of the toric ideal of the design matrix. 
 
 The output is a TeX code that draws the State Graph
 and requires the package 'pstricks'

  -H will print out latex document and pstricks headers.
  -P will print out just pstricks headers.
  -I will draw a symbol for the initial state.
  -C will read in the counts instead of a path
  -L will assume loopless when reading in counts
  -D will print the degree counts.
  -A <num> will be arrowSep

  Usage: drawstategraph 3 4 -H < (file with strings)
     eg: drawstategraph 3 4 -P < <(echo 1231 1212) 
     eg: drawstategraph 3 4 -C < <(echo 1 0 1 0 2 0 1 0 2)
     eg: drawstategraph 3 4 -C -L < <(echo 0 1 0 2 1 0 )




 the option - P adds the \begin{pspicture} and \end{pspict}


	./drawstategraph 3 4 -P < testinput3.txt


 The option -H creates a self contained LaTeX file
 starting with the \documentclass, \begin{document} and so


	./drawstategraph 3 4 -H < testinput3.txt


 The option -I is for including the initial states in the graph
 by making a larger node on the initial state

	./drawstategraph 3 4 -I < testinput3.txt


