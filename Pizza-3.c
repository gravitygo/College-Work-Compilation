#include <stdio.h>
#include <conio.h>
#include <math.h>

/*=========================================================
Description: Handles the customer at night phase such as 
whether they are going to show up in a specific date and 
if the customers would leave

Parameters: nDays, fPrice, nPizza(pointers), nCustomers(pointers)
    nDays: to check if a how many customer would show up on that day
    fPrice: the price of pizza to get the total earnings in a night
    nPizza: the amount of pizza available for selling
    nCustomers: the amount of total customers that may appear
    nAmountOfPeopleCame: The amount of customers that actually came

Return value: the total earnings in a night
=========================================================*/
float handleCustomers(int nDays, float fPrice, int *nPizza, int *nCustomers, int *nAmountOfPeopleCame)
{
	/*variable declaration*/
	float fEarnedPizo = 0;
	int i;

	/*check if there is pizza for customers*/
	if (*nPizza == 0)
	{
		*nCustomers = 0;
		*nAmountOfPeopleCame = 0;
	}
	else
	{
		/*Count the total customers for a log later on*/
		for (i = 1; i <= *nCustomers; i++)
		{
			if (nDays % i == 0)
			{
				*nAmountOfPeopleCame += 1;
			}
		}

		/*gives pizza to customers if there are pizza and remove other customers if cannot be provided*/
		for (i = 1; i <= *nCustomers; i++)
		{
			/*gives pizza if there are pizza left*/
			if (*nPizza > 0)
			{
				if (nDays % i == 0)
				{
					*nPizza -= 1;
					fEarnedPizo += fPrice;
				}
			}

			/*Get out of loop*/
			else
			{
				if (nDays % i == 0)
				{
					*nCustomers = i - 1;
				}
			}
		}
	}

	/*Return Total earnings*/
	return fEarnedPizo;
}

/*=========================================================
Description: Manage the cooks at night such as checking if 
they would resign or not and the amount of salary they get

Parameters:
	nCooks: The total cooks
	fPizo: The total Pizo
	fCooksSalaries: The total salaries of every cook

Return value: since each cooks creates 1 pizza then total 
cooks left for the night will be the total pizza that's 
going to be created
=========================================================*/
int manageCooks(int *nCooks, float *fPizo, float *fCooksSalaries)
{
	/*Variable declaration*/
	float fCookSalary;

	/*Get value of the total salary of cooks for comparison*/
	fCookSalary = ((1 + *nCooks) / 2.00) **nCooks;

	/*Get rid of cooks if their salary is more than the pizo*/
	while (fCookSalary > *fPizo)
	{
		*nCooks -= 1;
		fCookSalary = ((1 + *nCooks) / 2.00) **nCooks;
	}

	/*Variable Update*/
	*fCooksSalaries += fCookSalary;
	*fPizo -= fCookSalary;
	/*Return total Pizza Made*/
	return * nCooks;
}

/*=========================================================
Description: Night Phase operations

Parameters:
	nDays: The current in game day
	nPizza: The total pizza
	fPizo: The total Pizo
	nCooks: The total Cooks
	nCustomers: The total customers
	fPrice: The price of a single pizza
	nSkipDays: The amount of days that is need to be skipped

Return value: none
=========================================================*/
void nightPhase(int *nDays, int *nPizza, float *fPizo, int *nCooks, int *nCustomers, float fPrice, int nSkipDays)
{
	/*variable declaration*/
	int nAmountOfPeopleCame = 0;
	int nTotalMadePizza 	= 0;
	int nTotalPizza 		= 0;
	float fPizoMade 		= 0;
	float fCookSalaries 	= 0;
	float fCooksSalaries 	= 0;
	float fTotalPizoMade 	= 0;
	
	int nResignedCooks, nRemainingCustomer, i;

	/*variable initialization*/
	nResignedCooks 		= *nCooks;
	nRemainingCustomer 	= *nCustomers;

	/*===========================================================
	night phase loops *depends on how many days would be skipped*
	===========================================================*/

	for (i = 1; i <= nSkipDays; i++)
	{
		/*creates a pizza proportional to the amount of cooks*/
		nTotalMadePizza = manageCooks(nCooks, fPizo, &fCooksSalaries);
		nTotalPizza += nTotalMadePizza;
		*nPizza += nTotalMadePizza;

		/*sells pizza*/
		fTotalPizoMade = handleCustomers(*nDays, fPrice, nPizza, nCustomers, &nAmountOfPeopleCame);
		fPizoMade += fTotalPizoMade;
		*fPizo += fTotalPizoMade;
		*nDays += 1;
	}

	/*Variable Update*/
	nResignedCooks = nResignedCooks - *nCooks;
	nRemainingCustomer = nRemainingCustomer - *nCustomers;
	/*===========================================================
							nightphase log
	===========================================================*/

	printf("====================================================\n");
	printf("||                   NIGHTPHASE                   ||\n");
	printf("====================================================\n");
	printf("The Cooks made a total of %d pizzas					\n", nTotalPizza);
	printf("You paid a total of %0.2f to the cooks as salary	\n", fCooksSalaries);
	printf("Your total sales is %0.2f Pizos from the night phase\n", fPizoMade);
	printf("Your net profit is %0.2f Pizos from the night phase \n", fPizoMade - fCooksSalaries);
	printf("A total of %d cooks Resigned						\n", nResignedCooks);
	printf("A total of %d People Came							\n", nAmountOfPeopleCame);
	printf("A total of %d Customers left due to no pizza		\n", nRemainingCustomer);
}

/*=========================================================
Description: handles overflow

Parameters:
	nCooks: The total cooks
	nCustomer: The total customer
	nPizza: The total pizza
	fPizo: the total pizo
	fPrice: the price of pizza

Return value: none
=========================================================*/
void dataHandler(int *nCooks, int *nCustomers, int *nPizza, float *fPizo, float *fPrice){
	if(*nPizza>999999){
		*nPizza=999999;
	}
	if(*fPizo>999999999.99){
		*fPizo=999999999.99;
	}
	if(*nCooks>999){
		*nCooks=999;
	}
	if(*nCustomers>999){
		*nCustomers=999;
	}
	if(*fPrice>999.99){
		*fPrice=999.99;
	}
}

int main()
{
	/*variable declaration*/
	/*game values*/
	int nCooks 		= 0;
	int nCustomers 	= 0;
	int nDays 		= 1;
	int	nPizza 		= 0;
	float fPizo 	= 0;
	float fPrice 	= 2.00;

	float 	fCookSalary, fResearchMoney;
	int 	nAction, nSkipDays, nStopDay;

	/*program runners*/
	int nRunner 	= 1;

	/*loop to make it run as long as you dont press exit*/
	while (nRunner 	== 1 && nDays<999)
	{
		/*initialization for each day*/
		nSkipDays 	= 1;
		nStopDay 	= 0;

		/*print statements*/
		printf("====================================================\n");
		printf("||                    Stats Menu                  ||\n");
		printf("====================================================\n");
		printf("Day: %d				\n", nDays);
		printf("Pizza: %d			\n", nPizza);
		printf("Pizo: %0.2f			\n", fPizo);
		printf("Cooks: %d			\n", nCooks);
		printf("Customers: %d		\n", nCustomers);
		printf("Pizza Price: %0.2f	\n", fPrice);
		printf("====================================================\n");
		printf("||                   Action Menu                  ||\n");
		printf("====================================================\n");
		printf("1. Make a Pizza				\n");
		printf("2. Sell a Pizza				\n");
		printf("3. Hire a Cook				\n");
		printf("4. Attract a Customer		\n");
		printf("5. Research Pizza Quality	\n");
		printf("6. Skip x days				\n");
		printf("7. Exit						\n");
		printf("Pick an action: ");

		/*scan action*/
		scanf("%d", &nAction);
		system("cls");

		/*print log title*/
		printf("====================================================\n");
		printf("||                      LOGS                      ||\n");
		printf("====================================================\n");

		/*look at the action to take*/
		switch (nAction)
		{
			case 1:	/*make a pizza*/
				nPizza++;
				printf("you made a pizza!\n");
				break;

			case 2:	/*sell a pizza*/
				if (nPizza > 0)
				{
					fPizo += fPrice;
					nPizza--;
					printf("you sold a pizza!\n");
				}
				else
				{
					printf("No changes, You don\'t have enough pizza!\n");
					nStopDay = 1;
				}

				break;

			case 3:	/*hire cooks*/
				nCooks++;
				fCookSalary = ((1 + nCooks) / 2.00) *nCooks;
				if (fPizo < fCookSalary || fPizo == 0)
				{
					nCooks--;
					printf("Can't hire a cook\n");
					nStopDay = 1;
				}
				else
				{
					printf("you hired a cook!\n");
				}

				break;

			case 4:	/*attract customers*/
				nCustomers++;
				printf("you attracted a customer!\n");
				break;

			case 5:	/*Research Pizza Quality*/
				printf("How much would you invest for research: ");
				scanf("%f", &fResearchMoney);
				if (sqrt(fResearchMoney) <= fPrice)
				{
					printf("No changes, Pizza Quality would not increase\n");
					nStopDay = 1;
				}
				else if (fResearchMoney < 0)
				{
					printf("No changes, Please input a valid amount\n");
					nStopDay = 1;
				}
				else
				{
					if (fPizo >= fResearchMoney)
					{
						fPizo -= fResearchMoney;
						fPrice = sqrt(fResearchMoney);
						printf("your pizza price increased by %0.2f\n", sqrt(fResearchMoney));
					}
					else
					{
						printf("No changes, you don\'t have enough money\n");
						nStopDay = 1;
					}
				}

				break;

			case 6:	/*skip days*/
				printf("How many days to skip: ");
				scanf("%d", &nSkipDays);
				while(nSkipDays<0){
					printf("(Put Valid Amount)How many days to skip: ");
					scanf("%d", &nSkipDays);
				}
				if(nSkipDays+nDays>999){
					nSkipDays=999-nDays;
				}
				printf("you skipped %d days\n", nSkipDays);
				nightPhase(&nDays, &nPizza, &fPizo, &nCooks, &nCustomers, fPrice, nSkipDays);
				nStopDay = 1;
				break;

			case 7:	/*Stops the game*/
				nRunner = 0;
				break;

			case 10: /*game customization*/
				printf("====================================================\n");
				printf("||                Game Customization              ||\n");
				printf("====================================================\n");

				printf("Starting Day: ");
				scanf("%d", &nDays);
				while (nDays < 0 || nDays>999)
				{
					printf("Please Input a proper Starting Day: ");
					scanf("%d", &nDays);
				}

				printf("\nStarting Pizza Count: ");
				scanf("%d", &nPizza);
				while (nPizza < 0 || nPizza>999999)
				{
					printf("Please Input a proper Pizza Count: ");
					scanf("%d", &nPizza);
				}

				printf("\nStarting Pizo Count: ");
				scanf("%f", &fPizo);
				while (fPizo>1000000000.00){
					printf("Please Input a proper Pizo Count: ");
					scanf("%f", &fPizo);	
				}

				printf("\nStarting Cooks Count: ");
				scanf("%d", &nCooks);
				while (nCooks < 0 || nCooks>999)
				{
					printf("Please Input a proper Cooks Count: ");
					scanf("%d", &nCooks);
				}

				printf("\nStarting Customer Count: ");
				scanf("%d", &nCustomers);
				while (nCustomers < 0 || nCustomers>999)
				{
					printf("Please Input a proper Customer Count: ");
					scanf("%d", &nCustomers);
				}

				printf("\nStarting Pizza Price: ");
				scanf("%f", &fPrice);
				while (fPrice < 0 || fPrice>999.99)
				{
					printf("Please Input a proper Customer Count: ");
					scanf("%f", &fPrice);
				}

				nStopDay = 1;
				system("cls");
				break;

			default: /*Error Input*/
				printf("Input was not understood please select an action\n");
				nStopDay = 1;
				break;
		}

		/*night phase--automated*/
		if (nStopDay == 0)
		{
			nightPhase(&nDays, &nPizza, &fPizo, &nCooks, &nCustomers, fPrice, nSkipDays);
		}
		
		/*data overflow handler*/
		dataHandler(&nCooks, &nCustomers, &nPizza, &fPizo, &fPrice);
	}

	system("cls");

	printf("====================================================\n");
	printf("||                 Final Stats Menu               ||\n");
	printf("====================================================\n");
	printf("Day: %d\n"				, nDays);
	printf("Pizza: %d\n"			, nPizza);
	printf("Pizo: %0.2f\n"			, fPizo);
	printf("Cooks: %d\n"			, nCooks);
	printf("Customers: %d\n"		, nCustomers);
	printf("Pizza Price: %0.2f\n"	, fPrice);
	printf("====================================================\n");
	printf("||              Thank you for playing!            ||\n");
	printf("====================================================\n");
}
