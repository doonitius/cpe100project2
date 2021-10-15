/* project 2
* Created by Doonlayatis (DOON)
* ID 62070503532
* This is the main file
* This program feature main menu
* including searching displaying and adding
* each session will call other sub-function
* to make the program works correctly
* 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "computer.h"
#include "validation.h"
#include "filesearch.h"
#include "filemodify.h"
#include "filereadwrite.h"
/*displaying all data from database to terminal */
void goDisplay()
{
	char inputline[128];				/* get string from file */
	COMPUTER_T * computer;				/* database structure */
	int count = 0;						/* count line in file */
	int i = 0;							/* index in for loop */
	/* call count line function */
	count = countline();
		if(count == 0)
		{
			printf("\nNo data in file, please add data\n");
			return;
		}
		/* dynamic allocating database */
		computer = (COMPUTER_T*) calloc(count,sizeof(COMPUTER_T));
		if(computer == NULL)
		{
			printf("cannot allocate memory\n");
			exit(0);
		}
		/*call read data in file function */
		readFile(count,computer);
			printf("\n--------Total %d computers--------\n",count);
			/* read and print data to terminal */
			for(i=0;i<count;i++)
			{
				printf("\n-----------Computer #%d-----------\n",i+1);
				printf("Date purchased: %s\n",computer[i].datepurchased);
				printf("IP Address: %s\n",computer[i].ipaddress);
				printf("Owner name: %s\n",computer[i].ownername);
				printf("Owner moblie phone: %s\n",computer[i].ownerphone);
				printf("Room number: %s\n",computer[i].roomnumber);
				printf("Type of computer: %s\n",computer[i].typecomputer);
			}
	printf("\n----------------------------------\n");
	free(computer);
}

/* This function let user add data*/
void goAddinfo()
{
    char input[256];				/* get string from user */
    char add[128];					/* for scan string that user add */
    int amountToAdd = 0;			/* number of computer to add */
    int i = 0;						/* index counting in loop */
	int flag = 1;					/* boolean variable 0 for true and 1 for false*/
    COMPUTER_T * computer = NULL;	/* database structure */	
        printf("\n------------Add Computer------------\n");
        printf("    **List of data to be added**\n");
        printf("    1. Date purchased\n");
        printf("    2. IP Address\n");
        printf("    3. Owner name\n");
        printf("    4. Owner mobile phone\n");
        printf("    5. Room number\n");
        printf("    6. Type of computer\n");
		/* asking user for number of addition */
        while(1)
        {
            printf("\nHow many computers you want to add? ");
            memset(input,0,sizeof(input));
            fgets(input,sizeof(input),stdin);
			/* loop checking if user is type correctly */
			for(i=0;i<strlen(input)-1;i++)
			{
				if(isdigit(input[i]))
				{
					flag = 0;
				}
				else
				{
					flag = 1;
					break;
				}
			}
            sscanf(input,"%d",&amountToAdd);
			/* allocating data structure */
			computer = (COMPUTER_T*) calloc(amountToAdd,sizeof(COMPUTER_T));
            if(computer == NULL)
            {
				printf("cannot allocate memory for %d computers\n",amountToAdd);
                exit(0);
            }
			else if(flag == 0)
			{
				break;
			}
        }
			/* adding session */
            for(i=0;i<amountToAdd;i++)
            {
                printf("\nComputer #%d\n",i+1);
                while(1)
                {
                    printf("1. Date purchased : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s",add);
                    if(validateDateTime(add) == 0)
                    {	
						sscanf(add,"%s",computer[i].datepurchased);
                        break;
                    }
                }

                while(1)
                {
                    printf("2. IP Address : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s",add);
					input[strlen(input)-1] = '\0';
                    if(validateIPaddress(add) == 0)
                    {
						sscanf(input,"%s",computer[i].ipaddress);
                        break;
                    }
                }

                while(1)
                {
                    printf("3. Owner name : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%[^\n]",add);
                    if(checkname(add) == 0)
                    {
						strcpy(computer[i].ownername,add);
                        break;
                    }
					else
					{
						printf("Invalid - contain punctuation characters\n");
					}
                }

                while(1)
                {
                    printf("4. Owner mobile phone : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s",add);
					input[strlen(input)-1] = '\0';
                    if(validphonenumber(add) == 0)
                    {
						sscanf(input,"%s",computer[i].ownerphone);
                        break;
                    }
                }

                while(1)
                {
                    printf("5. Room number : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s",add);
                    if(checkroom(add) == 0)
                    {
						sscanf(add,"%s",computer[i].roomnumber);
                        break;
                    }
                }

                while(1)
                {
                    printf("6. Type of computer : ");
                    memset(add,0,sizeof(add));
                    fgets(input,sizeof(input),stdin);
                    sscanf(input,"%s",add);
                    if(validtype(add) == 0)
                    {
						sscanf(add,"%s",computer[i].typecomputer);
                        break;
                    }
                }
				/* calling add file function to add data to data base file */
				addfile(computer[i].datepurchased,computer[i].ipaddress,computer[i].ownername,
				computer[i].ownerphone,computer[i].roomnumber,computer[i].typecomputer);
            }
	free(computer);
}
/* function ask for edit */
void getEdit(int index)
{				
	char input[128];		/* get input from user */
	char yesno[128];		/* decision from user */
	/* ask user for edit data */
	while(1)
	{
		printf("\nDo you want to edit? (Y/N) ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%s",yesno);
		if(strcasecmp(yesno,"N") == 0)
		{
			break;
		}
		if(strcasecmp(yesno,"Y") == 0)
		{
			printf("Edit in process\n");
			modifyFile(index);
		}
	}
}
/* searching name function */
void getsearchName()
{
    char input[128];		/* get input from user */
    char name[128];			/* hold variable */
	int result;				/* boolean variable */	
    printf("    \n[Search by Owner name]\n");
    while(1)
    {        
        printf("    Search owner name: ");
        memset(input,0,sizeof(input));
        fgets(input,sizeof(input),stdin);
        if(strlen(input) >= 1)
        {
			sscanf(input,"%[^\n]",name);
			/* call search file function */
			result = searchFile(2,name);
			if(result == -99)
			{
				break;
			}
			if(result >= 0)
            {	
				/* call edit function */
				getEdit(result);
				break;
			}
        }
    }
}


void getsearchIP()
{
    char input[128];		/* get input from user */
    char ipAddress[128];	/* hold variable */
	int result;				/* boolean variable */
    printf("    \n[Search by IP Address]\n");
    while(1)
    {
        printf("    Search IP Address: ");
        memset(input,0,sizeof(input));
        fgets(input,sizeof(input),stdin);
        if(strlen(input) >= 1)
        {
			sscanf(input,"%s",ipAddress);
			/* call search file function */
			result = searchFile(1,ipAddress);
			if(result == -99)
			{
				break;
			}
            if(result >= 0)
            {
				/* call edit function */
				getEdit(result);
				break;
			}
        }
    }
}
/* main searching fucntion */
void gosearch()
{
    char inputstring[128];			/* get input from user */
    int searchchoice = 0;			/* get choice that user selected */
	/* menu search session */
    while(1)
    {
    	printf("\nSearch menu\n");
    	printf("    1. IP Address\n");
    	printf("    2. Owner name\n");
    	printf("    Exit (Hit return)\n");
    	printf("\nWhat do you want to search? ");
    	memset(inputstring,0,sizeof(inputstring));
		memset(&searchchoice,0,sizeof(searchchoice));
    	fgets(inputstring,sizeof(inputstring),stdin);
    	if(strlen(inputstring) == 1)
    	{
        	break;
    	}
	    else
	    {	
        	sscanf(inputstring,"%d",&searchchoice);
	        if(searchchoice == 1)
    	    {	
				/* call search ip address fucntion */
    	        getsearchIP();
    	    }
    	    else if(searchchoice == 2)
    	    {
				/* call search name fucntion */
    	        getsearchName();
    	    }
		}

    }
}
/* control fucntion from selection from main menu */
void controlfunction(int choice)
{
    if (choice == 1)
    {
		/* calling search menu */
        gosearch();
    }
    else if(choice == 2)
    {
		/* calling add menu */
        goAddinfo();
    }
	else if(choice == 3)
	{
		/* calling display function */
		goDisplay();
	}
}
/* main fucntion for displaying main menu */
int main()
{
    int choices = 0;		/* get choice from user */
    char input[64];			/* get string from input */
	/* main menu loop */
    while(choices != 4)
    {
	    printf("\n-------CPE Computer Database------\n");
    	printf("Menu\n");
    	printf("    1. Search computer\n");
    	printf("    2. Add computer\n");
    	printf("    3. Display all computer\n");
    	printf("    4. Exit program\n");
    	printf("\nWhat do you want to do? ");
    	memset(&choices,0,sizeof(choices));
    	fgets(input,sizeof(input),stdin);
    	sscanf(input,"%d",&choices);
		/* if user selected number between menu numbers */
    	if(choices >= 1 && choices <= 3)
    	{
			/* calling control function */
    	    controlfunction(choices);
    	}
		/* exiting condition */
    	else if (choices == 4)
    	{
    	    printf("Good bye!\n");
    	    exit(0);
    	}
    }
}
