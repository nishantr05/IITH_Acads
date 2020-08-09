#include <stdio.h>

//This fuction computes the cofactor of the element M[a][b], and stores it in the matrix 'temp'.
void cofactor(int a, int b, int n, int M[n][n], int temp[n-1][n-1])
{
    int row, col ; //'row' and 'col' are counter variables to traverse matrix 'M'
    int i = 0,j = 0 ;      //'i' and 'j' are counter variables to traverse matrix 'temp'
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if ((row == a)||(col == b))  //when the current row is 'a' or col is 'b', then no update is made to matrix 'temp.'
                continue ;

            temp[i][j++] = M[row][col] ; //We store M[row][col] in temp[i][j], and then 'j' is incremented.
            if (j == n-1)                //once 'j == n-1', we crossed the last column of 'temp'. 
            {
                i++ ;                  // continue filling from the next row in 'temp'
                j = 0 ;                //setting j = 0 (i.e 1st column) since we'return in the new row.
            }
        }
    }
}
//Recursive function for finding determinant of the matrix.
int det(int n , int M[n][n])
{
    int sign = 1, sum = 0 ; //'sum' variable stores the final determinant value.
    
    //Base case of recursion. If only one element is present then 'det' will be that element itself.
    if (n == 1)
        return M[0][0] ;

    int temp[n-1][n-1] ;     // 'temp' matrix ,to store cofactors 
    for (int i = 0; i < n; ++i)  //for loop iterates for each element of first row.
    {
        cofactor(0, i, n, M, temp) ;         //computes the cofactor of M[0][i], and is stored in 'temp'
        sum += sign*M[0][i]*det(n-1, temp) ; //recursive call, to compute determinant
        sign = -sign ;                       //at every iteration value of 'sign' is switched (i.e alternates btw -1 and 1)
    } 

    return sum ;
}
// Function to get adjoint of M[n][n] in adj[n][n].'n' is the dimention of square matrix 'M'.
void adjoint(int n, int M[n][n], int adj[n][n])
{
    int temp[n-1][n-1] ; // 'temp' matrix ,to store cofactors  
    int sign ;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cofactor(i, j, n, M, temp) ;     //Computing and storing the cofactor of M[i][j] in temp.
            sign = ((i+j)%2 == 0) ? 1 : -1 ; // If (i+j) is even then adj[j][i] is positive, otherwise it's negative.

            //adjoint is the TRANSPOSE of the cofactor matrix.
            //That is why we update 'adj[j][i]' instead of 'adj[i][j]'(row and columns are interchanged).
            adj[j][i] =  sign*det(n-1, temp) ;
        }
    }
}
// Function to calculate and store inverse.
void inverse(int n, int M[n][n])
{
    int d = det(n, M) ;  //storing the determinant of matrix 'M' in D.
    if (d == 0)
    {
        printf("The inverse of the matrix is not possible\n");
        return ;
    }
    //find and store the adjoint matrix in 'adj'
    int adj[n][n] ;
    adjoint(n, M, adj) ;
    //printing the the inverse matrix using the formula inv[i][j] = adj[i][j]/det(M) .
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%0.2f\t ", adj[i][j]/(float)d );
        }   
        printf("\n");
    }
}
//Function to compute and print the product of matrices 'A' and 'B'
void matrix_mul(int m, int n, int p, int q, int A[m][n], int B[p][q])
{
    int C[m][q] ; // Product matrix 'C' will have order m,q .
    int sum ; // 'sum' variable stores sum of the product of row elements in 'A' multiplied with corresponding column elements in 'B'.
    printf("\nMultiplication Matrix C[%d][%d]:\n", m , q);
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < q; ++j)
        {
            sum = 0 ;
            for (int k = 0; k < n; ++k)  // the value 'n' and 'p' are the same, so 'k' can be iterated til either value.
            {
                sum += A[i][k]*B[k][j] ;  //summing up product of elements in ith row of 'A' and jth row of 'B'.
            }
            C[i][j] = sum ;
            printf("%d\t", C[i][j] ); //printing the values of matrix 'C' 
        }
        printf("\n");
    }
    //Inverse computation of matrix 'C'
    printf("\nInverse of Matrix C :\n");
    if (m != q)
        printf("The inverse of the matrix is not possible\n");
    else
        inverse(m, C) ;    //Calling function 'inverse' by passing matrix 'C' and it's dimension.
}

int main()
{
    int i, j ; //counter variables
    int m,n,p,q ; //m,n--> number of rows and columns in matrix 'A'. p,q--> number of rows and columns in matrix 'B'.
    //While loop which terminates only when valid input in given.
    while(1)
    {
        printf("Enter order of matrix A : ");
        scanf("%d %d", &m, &n) ;
        printf("Enter order of matrix B : ");
        scanf("%d %d", &p, &q) ;
        if ((n == p)&&(m >= 2)&&(n >= 2)&&(p >= 2)&&(q >= 2)) //If all these conditions satisfy, then input is valid and we break out.
            break ;
        else
            printf("Error: Enter the orders again:\n");  //In case of invalid input, print an error statement and take input again.
    }
    int A[m][n], B[p][q] ; //declaring two 2-D arrays 'A' and 'B', to store the matrix entries.
    //Reading elements of matrix A.
    printf("\nEnter the elements of matrix A[%d][%d]\n", m, n);
    for (i = 0; i < m; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &A[i][j]) ;

    //Reading elements of matrix B.
    printf("Enter the elements of matrix B[%d][%d]\n", p, q);
    for (i = 0; i < p; ++i)
        for (j = 0; j < q; ++j)
            scanf("%d", &B[i][j]) ;

    matrix_mul(m, n, p, q, A, B) ; 


    return 0;
}