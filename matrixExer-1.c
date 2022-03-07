/* Contributing Members:
    Binalla, Nathania Izabel Dizon
    Bondoc, Alyana Erin Uy
    Sy, Mon Jericho 
    Lee, Chyle Andrei Antonio

   Section: S12
*/
#include<stdio.h>
#define MAX 20

/* This function gets n inputs for the 1-D array.
     
   You are NOT allowed to edit this function.
*/
void
InputList(int A[], int n)
{ 
	int i;

    for (i = 0; i < n; i++)
      scanf("%d", &A[i]);
}

/* This function displays the contents of the 1-D array L.
   
   You are NOT allowed to modify this function.
*/
void
PrintList(int L[], int n)
{
  int j;
  for (j = 0; j < n; j++)
    printf("%4d ", L[j]);
  printf("\n");
}

// ---- Implement the following functions ----
//   -- NO printf() statements in the following functions
//   -- main() should NOT be in this file

/* This function should get row_size x col_size number
   of input values from the user.  The getting of input
   is done using row major accessing, and should be via
   calls to InputList().
   
   @param M - the 2D array
   @param row_size - the number of rows to initialize in M
   @param col_size - the number of columns to initialize in M
   
   Precondition: row_size and col_size are positive and at most
                 equal to MAX
*/
void
getInputs(int M[][MAX], int row_size, int col_size)
{
  int i;
	
	for (i = 0; i < row_size; i++)
		InputList(M[i], col_size);    
}

/* This function displays the contents of M using row-major
   accessing.  The solution to this function SHOULD include
   call to PrintList().  No printf() should be in this 
   function.
 
   @param M - the 2D array
   @param row_size - the number of rows to initialize in M
   @param col_size - the number of columns to initialize in M
   
   Precondition: row_size and col_size are positive and at most
                 equal to MAX
*/
void
display2D(int M[][MAX], int row_size, int col_size)
{
  int row;
  for(row=0; row < row_size; row++)
    PrintList(M[row], col_size);
}

/* This function returns 1 if the dim x dim matrix M is
   an identity matrix, and returns 0 otherwise.  An 
   identity matrix is a square matrix whose main diagonal
   elements are all 1, and the remaining elements are all 0.
   
   @param M - the 2D array
   @param dim - the dimensions of M.  That is if dim is 5, 
                then M is a 5 x 5 array.
   @return 1 if M is an identity matrix, 0 otherwise

   Precondition: dim is an odd number and is at most 19
*/
int 
isIdentityMatrix(int M[][MAX], int dim)
{
   int row;
   int col;
   int found = 1;

   for(row = 0; row < dim; row++)
   {
      for(col = 0; col < dim; col++)
      {
         if(row == col && M[row][col] != 1)
            found = 0;
         else if(row != col && M[row][col] != 0)
             found = 0;
      }
   }
   
  return found;
}

/* This function updates the contents of T to contain
   the transpose of M with row_size number of rows and
   col_size number of columns.
   
   @param M - the 2D array
   @param row_size - number of initialized rows in M
   @param col_size - number of initialized columns in M
   @param T - the transpose of M
 
   Precondition: row_size and col_size are positive and
                 at most equal to MAX
*/  
void
TransposeMatrix(int M[][MAX], int row_size, int col_size,
                int T[][MAX])
{
  int row, col;
  
  for(row=0; row<row_size; row++)
  {
    for(col=0; col<col_size; col++)
      T[col][row]=M[row][col];
  }

}

/* This function updates the contents of C to contain
   the sum of the matrices A and B, where each has
   row_size number of initialized rows and col_size 
   number of columns initialized. M with row_size number of rows and
   col_size number of columns.
   
   @param A - one of the 2D arrays to be used in the sum
   @param B - the other 2D array to be used in the sum
   @param C - the 2D array where the resulting sum should be stored
   @param row_size - number of initialized rows in B & c
   @param col_size - number of initialized columns in B & C
 
   Precondition: row_size and col_size are positive and
                 at most equal to MAX
*/  
void
MatrixAdd(int C[][MAX], int A[][MAX], int B[][MAX], 
               int row_size, int col_size)
{
  /*source: https://en.wikipedia.org/wiki/Matrix_addition*/
  int i, j;

  for(i = 0 ; i < row_size; i++){
    for(j = 0; j < col_size; j++){
        C[i][j] = A[i][j] + B[i][j];
    }
  }

}



/* This function performs matrix multiplication on A and B
   and stores the result in C. A and B, where each has
   row_size number of initialized rows and col_size 
   number of columns initialized. M with row_size number of rows and
   col_size number of columns.
   
   @param A - one of the 2D arrays to be used in the sum
   @param B - the other 2D array to be used in the sum
   @param C - the 2D array where the resulting product should be stored
   @param row_sizeA - number of initialized rows in A; this is also
                   the resulting number of initialized rows in C
   @param col_sizeA - number of initialized columns in A; this
                     is also the number of initialized rows in B
   @param col_sizeB - number of initialized columns in B; this is
                   also the resulting number of initialized columns in C
 
   Preconditions: 
     1. row_sizeA and col_size are positive and at most equal to MAX
	    rows in 
2. the number of columns in the A is equal to the number of     rows in the B
*/
void MatrixMultiply(int C[][MAX], int A[][MAX], int B[][MAX], 
                    int row_sizeA, int col_sizeA, int col_sizeB)
{
  /* source: https://en.wikipedia.org/wiki/Matrix_multiplication*/
  int i, j, k;
  int sum;

  for(k = 0; k < col_sizeB; k++){
    for( j = 0; j < col_sizeA; j++){
      sum=0;
      for(i  = 0; i < row_sizeA; i++){
        sum += A[i][j] * B[k][i];
      }
      C[k][j]=sum;
    }
  }

}
