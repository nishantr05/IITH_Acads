#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;

//structure 'node' for each member of the set.
struct node
{
    int rank;
    node* parent ; 
};
struct edge
{
    int u, v ;
    int wt ;
};
bool compare(edge a, edge b) 
{ 
    return a.wt < b.wt; 
} 

//Disjoint set functionalities implemented using forests. Rank, path compression heuristics are also implemented.
node* make_set(int val)
{
    node* new_node = new node ;
    new_node -> rank = 0 ;
    new_node -> parent = new_node ;  //The 'parent' field points to the node its present in.
    return new_node ;
}

//'find_set': recursive function which returns the representative node of the set
// As it recurses, it makes one pass to find the root (representative) node.
// As the recursion unwinds, the parent of each node is made to point to the root, i.e path compression heuristic is implemented.
node* find_set(node* x)
{
    if(x != (x -> parent))
        x -> parent = find_set(x -> parent);
    return(x -> parent) ;
}

//Computes the union of two sets using rank heuristics.
void union_set(node* Arr[], int x, int y)
{
    node* x_rep = find_set(Arr[x]) ;
    node* y_rep = find_set(Arr[y]) ;
    if ((x_rep -> rank) > (y_rep -> rank))
        y_rep -> parent = x_rep ;
    else
    {
        x_rep -> parent = y_rep ;
        if ((x_rep -> rank) == (y_rep -> rank))
            y_rep->rank += 1 ;
    }
}

int main()
{
    char ch ;
    int V, E, x, y, weight, len = 0;
    vector<edge> Edges; 
    vector<edge> A ;    //Set 'A' which stores all the edges belonging to the MST.
    cout << "Enter the number of vertices" << endl ;
    cin >> V ;
    node* Arr[V] ;
    cout << "Enter the edges (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        getchar() ;
        ch = getchar() ; 
        if (ch == '\n')
            break ;
        cin >> x >> y >> weight ;
        Edges.push_back(edge()) ;
        Edges[len].u = x ;
        Edges[len].v = y ;   
        Edges[len].wt = weight ;
        len++ ; 
    }
    //Implementing Kruskals algorithm for determining the MST :

    for (int i = 0; i < V; ++i) 
        Arr[i] = make_set(i) ;                    // O(V) make set operations
    sort(Edges.begin(), Edges.end(), compare) ;   //sorting the edges in ascending order (O(ElogE) time).
    
    for (edge iter : Edges) 
    { 
        if (find_set(Arr[iter.u]) != find_set(Arr[iter.v]))  //Checking if the edge is safe to add to set 'A' or not:
        {   
            A.push_back(iter) ;
            union_set(Arr, iter.u, iter.v) ;
            if(A.size() == V-1)                //We have already formed our MST, so we break out.
                break ;
        }
    } 
    if (A.size() == V-1)
    {
        for (edge i : A)
            cout << "(" << i.u << ", " << i.v << ")  " ;
        cout << endl ;
    }
    else
        cout << "Spanning tree does not exist" << endl ;
    
    return 0;
}