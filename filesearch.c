/* project 2
* Created by Doonlayatis (DOON)
* ID 62070503532
* This is search session file
* This program feature search data base
* search the data that match what user has input
* then display the object that user wanted to find
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "computer.h"
#include "filesearch.h"
#include "filereadwrite.h"
/* display result of searching */
void displaysearch(int tochoice,COMPUTER_T * computer,int getchoice,int result,int * var,int j)
{
	if(tochoice == 2)
				{
				printf("\nselected %d. owner name: %s (IP address:%s)\n",getchoice,computer[var[j]].ownername,computer[var[j]].ipaddress);
				}
				printf("-------------------------------------------------------");
				printf("\nDate purchased: %s\n",computer[result].datepurchased);
				printf("IP Address: %s\n",computer[result].ipaddress);
				printf("Owner name: %s\n",computer[result].ownername);
				printf("Owner moblie phone: %s\n",computer[result].ownerphone);
				printf("Room number: %s\n",computer[result].roomnumber);
				printf("Type of computer: %s\n",computer[result].typecomputer);
				printf("-------------------------------------------------------\n");	
}
/* search file function recieve 2 argument choice(ip or name) 
and string that user search for */
int searchFile(int tochoice, char search[])
{
	FILE * pFile = NULL;			/* file variable */
	char inputline[128];			/* get string from file */
	COMPUTER_T * computer;			/* structure variable */
	int count = 0;					/* count number of line in file */
	char input[128];				/* get string from input */
	int i = 0;						/* index variable */
	int choice = 0;					/* get choice from user */
	int var[256];					/* hold index where it found object */
	int j = 0;						/* index variable */
	int getchoice = 0;				/* user choose an object */
	int result = -1;				/* result of user's selection */
	int len = strlen(search);		/* length of string that user input */
		/* call count line in file function */
		count = countline();
		if(count == 0)
		{
			printf("\nNo data in file, please add data\n");
			return result = -99;
		}
		/* allocate data base structer */
		computer = (COMPUTER_T*) calloc(count,sizeof(COMPUTER_T));
		if(computer == NULL)
		{
			printf("cannot allocate memory\n");
			exit(1);
		}
		/* call read data in file function */
		readFile(count,computer);
			for(i=0;i<count;i++)
			{
				if(strncasecmp(search,computer[i].ownername,len) == 0 && tochoice == 2)
				{
					choice++;
					var[j] = i;
					j++;
				}
				if(strcmp(search,computer[i].ipaddress) == 0 && tochoice == 1)
				{
					choice++;
					var[j] = i;
					j++;
				}
			}
			if(j-1 < 0)
			{
				printf("No computer found!\n");
				return result = -99;
			}
			if(tochoice == 2)
			{
			printf("\nTotal %d computers has found\n",choice);
			}
			/* print object that match */
			for(j=0;j<choice;j++)
			{
				if(tochoice == 2)
					{
						printf("%d. owner name: %s (IP address:%s)\n",j+1,computer[var[j]].ownername,computer[var[j]].ipaddress);
					}
				if(tochoice == 1)
					{
						printf("\nResult search for %s\n",computer[var[j]].ipaddress);
					}
			}
			/* ask for specific object */
			while(1 && tochoice != 1)
			{
				memset(&getchoice,0,sizeof(getchoice));
				printf("\nWhich one do you want to search for? ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%d",&getchoice);
				if(getchoice >= 1 && getchoice <= choice)
					{
						break;
					}
			}
				/* find position of specific object */
				for(j=0;j<choice && tochoice != 1;j++)
				{
					if(getchoice == j+1)
					{
						result = var[j];
						break;
					}
				}
				if(tochoice == 1)
				{
					result = var[j];
				}
				displaysearch(tochoice,computer,getchoice,result,var,j);
	free(computer);	
	return result;
}
