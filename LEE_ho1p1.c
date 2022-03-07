/*12041602, Chyle Andrei A. Lee (S14A)*/

#include <stdio.h>

int computeParkingFee(int nHour){
	int nParkingFee=40;
	int nHourLeft;
	
	if(nHour>4){
		nHourLeft=nHour-4;
		nParkingFee+=nHourLeft*50;
	}
	
	return nParkingFee;
}

int customerChargedTime(int nTimeIn, int nTimeOut){
	int nHour;
	
	nHour=nTimeOut-nTimeIn;
	
	if (nHour%100!=0)
		nHour=nHour/100 + 1;
	else
		nHour/=100;
		
	printf("Hours Charged: %d\n", nHour);
	
	return computeParkingFee(nHour);
}
int main(){
	int nTimeIn, nTimeOut;
	
	printf("time in and time out in format (0000, 2359): ");
	scanf("%d, %d", &nTimeIn, &nTimeOut);
	printf("Parking Fee: %d", customerChargedTime(nTimeIn, nTimeOut));
}
/*===============================================================================
contains 2 function
computeParkingFee(based on the time in and time out military format)
customer's charged time rounded up to the nearest hour and the amount to be paid
assumes that time is correct
time in is always <= time out
no overnight parking i.e no next day
<=4hrs== 40 pesos
succeeding hours +50
===============================================================================*/
