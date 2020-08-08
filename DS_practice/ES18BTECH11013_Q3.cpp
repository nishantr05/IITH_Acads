#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std ;

int V ;

bool contains_vertex(int v)
{
    if (v >= 0 && v < V)
        return true ;
    else
        return false ;
}

bool contains_edge(vector<pair<int, int>> adj[], int v1, int v2)
{
    bool is_present = 0 ;
    if ((v1 >= V || v1 < 0)||(v2 >= V || v2 < 0))
        return  0 ;

    for (pair<int, int> x : adj[v1]) 
    {
        if (x.first == v2)
        { 
            is_present = 1;
            break ;
        }
    }   
    if (is_present)
        return true ;
    else
        return false ;
}

void vertices()
{
    for (int i = 0; i < V; ++i)
        cout << i << " " ;
    cout << endl ;    
}

void neighbors(vector<pair<int, int>> adj[], int v)
{
    if (! contains_vertex((adj, v)))
    {
        cout << "Such a vertex does not exist. Please enter a valid vertex." << endl ;
        return ;
    }
    for (pair<int, int> x : adj[v]) 
        cout << x.first << " " ;
    cout << endl ;    
}

void edge_weight(vector<pair<int, int>> adj[], int v1, int v2)
{
    if (!contains_edge(adj, v1, v2))
    {
        cout << "Such an edge does not exist. Please enter a valid edge." << endl ;
        return ;
    }

    for (pair<int, int> x : adj[v1]) 
    {
        if (x.first == v2)
        { 
            cout << x.second << endl ;
            break ;
        }
    }   
}

int main()
{
    char ch, c ;
    int x, y, wt, v1, v2 ;
    cout << "Enter number of vertices :" << endl ;
    cin >> V ;
    vector<pair<int, int>> adj_D[V] ;    // adjacency list of directed graph.
    cout << "Enter the edges (enter two successive new line characters to terminate) :" << endl ;
    //Taking user INPUT :
    while(true)
    {
        getchar() ;
        ch = getchar() ; 
        if (ch == '\n')
            break ;
        cin >> x >> y >> wt ;
        adj_D[x].push_back(make_pair(y, wt)) ;
    }
    cout << "Functionality input (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        ch = getchar() ;
        if (ch == '\n')
            break ;
        switch(ch)
        {
            case 'N' :
            case 'n' :
                cin >> v1 ;
                neighbors(adj_D, v1) ;
                break ;

            case 'V' :
            case 'v' :
                vertices() ;
                break ;

            case 'C' :
                c = getchar() ;
                if (c == 'V')
                {    
                    cin >> v1 ;
                    if (contains_vertex(v1))
                        cout << "Vertex " << v1 << " is present" << endl ;
                    else
                        cout << "Vertex " << v1 << " is NOT present" << endl ;
                }
                else
                {
                    cin >> v1 >> v2 ;
                    cout << "Edge from " << v1 << " to " << v2 ;
                    if(contains_edge(adj_D, v1, v2))
                        cout << " exists" << endl ;
                     else
                        cout << " doesn't exist " << endl ;
                }
                break ;

            case 'E' :
                getchar() ;
                cin >> v1 >> v2 ;
                edge_weight(adj_D, v1, v2) ;
                break ;
        } 
        getchar() ;
    }
    return 0;
}