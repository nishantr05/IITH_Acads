#include <iostream>
#include <cmath>
#define MAX 1000000
using namespace std;

/* "DP_COINS PROBLEM"
int coins[4] = {1, 3, 5, 8} ;

int main()
{
	  int S = 22 ;
	  int min_sum[S+1] ;
	  min_sum[0] = 0 ;
	  for (int i = 1; i <= S; ++i)
	    min_sum[i] = MAX ;

	  //min_sum[i] = min(min_sum[i-coins[j]]) , where rhs is evaluated for each 'coin[j]' . *reccurence relation*
	  //for each 'i', 'i' being the sum, we find min_sum[i], which is the minimum number of coins required to form sum 'i'.  
	for (int i = 1; i <= S; ++i)
		for (int j = 0; j < 4; ++j)
			if(i >= coins[j] && min_sum[i-coins[j]]+1 < min_sum[i])
				min_sum[i] = min_sum[i-coins[j]] + 1 ;
    
    if (min_sum[S] < MAX )
	  cout << min_sum[S] << endl ;
	else
	  cout << "ampossiiblee\n" ;

	  return 0;
} */

int main()
{
	int N = 6, max = 0;
	int seq[N] = {} ;
	int S[N] ;  // S[i] is the length of the longest decresing subsequence with last element as seq[i]
    
    for (int i = 0; i < N; ++i)
      S[i] = 1 ; // the least len of the longest decresing subsequence is 1, with element seq[i]

    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < i; ++j)
      {
      	 if (seq[j]<=seq[i] && S[j]+1 > S[i])
      	 	S[i] = S[j]+1 ;
      }
    }

    for (int i = 0; i < N; ++i)
      if (max < S[i])
      	max = S[i] ;
	
	return 0;
}