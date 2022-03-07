/* 12041602, Chyle Andrei Lee and S14-A */

#include <stdio.h>

/* *******************
 This returns the distance between (x1,y1) and (x2,y2).
 You’ll have to call this later on.

 DO NOT CODE THIS. Assume this is already implemented and can be called.
******************* */
double getDistance(double x1,double y1,double x2,double y2);


/* *******************
 Objective #2: Complete the four functions.

 You may refer to the main() function as to how they were called.
 Replace the blanks with the proper statements and data types.
******************* */

void moveCadenceUp(int *cadenceY,int *cloneY)
{
	*cadenceY+=1; // Update Cadence’s Y to move up. Remember, the change should reflect in main()
	*cloneY-=1; // Update Clone’s Y to move down. Remember, the change should reflect in main()
}

void moveCadenceDown(int *cadenceY,int *cloneY)
{
	*cadenceY-=1; // Update Cadence’s Y to move down. Remember, the change should reflect in main()
	*cloneY+=1; // Update Clone’s Y to move up. Remember, the change should reflect in main()
}

void moveCadenceLeft(int *cadenceX,int *cloneX)
{
	*cadenceX-=1;  // Update Cadence’s X to move left. Remember, the change should reflect in main()
	*cloneX+=1; // Update Clone’s X to move right. Remember, the change should reflect in main()
}

void moveCadenceRight(int *cadenceX,int *cloneX)
{
	*cadenceX+=1;  // Update Cadence’s X to move right. Remember, the change should reflect in main()
	*cloneX-=1; // Update Clone’s X to move left. Remember, the change should reflect in main()
}

int main()
{

	/* *********************
	 DO NOT CHANGE THIS SECTION
	 ********************** */

	int cadenceX, cadenceY; // (x,y) coordinates of Cadence
	int cloneX, cloneY; 		// (x,y) coordinates of the Clone
	
	int bSafe = 0; 			// boolean flag. You MAY use this
	char cIn; 				// Character input to represent each movement
	
	printf ("Enter Cadence's coordinates (x,y): ");
	scanf ("%d%d",&cadenceX,&cadenceY);
	printf ("Enter Clone's coordinates (x,y): ");
	scanf ("%d%d",&cloneX,&cloneY);
	
	printf ("\n");
  
	/* **********************
	 From this section hereon, you are to complete the skeleton
	********************* */
	
	do 	/* Use a proper loop and condition */
	{
		scanf ("%c",&cIn);

		/* ******************
		 Objective #1: Properly map the inputs to the correct condition and action
		******************* */

		if (cIn=='U') 		// Input to move Cadence Up
			moveCadenceUp(&cadenceY,&cloneY);
		else if (cIn=='D') 		// Input to move Cadence Down
			moveCadenceDown(&cadenceY,&cloneY);
		else if (cIn=='L') 		// Input to move Cadence Left
			moveCadenceLeft(&cadenceX,&cloneX);
		else if (cIn=='R') 		// Input to move Cadence Right
			moveCadenceRight(&cadenceX,&cloneX);
		else if (cIn=='-') 		// Attempt to end the program
		{
			printf ("Cadence's location: (%d,%d)\n",cadenceX,cadenceY);
			printf ("Clone's location: (%d,%d)\n",cloneX,cloneY);

			/* ***********
			 Objective 3: Find the correct condition to check for Cadence’s safety
						 and terminate the loop & program successfully
			************/
			
			if (10.0<=getDistance(cadenceX *1.0,cadenceY*1.0,cloneX*1.0,cloneY*1.0)) 		/* Check if Cadence is safe.
										   Make use of the correct condition or function call. */
			{
				bSafe=1; 		
				printf ("Cadence is safe now! We can stop.\n");
			}
			else
				printf ("Cadence is NOT SAFE! We can't stop yet!\n");
		}
	}while(bSafe==0);
	
	return 0;
}
