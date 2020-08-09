
A = []

def selection_sort():
	global A
	n = len(A)
	for i in range(0,n-1):
		for j in range(i,n):
			min = A[i]
			if A[j] < min :
				min = A[j]
    #swaping A[i] and min
	temp = A[i]
	A[i] = min
	A[j] = temp
	print('Sorted list : \n', A)

inp = input('Enter your numbers \n')
A = [int(x) for x in inp.split()]
selection_sort()
 	


				
			

		