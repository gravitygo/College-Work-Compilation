#include <stdio.h>
#include "matrixExer.c"

int
main()
{  
   int M[MAX][MAX], 
       B[MAX][MAX],
	   Res[MAX][MAX];

   int row_size, col_size, col_size2; //Assume values are at most equal to MAX
   
   /* put in comment those functions which you have not
      implemented yet */
   
   /* Testing isIdentityMatrix() */
   printf("====================\n");
   printf("Dimension of square matrix: ");
   scanf("%d", &row_size);
   printf("\n====================\n");
   if (row_size % 2 == 0)
      row_size--;
   if (row_size <= 0)
      row_size = 1;
   getInputs(M, row_size, row_size);
   if (!isIdentityMatrix(M, row_size))
      printf("Not an ");
   printf("Identity Matrix!\n\n");
   
   /* Testing TransposeMatrix() */
   printf("====================\n");
   printf("Test Transpose:\n");
   printf("====================\n");
   printf("Rows: ");
   scanf("%d", &row_size);
   printf("Cols: ");
   scanf("%d", &col_size);
   getInputs(M, row_size, col_size);
   TransposeMatrix(M, row_size, col_size, Res);
   printf("\nResulting Table: \n");  
   display2D(Res, col_size, row_size);
    //heres the parameters

   /* Create your statements to test the functions 
      MatrixAdd() and MatrixMultiply() */
    /* test MatrixAdd () */
    printf("====================\n");
    printf("Test Sum:\n");
    printf("====================\n");
  	printf("Rows: ");
  	scanf("%d", &row_size);
  	printf("Cols: ");
  	scanf("%d", &col_size);
   	getInputs(M, row_size, col_size);
    getInputs(B, row_size, col_size);
	  MatrixAdd(Res, M, B, row_size, col_size);
  	printf("Sum of elements: \n");  
	  display2D(Res, row_size, col_size);
      
   /* test MatrixMultiply () */
    printf("====================\n");
    printf("Test Multilply:\n");
    printf("====================\n");
	  printf("Rows in A: ");
  	scanf("%d", &row_size);
    printf("Cols in A: ");
    scanf("%d", &col_size);
    printf("Cols in B: ");
    scanf("%d", &col_size2);
   	getInputs(M, row_size, col_size);
    getInputs(B, col_size2, row_size);
    MatrixMultiply(Res, M, B, row_size, col_size, col_size2);
    printf("Product of elements: \n");  
    display2D(Res, col_size2, col_size);

   return 0;
}