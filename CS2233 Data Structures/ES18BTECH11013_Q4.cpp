#include <iostream>
#include<string>
#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#define infinity 1e9
#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2
using namespace std;

typedef pair<int, int> intPair ;
vector<intPair> A;   //Vector 'A' is our min-heap.

// Min-heap functionalities; heapify, insert and extract_min :
void heapify(int i)
{
    int len = A.size()-1, smallest;
    int l = LEFT(i) ;
    int r = RIGHT(i) ;
    if (l <= len && A[l].first < A[i].first )
        smallest = l ;
    else
        smallest = i ;
    if (r <= len && A[r].first < A[smallest].first)
        smallest = r ;
    if(smallest != i)
    {
        iter_swap(A.begin()+i, A.begin()+smallest) ;
        heapify(smallest) ;
    }
}

void insert(intPair P)
{
    A.push_back(P) ;
    int x = A.size()-1 ;
    while(PARENT(x) >= 0 && A[x].first < A[PARENT(x)].first)
    {
        iter_swap(A.begin()+x, A.begin()+PARENT(x)) ;
        x = PARENT(x) ;
    }
}

int extract_min()
{
    int len = A.size()-1 ;
    int result = A[0].second ;    //vertex whose distance from source is min
    iter_swap(A.begin(), A.end()-1)  ;
    A.pop_back() ;
    heapify(0) ;
    return result ;
}

void BFS(vector<int> adj[], int visited[], int s, int &count)
{
    int u ;
    count ++ ;
    visited[s] = count;     //The source vertex is by default visited.
    queue <int> Q ;
    Q.push(s) ;
    while (!Q.empty())
    {
        u = Q.front() ;
        Q.pop() ;
        for (int i = 0; i < adj[u].size(); ++i)
        {
            if(visited[adj[u][i]] == 0)
            {
                visited[adj[u][i]] = count ; // Marking the vertice as visited with some non-zero value
                Q.push(adj[u][i]) ;
            }
        }
    }
}

void Find(vector<int> adj[], int V)
{
    int visited[V] = {0} ;
    int count = 0 ;
    for (int i = 0; i < V; ++i)
    {
        if (visited[i] == 0)
            BFS(adj, visited, i, count) ;
    }
    cout << count << " components" << endl ;
    for (int i = 1; i <= count; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            if (visited[j] == i)
                cout << j << " " ;
        }
        cout << endl ; 
    }

}

void dijkstra(vector<intPair> adj[], int src, int V)
{
    int u, v, weight, id, i = 0 ;
    //Using minimum priority queue (i.e min heap) 
    //creating a vector of distances, all initialized to infinity.
    vector<int> dist(V, infinity) ;  
    dist[src] = 0 ;
    insert(make_pair(0, src)) ;  //inserting into min-heap 'A'
    while (!A.empty())
    {
        u = extract_min() ;
        i = 0 ;
        for (intPair x : adj[u]) 
        { 
            v = x.first ;
            weight = x.second ;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u]+weight ;  
                insert(make_pair(dist[v], v)) ;
            }
        } 
    } 
    for (int i = 0; i < V; ++i)
    {
        if (dist[i] != infinity)
            cout << src << " " << i << " " << dist[i] << endl ;
    }
}

int main()
{
    char ch ;
    int V, E, x, y, wt, source ;
    string ign ;
    cout << "Enter number of vertices :" << endl ;
    cin >> V ;
    
    vector<intPair> adj_D[V] ;    // adjacency list of directed graph.
    vector<int> adj_UD[V] ;       // adjacency list of undirected graph. 
    //Taking the input from user :
    cout << "Enter the edges (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        getchar() ;
        ch = getchar() ;
        if (ch == '\n')
            break ;
        cin >> x >> y >> wt ;
        adj_D[x].push_back(make_pair(y, wt)) ;
        adj_UD[x].push_back(y) ;    
        adj_UD[y].push_back(x) ;
        
    }
    cout << "Functionality input (enter two successive new line characters to terminate) :" << endl ;
    while(true)
    {
        ch = getchar() ;
        if (ch == '\n')
            break ;
        switch(ch)
        {
            case 'f' :
            case 'F' :
                cin >> ign ;
                Find(adj_UD, V) ;
                break ;

            case 'S' :
                getchar() ;
                cin >> source ;
                dijkstra(adj_D, source, V) ;
                break ;
        } 
        getchar() ;
    }
    return 0;
}