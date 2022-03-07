/* 12041602, Chyle Andrei Lee and S14-A */

#include <stdio.h>

void chow(int nHand){
	int notYetDetected=1, nDig, nTemp;
	while(notYetDetected && nHand>0){
		nTemp=nHand;
		nDig=nHand%10;
		nTemp/=10;
		while(nTemp%10==nDig){
			nTemp/=10;
		}
		if(nTemp%10+1 ==nDig){
			nDig=nTemp%10;
			nTemp/=10;
			while(nTemp%10==nDig){
				nTemp/=10;
			}
			if(nTemp%10+1==nDig){
				printf("Chow!\n");
				notYetDetected=0;
			}
		}
		nHand/=10;
	}
}

void pung(int nHand){
	int notYetDetected=1;
	while(notYetDetected && nHand>=100){
		if(nHand%1000%111==0){
			printf("Pung!\n");
			notYetDetected=0;
		}
		nHand/=10;
	}
}
void kung(int nHand){
	int notYetDetected=1;
	while(notYetDetected && nHand>=1000){
		if(nHand%10000%1111==0){
			printf("Kung!\n");
			notYetDetected=0;
		}
		nHand/=10;
	}
}


int main()
{
	int nHand;
	printf("Enter A Hand: ");
	scanf("%d", &nHand);	
	chow(nHand);
	pung(nHand);
	kung(nHand);
	return 0;
}
