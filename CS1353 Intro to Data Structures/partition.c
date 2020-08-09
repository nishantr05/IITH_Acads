#include<stdio.h>

void swap(int *ptra, int *ptrb)
{
 int t;
  t = *ptra;
  *ptra = *ptrb;
  *ptrb = t;
} 
//method 1
int partition(int A[], int low, int high)
{
    int pivot = A[low];
    int i = low; int j = high ;
	while(i<j)
	{
		while(A[i] <= pivot)
		{
			i++;
			if(i == high) break;
		}

		while(A[j] >= pivot)
		{
			j--;
			if(j == low) break;
		}
		if(i<j)
			swap(&A[i], &A[j]);

	}
	swap(&A[j], &A[low]);
	return j;

}
//method 2
int partition_1(int A[], int low, int high)
{

	int pivot = A[low];
	int pivot_index = high;
	for (int i = high; i > low; i--)
	{
		if(A[i] >= pivot)
		{
			swap(&A[i], &A[pivot_index]);
			pivot_index--;
		}
	}

	swap(&A[low], &A[pivot_index]);
    return pivot_index;

}
int partition_2(int A[], int low, int high)
{
	int pivot = A[high];
	int pivot_index = low ;
	for (int i = 0; i < high; ++i)
	{
		if (A[i] < pivot)
		{
			swap(&A[i], A[pivot_index]);
			pivot_index++;
		}
	}
}
void quick_sort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pindex = partition(arr, low, high);
		quick_sort(arr, low, pindex-1);
		quick_sort(arr, pindex+1, high);
	
	}

}

int main()
{
	int arr[] = {4, 2, 3, 5, 1, 7, 4, -8};
	quick_sort(arr, 0, 7);
	for (int i = 0; i < 8; ++i)
	printf("%d, ", arr[i]);
    printf("\n");
	return 0;
}