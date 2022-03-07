/********************************************************************************************************* 
This is to certify that this 
project is my own work, based on my personal efforts in studying and applying the concepts learned. I have constructed 
the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and 
debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of 
other students and/or persons.
 Chyle Andrei Antonio Lee, DLSU ID# 12041602
************************************** *******************************************************************/
#include "trivia.h"
#include <stdlib.h>

#define OBJLEN 29 //"Object: " + answer +\n
#define RELLEN 63 //Relation + ": " + relationValue + \n

typedef char fStrWord[OBJLEN + 1];
typedef char fStrPhrase[RELLEN + 1]; 

/* Displays the clues with numbers on the side from 1 to the total clues

	@param aList - the list of all clues
	@param numClues - the amount of clues in the list
*/
void
displayCluesWithNumber(arrClues aList, int numClues)
{
	int i;
	for(i=0; i<numClues; i++){
		printf("%d %s: %s\n", i+1, aList[i].relation, aList[i].relValue);
	}
}

/* Deletes a clue using the index

	@param oneEntry - just one entry of a trivia to be process
*/
void
deleteClue(struct triviaTag * oneEntry){
	int	index;
	int	i;
	char	dump;
	displayCluesWithNumber(oneEntry->clueList, oneEntry->numClues);
	do{
		scanf("%d%c", &index, &dump);
	}while(index<1 || index > oneEntry->numClues);
	if(oneEntry->numClues>1){
		oneEntry->numClues--;
		for(i=index-1; i<oneEntry->numClues; i++){
			oneEntry->clueList[i]=oneEntry->clueList[i+1];
		}
	}else
		printf("Only 1 clue left, can't delete.\n");
}

/* Checks if the relation is unique

	@param clueList - List of clues
	@param clue - the clue to be checked(both rel and relvalue is contained here)
	@param numClues - total clues in the list
	@return the index where relation was found, -1 otherwise
*/
int isRelUnique(arrClues clueList, struct clueTag clue, int numClues){
	int i;
	for(i=0; i<numClues; i++){
		if(!strcmp(clueList[i].relation, clue.relation)){
			if(!strcmp(clueList[i].relValue,clue.relValue))
				return i;
		}
	}
	return -1;
}

/* Display a row of the board

	@param row - an array of the current row
	@param nCols - the amount of column per row
*/
void
displayRow(char row[], int nCols){
	int i;
	for(i=0; i<nCols; i++)
		printf("%c ", row[i]);
	printf("\n");
}

/* Change all alphabets to uppercase

	@param answer - The string to be processed
*/
void
toUpper(strWord answer){
	int i;
	int len=strlen(answer);
	for(i=0; i < len; i++){
		if(answer[i]>='a' && answer[i]<='z')
			answer[i]=answer[i]-'a'+'A';
	}
}

/* This function loads the clues and the clue type for each answer
 
	@param aEntries - the list of all entries and its values
	@param cElem - the current answer element of the clues
	@param fp - the file that has been opened
*/
void 
addRels(wordList aEntries, int cElem, FILE *fp)
{
	int		cCurrent;
	int		sLength=0;
	int		i=0;
	struct	clueTag temp;

	fStrPhrase relate;
	fStrPhrase enter = "\n";

	aEntries[cElem].numClues = 0;//initialize available hints
	
	while(fgets(relate, RELLEN + 1, fp) && 
			strcmp(relate, enter) && 
			aEntries[cElem].numClues < MAX)//put the rel and relvalue in one string, scan while its not "\n", and check if the count of relation is less than 10
	{
		//reinitialize variable every loop
		i=0;
		sLength=strlen(relate);
		cCurrent=0;

		//put character to relation type until ": "
		do{
			//aEntries[cElem].clueList[aEntries[cElem].numClues].relation[cCurrent] = relate[cCurrent];
			temp.relation[cCurrent]=relate[cCurrent];
			cCurrent++;
		}while(relate[cCurrent]!=':' || relate[cCurrent + 1]!=' '); 
			
		//aEntries[cElem].clueList[aEntries[cElem].numClues].relation[cCurrent]='\0';
		temp.relation[cCurrent]='\0';

		cCurrent+=2; //to skip the ':' and ' '

		//put character to relation value until "\n"
		do{
			//aEntries[cElem].clueList[aEntries[cElem].numClues].relValue[i] = relate[cCurrent];
			temp.relValue[i] = relate[cCurrent];
			cCurrent++;
			i++;
		}while(cCurrent<sLength);
		//set the last from "\n" to "\0"
		//aEntries[cElem].clueList[aEntries[cElem].numClues].relValue[i-1]='\0';
		temp.relValue[i-1]='\0';
		toUpper(temp.relation);
		toUpper(temp.relValue);

		//counts the total trivias added
		if(isRelUnique(aEntries[cElem].clueList, temp, aEntries[cElem].numClues)==-1){
			aEntries[cElem].clueList[aEntries[cElem].numClues]=temp;
			aEntries[cElem].numClues++;
		}
	}
	if(aEntries[cElem].numClues==MAX && strcmp(relate, enter)){
		while(fgets(relate, RELLEN + 1, fp) && 
			strcmp(relate, enter)){}
	}
}

/* Displays the game board in the screen

	@param gameboard - the gameboard to be displayed
	@param nRows - the amount of rows to display
	@param nCols - the amount of columns to display
*/
void
displayMatrix(arrMatrix gameboard, int nRows, int nCols){
	int i;

	for(i=0; i<nRows; i++){
		displayRow(gameboard[i], nCols);
	}
}

/* Returns the amount of entries that can be initialized without
	having more than 1 repetative character in a row.
 
	@param aEntries - place to check all the first characters
	@param nElem - The amount of elements in aEntries
	@param nRows - The amount of row of the matrix since that is 
						the max amount per character
	@return the max initiable entries with the given board.
*/
int 
totalInitialable(wordList aEntries, int nElem, int nRows){
	int aToz[128];
	int i;
	int total=0;
	//128 to represent all ascii value
	for(i=0; i<128; i++)
		aToz[i]=0;

	for(i=0; i<nElem; i++){
		if(aToz[(int)aEntries[i].answer[0]] < nRows)
			aToz[(int)aEntries[i].answer[0]]++;
	}
	for(i=1; i<128; i++){
		total+=aToz[i];
	}
	return total;
}

/* Returns the index of a letter choice in a row and returns -1 if
	it doesn't exist in the row
 
	@param row - A row from the gameboard
	@param nCols - The amount of columns in a row
	@param key - The character that needs to be found in the row
	@return the index of the key or -1 if it doesn't exist.
*/
int
letterRow(char row[], int nCols, char key){
	int i;
	for(i=0; i<nCols; i++){
	  if(row[i]==key)
		return i;  
	}
	return -1;
}

/* Returns the index of an entry to be used on the matrix
 
	@param aEntries - place where to find the entry
	@param nElem - The amount of elemnt in the wordList
	@param matrixIndex - the 1d array value of a specific location in the matrix
	@return the index of the entry to be used on the matrix or -1 if entry doesnt exist.
*/
int
entryIndex(wordList aEntries, int nElem, int matrixIndex){
	int i;	
	for(i=0; i < nElem; i++){
		if(aEntries[i].use==matrixIndex)
			return i;
	}
	return -1;
}

/* This function sorts the entries using quicksort, quicksort
	uses a pivot and sort it. Comparing the pivot value with all index
	until the index is equal to the last value or when the index's value
	is greater than the pivot's value. Then it loops reducing j again and again 
	while its a value that is bigger than the pivot's value. switches the small value
	to the larger value then repeats until the small and large index is the same.
	switch the pivot and biggest value and then call the sort again to induce
	recurssion.

	@param aEntries - the array of words with the corresponding clues
	@param small - lowest index
	@param big - highest possible index
*/
void 
sorterRecurssion(wordList aEntries, int small, int big){
	struct triviaTag temp;
	int i;
	int j;
	int pivot;

	//check first if the small parameter is smaller than the big parameter
	if(small<big){
		pivot=small;
		i=small;
		j=big;

		while(i<j){
			while(strcmp(aEntries[i].answer,aEntries[pivot].answer)<1 && i<big) 
				i++;
			while(strcmp(aEntries[j].answer,aEntries[pivot].answer)==1)
				j--;
			if(i<j){
				temp=aEntries[i];
				aEntries[i]=aEntries[j];
				aEntries[j]=temp;
			}
		}
		//switch pivot and biggest value
		temp=aEntries[pivot];
		aEntries[pivot]=aEntries[j];
		aEntries[j]=temp;

		//recurssion till all is sorted
		sorterRecurssion(aEntries, small, j-1);//left side
		sorterRecurssion(aEntries, j+1, big);//right side
	}
}

/* Scan for the trivia's relation and relValue until a 
	\n or the length of answer is greater than
	sizeof(strPhrase).
 
	@param temp - updatable value for the relations
*/
void
scanTrivia(struct clueTag * clue){
	int i=0;
	printf("Input Type of Clue: ");
	do{
		scanf("%c", &clue->relation[i]);
		if(clue->relation[0]=='\n'){
			printf("Input a relation:");
			i--;
		}
		i++;
	}while(i<=1||(clue->relation[i-1]!='\n' && i<=LEN2));
	clue->relation[i-1]='\0';

	i=0;
	printf("Input Clue: ");
	do{
		scanf("%c", &clue->relValue[i]);
		if(clue->relValue[0]=='\n'){
			printf("Input a relation value:");
			i--;
		}
		i++;
	}while(i<=1||(clue->relValue[i-1]!='\n' && i<=LEN2));
	clue->relValue[i-1]='\0';

	toUpper(clue->relation);
	toUpper(clue->relValue);
}

/* Scan for the answer until a \n or the length of answer is greater than
	sizeof(strWord).
 
	@param answer - updatable value for answer parameter
*/
void 
scanAnswer(strWord answer){
	int i=0;

	do{
		scanf("%c", &answer[i]);
		if(answer[0]=='\n'){
			printf("Input value:");
			i--;
		}
		i++;
	}while(i<=1 || (answer[i-1]!='\n' && i <= LEN1));
	answer[i-1]='\0';

	toUpper(answer);
}

/* Modification of a new unique word
 
	@param aEntries - the list of entries to be modified
	@param nElem - total number of entries
	@param index - index of the word to be modified
*/
void 
modifyWord(wordList aEntries, int nElem, int index){
	strWord modified;
	fStrPhrase error;
	strcpy(error, "");
	do{
		printf("%s\n", error);
		printf("Modified Word:");
		scanAnswer(modified);
		strcpy(error, "Value should be unique\n");
	}while(searchWord(modified, aEntries, nElem)!=-1);
	strcpy(aEntries[index].answer, modified);
	printf("Modified Successfully\n");
}
/*=============defined functions after this line=================*/

/* Given the filename stored in fname, this function
	loads the entries of the text file and ADDS them to
	the array aEntries. The number of elements should be
	updated in pElem. For each trivia word in the file 
	that already exists in aEntries, the user is asked if 
	he wants to keep the one in the array or replace it 
	with the one from the text file.
 
	@param fname - the string filename, including the extension
	@param aEntries - the array of words with the corresponding clues
	@param pElem - the address where the number of elements are 
						to be updated
*/
void
import(strWord fname, wordList aEntries, int * pElem)
{
	int YN;
	char dump;
	*pElem=0;
	fStrWord answer;
	fStrPhrase  temp;
	int index;
	FILE *fp = fopen(fname, "r"); //open file as read
	if(fp){
		while(fgets(answer, OBJLEN + 1, fp)!=NULL && 
				* pElem < CAP) //get the answer and check if elements is less than 150
		{
			answer[strlen(answer)-1]='\0';// MOVE THE NULL BYTE TO GET RID OF \n

			toUpper(answer);

			index = searchWord(answer + 8, aEntries, * pElem);

			if(index==-1){
				strcpy(aEntries[*pElem].answer, answer + 8);
				addRels(aEntries, * pElem, fp);
				aEntries[*pElem].use=-1;
				*pElem+=1; 
			}
			else{
				printf("The word is in the entry list already do you want to overwrite? Type \'1\' if yes type \'0\' if no: ");
				do{
					scanf("%d%c", &YN, &dump);
					if(YN!=1 || YN!=0)
						printf("Please input a valid value: ");
				}while(YN!=1 || YN!=0);
				
				if(YN==1){
					strcpy(aEntries[index].answer, answer + 8);
					addRels(aEntries, index, fp);
				}else{
					while(fgets(temp, RELLEN + 1, fp) && 
					strcmp(temp, "\n"))//put the rel and relvalue in one string, scan while its not "\n".
					{}

				} 
			}		
		}
		fclose(fp); //close the file
		printf("Import done! \nPress Enter to continue...");
		scanf("%c", &dump);
	}else{
		fclose(fp); //close the file
		printf("File doesn't Exists.\n");
	}
}

/* This function initializes the gameboard with nRows by
	nCols number of characters based on the contents of 
	aEntries.  The use member field is also updated to
	signify that this entry is already used in the board
	for the current game.  The function returns 1 if the
	board can be fully initialized with unique entries based
	on the needed dimension. Otherwise, the function returns 0.

	@param gameboard - 2D array of characters containing the
							 first letters of the answer
	@param nRows - the number rows to be initialized in gameboard
	@param nCols - the number columns to be initialized in gameboard
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
	@return 1 if successful initialization of the gameboard, 0 otherwise
*/
int 
initBoard	(arrMatrix gameboard, int nRows, int nCols,
				wordList aEntries, int nElem)
{
	int total= nRows * nCols;
	int i,j;
	int curr=0;
	int rnd;
	int row, col;
	int tElem=totalInitialable(aEntries, nElem,  nRows);

	for(i=0; i<nRows; i++){
		for(j=0; j<nCols; j++)
			gameboard[i][j]=' ';
	}
	
	if(tElem>=total){
		srand(time(NULL));
		while(total){
			rnd=rand() % nElem;
			row=curr/nCols;
			col=curr%nCols;
			if(aEntries[rnd].use==-1 && total>0 && letterRow(gameboard[row], nCols, aEntries[rnd].answer[0])==-1){
				gameboard[row][col]=aEntries[rnd].answer[0];
				aEntries[rnd].use=curr;
				curr++;
				total--;
				srand(time(NULL)); //implemented srand here to avoid looping problems
			}
		}
		return 1;
	}
	printf("Board Can't be initialized. Try a Different Input\n");
	return 0;
}

/* This function facilitates the game play of the user,
	including determining when the game ends. 
	
	@param gameboard - the 2D array of characters
	@param nRows - the number of rows in gameboard
	@param nCols - the number of columns in gameboard
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries	
*/	
void 
play(arrMatrix gameboard, int nRows, int nCols,
			 wordList aEntries, int nElem)
{
	int i;
	int row=0;
	int curr;
	int rnd;
	char in;
	char dump;
	int lose=0;
	fStrWord answer;
	int currMatrixIndex;
	int currEntryIndex=-1;
	strWord repeat="";
	int rowIsDone[MAX];
	for(i=0; i<nCols; i++){
		rowIsDone[i]=0;
	}
	while(lose<nCols && row<nRows){
		printf("=======================\n");
		printf("BOARD\n");
		printf("=======================\n");
		displayMatrix(gameboard, nRows, nCols);
		printf("=======================\n");
		printf("CHOOSE FROM THESE LETTERS\n");
		printf("=======================\n");
		displayRow(gameboard[row], nCols);
		strcpy(repeat,"");
		do{
			i=0;
			printf("%s", repeat);
			scanf("%c%c", &in, &dump);
			curr= letterRow(gameboard[row], nCols, in);
			if(curr != -1 && rowIsDone[curr]){
				i=1;
			}
			strcpy(repeat,"Please a Valid Value: ");
		}while(curr==-1 || i);
		
		if(curr>-1){
			currMatrixIndex=row*nCols+curr;
			currEntryIndex=entryIndex(aEntries, nElem, currMatrixIndex);
			rnd=rand() % aEntries[currEntryIndex].numClues;
			printf("%s: %s\n",aEntries[currEntryIndex].clueList[rnd].relation, aEntries[currEntryIndex].clueList[rnd].relValue);
			printf("Answer: ");
			scanAnswer(answer);

		}
		if(!strcmp(answer,aEntries[currEntryIndex].answer)){
			printf("Correct\n");
			gameboard[row][curr]='*';\
			lose=0;
			for(i=0; i<nCols; i++){
				rowIsDone[i]=0;
			}
			row++;
		}else{
			printf("Incorrect\n");
			gameboard[row][curr]='-';
			rowIsDone[curr]=1;
			lose++;
		}
		printf("The answer is: %s\n", aEntries[currEntryIndex].answer);
	} 
	if(lose==nCols){
		printf("You Lost\n");
	}else{
		printf("You Won\n");
	}
	printf("Final Board:\n");
	displayMatrix(gameboard, nRows, nCols);
	printf("=====================================\n");
}

/* This function shows the menu options in the maintenance
	phase as well as call the functions (like listWords(), 
	addWord(), etc.) that are relevant to the chosen option.	
*/
void 
maintenance()
{
	int opt=0;
	char cDump;
	wordList aEntries;
	int nElem = 0;
	int index=0;
	strWord fname;
	do
	  {
		printf("=====Maintenance=====\n");
		printf("1 - Add Word\n");
		printf("2 - Add Trivia\n");
		printf("3 - Modify Word\n");
		printf("4 - Modify Clues\n");
		printf("5 - Delete Word\n");
		printf("6 - Delete Clue\n");
		printf("7 - View Words\n");
		printf("8 - View Clues\n");
		printf("9 - Export\n");
		printf("10 - Import\n");
		printf("11 - Exit\n");
	
		scanf("%d%c", &opt, &cDump);
		printf("===========================\n");
		switch (opt){
			case 1: //ADD WORD
				addWord(aEntries, & nElem);
				break;
			case 2: //ADD TRIVIA TO A WORD
				printf("Object: ");
				scanAnswer(fname);
				index=searchWord(fname, aEntries, nElem);
				if(index==-1)
					printf("Object not found\nReturning to Maintenance\n");
				else
					addTrivia(&aEntries[index]);
				printf("===========================\n");
				break;
			case 3: //MODIFY A WORD
				sortEntries(aEntries, nElem);
				listWords(aEntries,nElem);
				printf("Object: ");
				scanAnswer(fname);
				index=searchWord(fname, aEntries, nElem);
				if(index==-1)
					printf("Object not found\nReturning to Maintenance\n");
				else
					modifyWord(aEntries, nElem, index);
				printf("===========================\n");
				break;
			case 4: //MODIFY CLUES
				sortEntries(aEntries, nElem);
				listWords(aEntries,nElem);
				printf("Object: ");
				scanAnswer(fname);
				index=searchWord(fname, aEntries, nElem);
				if(index==-1)
					printf("Object not found\nReturning to Maintenance\n");
				else
					modifyEntry(&aEntries[index]);
				printf("===========================\n");

				break;
			case 5: //DELETE AN ENTRY ENTIRELY
				sortEntries(aEntries, nElem);
				listWords(aEntries,nElem);
				deleteWord(aEntries, &nElem);
				break;
			case 6: //DELETE A CLUE
				if(nElem>0){
					sortEntries(aEntries, nElem);
					listWords(aEntries,nElem);
					do{
						printf("Object: ");
						scanAnswer(fname);
						index=searchWord(fname, aEntries, nElem);
					}while(index==-1);
					deleteClue(&aEntries[index]);
				}else{
					printf("No entries.\nReturning to Maintenance\n");
				}
				break;
			case 7: //VIEW WORDS
				sortEntries(aEntries, nElem);
				listWords(aEntries,nElem);
				viewWords(aEntries,nElem);
				break;
			case 8: //VIEW CLUES OF A SPECIFIC WORD
				sortEntries(aEntries, nElem);
				listWords(aEntries,nElem);
				printf("Object: ");
				scanAnswer(fname);
				index=searchWord(fname, aEntries, nElem);
				if(index==-1)
					printf("Object not found\nReturning to Maintenance\n");
				else
					displayAllClues(aEntries[index].clueList, aEntries[index].numClues);
				printf("===========================\n");
				break;
			case 9: //EXPORT
				printf("Enter filename for export: ");
				scanAnswer(fname);
				export(fname, aEntries, nElem);
				break;
			case 10: //IMPORT
				printf("Enter filename for source of trivia: ");
				scanAnswer(fname);
				import(fname, aEntries, &nElem);
				break;
			case 11: //EXIT
				break;
			default: printf("Invalid option\n");
				
		}
	}while(opt != 11);
}

/* This function returns the index where the key was found
	in aEntries. If not found, the function returns -1.
	
	@param key - the word or phrase to look for
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
	@return the index where key was found, -1 otherwise
*/
int 
searchWord(strWord key, wordList aEntries, int nElem)
{
	int i;
	for(i=0; i<nElem; i++){
		if(!strcmp(key, aEntries[i].answer))
			return i;
	}
	return -1;
}

/* This function displays the list of words (without the clues)
	in aEntries. 
	
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
*/ 
void 
listWords(wordList aEntries, int nElem)
{
	int i;
	if(nElem==0)
		printf("No words\n");
	for(i=0; i<nElem; i++)
		printf("%s\n", aEntries[i].answer);
	printf("==================================\n");
}

/* This function will ask the user to input the word, calls
	searchWord() to check if the word is unique.  If unique, this
	word is added, the addTrivia() is called, and the
	number of elements is updated. Other error checking (as 
	indicated in the MP specs requirements) are also done.

	@param aEntries - the array of words with the corresponding clues
	@param pElem - the address where the number of elements are 
						to be updated
*/
void 
addWord(wordList aEntries, int * pElem)
{
	strWord word;
	fStrPhrase repeat;
	strcpy(repeat,"");
	if(*pElem<CAP){
		do{
			printf("%s", repeat);
			printf("Input Unique Word: ");
			scanAnswer(word); 
			strcpy(repeat,"Not a unique word! Please ");
		}while(searchWord(word, aEntries, *pElem)>-1);

		strcpy(aEntries[*pElem].answer, word);
		aEntries[*pElem].numClues=0;
		addTrivia(&aEntries[*pElem]);
		* pElem = * pElem+1;  
	}else
		printf("entries are full\n");
	printf("==================================\n");
}

/* This function will ask the user for the relation and
	relation value as store it in the clueList member field
	in *oneEntry, as long as the array can still accommodate
	more data and as long as the user still wants to add
	more entries. If there are existing clues already, new
	entries are added (not overwritten). The member field
	numClues is also updated.

	@param oneEntry - address to the structure containing the
							array of clues and the number of clues,
							among other data
*/
void 
addTrivia(struct triviaTag * oneEntry)
{
	int YN=1;
	char dump;
	struct clueTag temp;

	if(oneEntry->numClues<MAX){
		while(oneEntry->numClues < MAX && YN){
			scanTrivia(&temp);

			if(isRelUnique(oneEntry->clueList, temp, oneEntry->numClues)==-1){
				strcpy(oneEntry->clueList[oneEntry->numClues].relation, temp.relation);
				strcpy(oneEntry->clueList[oneEntry->numClues].relValue, temp.relValue);
				oneEntry->numClues++;
			}
			else{
				printf("The trivia is already in the set.\n");
			}
			if(oneEntry->numClues==MAX)
				printf("Sorry clues are full");
			else{
				printf("Would you like to add another clue? Type \'1\' if yes type \'0\' if no: ");
				do{
					scanf("%d%c", &YN, &dump);
					if(YN!=1 || YN!=0)
						printf("Please input a valid value: ");
				}while(YN!=1 || YN!=0);
			}
		}
	}else
		printf("clues are full");
	printf("==================================\n");
}

/* This function will ask the user for which part of the
	information in *oneEntry that will be modified (word or
	clue). The required input, including appropriate error
	checking as indicated in the specs, is done in this
	function.  The user is allowed to modify multiple parts
	of *oneEntry, until the user chooses to finish the 
	editing. For the clues, only modification can be done.
	That is, deletion or addition is not allowed here.

	@param oneEntry - address to the structure containing the
							words, array of clues and the number of clues,
							among other data
*/
void 
modifyEntry(struct triviaTag * oneEntry)
{
	int opt;
	int index;
	strWord mWord;
	char dump;
	struct clueTag temp;
	do{
		printf("Modify (%s)\n", oneEntry->answer);
		printf("1 - Trivia\n");
		printf("2 - Exit modification\n");
		scanf("%d%c", &opt, &dump);
		switch(opt){
			case 1:
				printf("==================================\n");
				displayCluesWithNumber(oneEntry->clueList, oneEntry->numClues);
				strcpy(mWord,"");

				do{
					scanf("%d%c", &index, &dump);
				}while(index<1 || index > oneEntry->numClues);

				strcpy(mWord,"");
				do{
					printf("Value Replacement\n");
					printf("%s", mWord);
					scanTrivia(&temp);
					strcpy(mWord, "Relation Already Exist\n");
				}while(isRelUnique(oneEntry->clueList, temp, oneEntry->numClues)>-1);
				strcpy(oneEntry->clueList[index-1].relation, temp.relation);
				strcpy(oneEntry->clueList[index-1].relValue, temp.relValue);
				break;
			case 2:
				break;
			default:
				printf("Invalid Input!");
				break;
		}
	}while(opt!=2);
}

/* This function will ask the user to input the word (or phrase)
	that will be deleted.  Calls to other functions, like 
	searchWord(), as needed by the function, will be done.
	If deletion is successful (i.e., the word was found), the
	number of elements in pElem should also be updated.

	@param aEntries - the array of words with the corresponding clues
	@param pElem - the address where the number of elements are 
						to be updated
*/
void 
deleteWord(wordList aEntries, int *pElem)
{
	int index, i;
	strWord object;
	fStrPhrase error;
	strcpy(error, "");
	if(*pElem>0){
		do{
			printf("Object: ");
			scanAnswer(object);
			index=searchWord(object, aEntries, *pElem);
			strcpy(error, "Please input existing ");
		}while(index==-1);

		*pElem = *pElem-1;

		for(i=index; i<*pElem; i++){
			aEntries[i]=aEntries[i+1];
		}
	}else
		printf("Can't Delete, No entries.\n");
	
}

/* This function displays all information per element in aEntries.
	Part of the solution is to call the other function/s, like 
	viewEntry(), as needed by the function.
 
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
*/
void 
viewWords(wordList aEntries, int nElem)
{
	int i=0;
	char opt, dump;
	if(nElem>0){
		do{
			viewEntry(aEntries[i]);
			printf("N - NEXT\n");
			printf("P - PREVIOUS \n");
			printf("X - EXIT \n");
			scanf("%c%c", &opt, &dump);

			switch(opt){
				case 'N':
					if(i<nElem-1){
						i++;
					}else{
						printf("Last Entry\n");
					}
					break;
				case 'P':
					if(i>0){
						i--;
					}else{
						printf("First Entry\n");
					}
					break;
				case 'X':
					break;
				default:
					printf("Invalid Input\n");
					break;
			}
		}while(opt!='X');
	}
}

/* This function displays all information in entry.
	Part of the solution is to call the other function/s, like 
	displayAllClues(), as needed by the function.
 
	@param entry - structure containing the word and the clues, 
						among other data
*/
void
viewEntry(struct triviaTag entry)
{
	printf("Object: %s\n", entry.answer);
	printf("==========================\n");
	displayAllClues(entry.clueList, entry.numClues);
}

/* This function displays numClues number of elements from aList.

	@param aList - array of relation and relation values
	@param numClues - number of elements in aList
*/
void
displayAllClues(arrClues aList, int numClues)
{
	int i;
	for(i=0; i<numClues; i++){
		printf("%s: %s\n", aList[i].relation, aList[i].relValue);
	}
}

/* Given the filename stored in fname, this function
	overwrites the contents of the text file with the contents 
	if the array aEntries. Contents of aEntries and nElem will 
	not change in this function.
 
	@param fname - the string filename, including the extension
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
*/
void
export(strWord fname, wordList aEntries, int nElem)
{
	FILE *fp;
	int i=0, j=0;
	int YN;
	char dump;
	if((fp=fopen(fname, "r"))){
		printf("File exist. Do you Want to overwrite?Type \'1\' if yes type \'0\' if no: \n");
		do{
			scanf("%d%c", &YN, &dump);
			if(YN!=1 || YN!=0)
				printf("Please input a valid value: ");
		}while(YN!=1 || YN!=0);
		if(YN){
			fp=fopen(fname, "w");
			while(nElem>i){
				j=0;
				fprintf(fp, "Object: %s\n", aEntries[i].answer);
				while(aEntries[i].numClues>j){
					fprintf(fp, "%s: %s\n", aEntries[i].clueList[j].relation,aEntries[i].clueList[j].relValue);
					j++;
				}
				i++;
				if(nElem>i)
					fprintf(fp, "\n");
			}
			fclose(fp);
		}
	}
	else{
		fp=fopen(fname, "w");
		while(nElem>i){
				j=0;
				fprintf(fp, "Object: %s\n", aEntries[i].answer);
				while(aEntries[i].numClues>j){
					fprintf(fp, "%s: %s\n", aEntries[i].clueList[j].relation,aEntries[i].clueList[j].relValue);
					j++;
				}
				i++;
				if(nElem>i)
					fprintf(fp, "\n");
			}
		fclose(fp);
		printf("File created....\n");
	}
}

/* This function sorts the contents of aEntries in increasing
	order (based on ASCII value). The solution to this function
	should be an IMPLEMENTATION of a sorting algorithm, NOT by
	calling a sort function from some C library.
	
	@param aEntries - the array of words with the corresponding clues
	@param nElem - the number of elements in aEntries
*/
void 
sortEntries(wordList aEntries, int nElem)
{
	sorterRecurssion(aEntries, 0,nElem-1);
}