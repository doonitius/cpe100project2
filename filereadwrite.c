/* 
 project 2 
* Created by Doonlayatis (DOON)
* ID 62070503532
* This program handle about reading and writing file
* read and write file 
*/
#include <stdio.h>
#include <stdlib.h>
#include "computer.h"
#include "filereadwrite.h"
/* this function count line in data base file */
int countline()
{
	FILE * pFile = NULL;			/* file variable */
	int count = 0;					/* count number of line in file */
	char inputline[128];			/* get string from file */
	pFile = fopen("data.txt","r");
	if(pFile == NULL)
	{
		printf("No data\n");
		return count;
	}
		/* counting line */
		while(fgets(inputline,sizeof(inputline),pFile) != NULL)
		{
			count++;
		}
		fclose(pFile);
	return count;
}
/* this function read data in data base file */
void readFile(int count,COMPUTER_T * comp)
{
	FILE * pFile = NULL;			/* file variable */
	int i = 0;						/* index variable */
	char inputline[128];			/* get string from file */
		/* open file for read data in file */
		pFile = fopen("data.txt","r");
		if(pFile == NULL)
		{
			printf("No data\n");
			return;
		}
		for(i=0;i<count;i++)
			{
				fgets(inputline,sizeof(inputline),pFile);
				sscanf(inputline,"%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^\n]",comp[i].datepurchased,comp[i].ipaddress,comp[i].ownername,
				comp[i].ownerphone,comp[i].roomnumber,comp[i].typecomputer);
			}
		fclose(pFile);
}
/* This function add data that user added to database file */
void addfile(char date[], char iP[], char name[], char phone[], char room[], char type[])
{
	FILE * fAdd = NULL;				/* file variable */
	/* opening file for add data */
	fAdd = fopen("data.txt","a");
	if(fAdd == NULL)
	{
		printf("cannot add file\n");
		exit(0);
	}
	fprintf(fAdd,"%s/%s/%s/%s/%s/%s\n",date,iP,name,phone,room,type);	

	fclose(fAdd);
}
/* this function write all new data that user has modified to data base */
void writefile(COMPUTER_T * computer,int count)
{
	FILE * pFile = NULL;			/* file variable */
	int i =0;
	/* opening file for write data */
	pFile = fopen("data.txt","w");
	if(pFile == NULL)
	{
		printf("cannot open file\n");
		exit(4);
	}
	/* write new data to file */
	for(i=0;i<count;i++)
	{
		fprintf(pFile,"%s/%s/%s/%s/%s/%s\n",computer[i].datepurchased,computer[i].ipaddress,computer[i].ownername,
		computer[i].ownerphone,computer[i].roomnumber,computer[i].typecomputer);
	}	
	fclose(pFile);
}
