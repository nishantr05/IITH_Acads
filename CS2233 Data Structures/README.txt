INPUT FORMATS :

QUESTION 1:

1) First line of input contains alphabet string (enter newline to terminate). NOTE: integer 'T' is NOT read on the first line.
2) The functionality input is given as dictated in the question, i.e :
 a) Store
 b) Print
 c) Sort (not 'Ascend')
 d) Remove T
3)Enter two successive new line characters to terminate giving the functionality input.

QUESTION 2:

1) Input is given as dictated by the question.
2) The input of keys will end with a new line character.Two successive new line characters are entered to terminate giving the functionality input.
 	
QUESTION 3 :

The graph is a 'Directed' graph
1)In the first line number of Vertices is entered.
2)List of edges in entered. Enter two successive new line characters to terminate.
3)Functionality input (enter two successive new line characters to terminate) :

 a) N v  		-- prints all neighbors of vertex 'v'
 b) V    		-- prints all the vertices present in G
 c) EW v1 v2  	-- prints the weight of edge (v1, v2)
 d) CE v1 v2	-- prints whether edge (v1. v2) is present or not.
 e) CV v		-- prints whether vertex 'v' is present or not.

QUESTION 4:

1) In the first line number of Vertices is entered.
2) Then list of edges are entered (as given in the question). Enter two successive new line characters to terminate this input.
3) Next, functionality input (i.e 'Find' and 'SP v') is entered. Again, enter two successive new line characters to terminate giving the functionality input.

QUESTION 5:

1) Input is given as dictated by the question.
2) The list of edges are entered (as stated in the 4th question). Enter two successive new line characters to terminate this input.

Note : Output format is as given in the problem statements.



ADDITIONAL LIBRARIES USED :

1) <vector> : Dynamic arrays.
2) <algorithm> : For using the 'sort' function (implemented using the quicksort algo, with O(nlogn) runtime).
3) <queue> : For using FIFO queues (priority_queues is not used and I have my own implementation, using min-heaps).
4) <utility> : for using 'pair<int, int>' i.e to store two integers as a pair.
