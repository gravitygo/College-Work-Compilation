/*12041602, Chyle Andrei A. Lee (S14A)*/

#include <stdio.h>
int tactic4(int * nMoney){
	int nHundred=*nMoney%1000, nThousand;
	if(*nMoney>999999){
		printf("1,000,000");
	}else{
		nThousand=(*nMoney%1000000-nHundred)/1000;
	
		printf("%d,%d", nThousand,nHundred );
	}
	
}

int tactic3(int * nMoney){
	*nMoney+=1;
}
int tactic2(int * nMoney){
	int nChecker=*nMoney%10;
	int nNineMaker;
	if(nChecker>=4){
		nNineMaker=*nMoney%10-9;
	}else{
		*nMoney-=4;
		nNineMaker=*nMoney%10-9;
	}
	*nMoney-=nNineMaker;
}
int tactic1(int * nMoney){
	int nMultiplier;
	nMultiplier= *nMoney/5;
	if (*nMoney%5!=0){
		nMultiplier++;
	}
	*nMoney=nMultiplier*5;
}
int main(){
	int nMoney;
	
	
	printf("input integer: ");
	scanf("%d", &nMoney);
	if(nMoney<=25){
		tactic1(&nMoney);
	}else{
		if(nMoney%10%9!=0){
			tactic2(&nMoney);
		}
		if((nMoney+1)%1000==0){
			tactic3(&nMoney);
		}
	}
	if(nMoney>9999){
		tactic4(&nMoney);
	}else{
		printf("%d", nMoney);
	}
}
/*===============================================================================
provide integer from 1 to 999999

tactic 1(seperate)
if price<=25 then round to nearest 5

tactic 2
if price ends with >=4 then round to the nearest 9 above
if price ends with <=3 then round to the nearest 9 below

tactic 3
if peso++ will have 3 zeroes then add else dont

tactic 4 
if peso has more than 4 digits then add comma else dont
===============================================================================*/
