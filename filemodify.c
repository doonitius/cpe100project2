/* project 2
* Created by Doonlayatis (DOON)
* ID 62070503532
* This is the modify file
* This program feature editing data base
* Ask user what properties they want to edit
* Then replace the new data to the old one
* 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "computer.h"
#include "validation.h"
#include "filemodify.h"
#include "filereadwrite.h"
/* modifying function */
void modifyFile(int index)
{
	COMPUTER_T * computer;			/* data structure variable */
	int i = 0;						/* index variable */
	char inputline[256];			/* get string from file */
	char input[128];				/* get string from user */
	int selected = 0;				/* get choice from user */
	int count = 0;					/* get number of line from file */
	char mod[128];					/* get edited data from user */
	/* call count line function */
	count = countline();
		/* allocate data base structer */
		computer = (COMPUTER_T*) calloc(count,sizeof(COMPUTER_T));
		if(computer == NULL)
		{
			printf("cannot allocate memory\n");
			exit(1);
		}
		/* call read data in file function */
		readFile(count,computer);
	/* editing session */
	while(1)
	{
		memset(&selected,0,sizeof(selected));
		printf("\nEdit Menu\n");
		printf("1. Date purchased\n");
		printf("2. IP Address\n");
		printf("3. Owner name\n");
		printf("4. Owner mobile phone\n");
		printf("5. Room number\n");
		printf("6. Type of computer\n");
		printf("\tWhat do you want to edit? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&selected);
		while(selected == 1)
		{
			printf("Enter new date: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",mod);
			if(validateDateTime(mod) == 0)
			{
				strcpy(computer[index].datepurchased,mod);
				printf("********successfully edited!********\n");
				break;
			}
		}
		while(selected == 2)
		{
			memset(mod,0,sizeof(mod));
			printf("Enter new IP address: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",mod);
			input[strlen(input)-1] = '\0';
			if(validateIPaddress(mod) == 0)
			{
				strcpy(computer[index].ipaddress,input);
				printf("********successfully edited!********\n");
				break;
			}
		}
		while(selected == 3)
		{
			memset(mod,0,sizeof(mod));
			printf("Enter new owner name: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%[^\n]",mod);
			if(checkname(mod) == 0)
			{
				strcpy(computer[index].ownername,mod);
				printf("********successfully edited!********\n");
				break;
			}
		}
		while(selected == 4)
		{
			memset(mod,0,sizeof(mod));
			printf("Enter new mobile phone: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",mod);
			input[strlen(input)-1] = '\0';
			if(validphonenumber(mod) == 0)
			{
				strcpy(computer[index].ownerphone,input);
				printf("********successfully edited!********\n");
				break;
			}
		}
		while(selected == 5)
		{
			memset(mod,0,sizeof(mod));
			printf("Enter new room number: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",mod);
			if(checkroom(mod) == 0)
			{
				strcpy(computer[index].roomnumber,mod);
				printf("********successfully edited!********\n");
				break;
			}
		}
		while(selected == 6)
		{
			memset(mod,0,sizeof(mod));
			printf("Enter new type: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",mod);
			if(validtype(mod) == 0)
			{
				strcpy(computer[index].typecomputer,mod);
				printf("********successfully edited!********\n");
				break;
			}
		}
		break;
	}
	/* call write data to file function */
	writefile(computer,count);
	free(computer);

}
