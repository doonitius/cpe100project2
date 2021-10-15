/* project 2
* Created by Doonlayatis (DOON)
* ID 62070503532
* validation file
* This file is the function
* that validate the input
* that user has entered
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"validation.h"
#include "computer.h"
/* strucuture for validating ip address */
typedef struct
{
    char datepurchased[128];
    char ipaddress[128];
    char ownername[128];
    char ownerphone[128];
    char roomnumber[128];
    char typecomputer[128];
} COMPUTER2_T;
int checkname(char name[])
{
	int i = 0;
	int flag = 1;
	int len = strlen(name);
	for(i=0;i<len;i++)
	{
		if(ispunct(name[i]))
		{
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}
	}
	return flag;
}

int checkday(int dd, int mm, int yyyy)
{
	int result; /* return value */
    time_t t=time(NULL);
    struct tm tm = *localtime(&t);
    if((dd <= tm.tm_mday && mm == tm.tm_mon+1 && yyyy == tm.tm_year+1900) ||
       (dd <= 31 && mm <= 12 && mm < tm.tm_mon+1 && yyyy == tm.tm_year+1900) ||
       (dd <= 31 && mm <= 12 && mm >= 1 && yyyy < tm.tm_year+1900))
    {
        if((dd >= 1 && dd <= 31) &&
           (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
        {
            result = 1;
        }
        else if((dd >= 1 && dd <= 30) &&
                (mm == 4 || mm == 6 || mm == 9 || mm == 11))
        {
            result = 1;
        }
        else if((mm == 2) && (yyyy %4==0) && (dd>=1 && dd<=29))
        {
            result = 1;
        }
            else if((mm == 2) && (yyyy %4!=0) && (dd>=1 && dd<=28))
        {
            result = 1;
        }
        else
        {
            result = 0;
        }
    }
    else
    {
        result = 0;
    }
    return result;
}
/* date and time validating function */
int validateDateTime(char checkDateTime[])
{
    int i = 0;                      /* counting loop */
    int result,status = 0;     /* boolean value */
    int yyyy,mm,dd;           /* date and time variable */
    int len = strlen(checkDateTime); /*length of date and time */
	int resultlast = 1;
    time_t t=time(NULL);
    struct tm tm = *localtime(&t);

    if(len == 10)
    {
        if(isdigit(checkDateTime[0]) && isdigit(checkDateTime[1]) &&
           isdigit(checkDateTime[3]) && isdigit(checkDateTime[4]) &&
           isdigit(checkDateTime[6]) && isdigit(checkDateTime[7]) &&
           isdigit(checkDateTime[8]) && isdigit(checkDateTime[9]))
        {
            sscanf(checkDateTime,"%d-%d-%d",&dd,&mm,&yyyy);
            if(yyyy <= tm.tm_year+1900 && yyyy >= tm.tm_year+1800)
            {
                if((yyyy == tm.tm_year+1900 && mm <= tm.tm_mon+1)||
                   (yyyy < tm.tm_year+1900 && mm >=1 && mm <=12))
                {
                    status = checkday(dd,mm,yyyy);
                    if(status == 1)
                    {
                            return resultlast = 0;
                    }
                    else
                    {
                        printf("    Not valid - illegal day or must be in the past\n");
                    }
                }
                else
                {
                    printf("    Not valid - illegal month or must be in the past\n");
                }
            }
            else
            {
                printf("    Not valid - illegal year or must be in the past or year is out of range\n");
            }
        }
        else
        {
            printf("    Not valid - Alphabetic\n");
        }
    }
    else
    {
        printf("    Not valid - wrong format\n");
    }
}

int checkdigit2dash(char first[], char second[], char third[])
{
    int i = 0;
    int result = 0;
    int one,two,three = 0;

    for(i=0;i<strlen(first);i++)
    {
        if(isdigit(first[i]))
        {
            one = 1;
        }
        else
        {
            return result = 0;
            break;
        }
    }
        for(i=0;i<strlen(second);i++)
    {
        if(isdigit(second[i]))
        {
            two = 1;
        }
        else
        {
            return result = 0;
            break;
        }
    }
        for(i=0;i<strlen(third)-1;i++)
    {
        if(isdigit(third[i]))
        {
            three = 1;
        }
        else
        {
            return result = 0;
            break;
        }
    }
    if(one == 1, two == 1, three == 1)
    {
        result = 1;
    }
    return result;
}

int checkdigit1dash(char first[], char second[])
{
    int i = 0;
    int result = 0;
    int one,two = 0;
    for(i=0;i<strlen(first);i++)
    {
        if(isdigit(first[i]))
        {
            one = 1;
        }
        else
        {
            return result = 0;
            break;
        }
    }
        for(i=0;i<strlen(second)-1;i++)
    {
        if(isdigit(second[i]))
        {
            two = 1;
        }
        else
        {
            return result = 0;
            break;
        }
    }
    if(one == 1 && two == 1)
    {
        result = 1;
    }
    return result;
}

int checkdigitNodash(char number[])
{
    int i = 0;
    int result = 0;
    for(i=0;i < strlen(number)-1;i++)
    {
        if(isdigit(number[i]))
        {
            result = 1;
        }
        else
        {
            result = 0;
            break;
        }
    }
    return result;
}

int checkdash(char str[])
{
    int i=0;                    /* for counting loop */
    int dashcount = 0;          /* counting dash */
    for(i=0;i<strlen(str);i++)
    {
        if(str[i] == '-')
        {
            dashcount++;
        }
    }
    return dashcount;
}

int validphonenumber(char input[])
{
    int i = 0;
    char what[] = "0";
    int len = strlen(input);
    int dash = 0;
    char *token1,*token2,*token3;
    const char cutter[2] = "-";
    int allDigit = 2;
	int result = 1;

    if(len >= 10 && len <= 12)
    {
        if(input[i] == '0')
        {
            i = 1;
            if(input[i] == '1' || input[i] == '5' || input[i] == '6' || input[i] == '8' || input[i] == '9')
            {
                dash = checkdash(input);
                if(dash == 1 && len == 11)
                {

                    token1 = strtok(input,cutter);
                    token2 = strtok(NULL,cutter);
                    if(token2 == NULL || strlen(token2) == 1)
                    {
                        printf("    Not valid - dash is together\n");
                    }
                    else
                    {
                        allDigit = checkdigit1dash(token1,token2);
                    }
                }
                else if(dash == 2 && len == 12)
                {
                    token1 = strtok(input,cutter);
                    token2 = strtok(NULL,cutter);
                    token3 = strtok(NULL,cutter);
                    if(token3 == NULL || strlen(token3) == 1)
                    {
                        printf("    Not valid - dash is together\n");
                    }
                    else
                    {
                        allDigit = checkdigit2dash(token1,token2,token3);
                    }
                }
                else if(dash == 0 && len == 10)
                {
                    allDigit = checkdigitNodash(input);
                }
                else
                {
                    printf("    Not valid - Illegal dash or digit\n");
                }
            }
            else
            {
                printf("    Not valid - Illegal first two digits\n");
            }

        }
        else
        {
            printf("    Not valid - Illegal first two digits\n");
        }
    }
    else
    {
        printf("Invalid - Illegal length\n");
    }
    if(allDigit == 1)
    {
        return result = 0;
    }
    else if(allDigit == 0)
    {
        printf("    Not valid - Alphabetic\n");
    }
}

int checkroom(char input[])
{
    char number[64];
    int room = 0;
	int result = 1;
    sscanf(input,"%s",number);
    if(strlen(number) == 4)
    {
        sscanf(number,"%d",&room);
        if(room >= 1000 && room < 1200)
        {
            return result = 0;
        }
        else
        {
            printf("    Not valid - illegal room\n");
        }
    }
    else
    {
        printf("    Not valid\n");
    }
}

int validtype(char input[])
{
    int i = 0;
    char type[64];
	int result = 1;
    sscanf(input,"%s",type);
    if(strcmp(type,"DESKTOP") == 0 || strcmp(type,"LAPTOP") == 0 ||
       strcmp(type,"SERVER") == 0 || strcmp(type,"TABLET") == 0)
    {
        return result = 0;
    }
    else
    {
        printf("    Not valid\n");
    }
}

/* function for checking digit in IP address */
int checkIPdigit(char first[],char second[],char third[],char fourth[])
{
    int result,i;                   /* result boolean and counting loop */
    int one,two,three,four;         /* boolean for each validtion */
    for(i=0;i<strlen(first);i++)
    {
        if(isdigit(first[i]))
        {
            one =0;
        }
        else
        {
            one =1;
            break;
        }
    }
    for(i=0;i<strlen(second);i++)
    {
        if(isdigit(second[i]))
        {
            two =0;
        }
        else
        {
            two=1;
            break;
        }
    }
    for(i=0;i<strlen(third);i++)
    {
        if(isdigit(third[i]))
        {
            three =0;
        }
        else
        {
            three=1;
            break;
        }
    }
    for(i=0;i<strlen(fourth);i++)
    {
        if(isdigit(fourth[i]))
        {
            four =0;
        }
        else
        {
            four=1;
            break;
        }
    }
    if(one == 0 && two == 0 && three == 0 && four == 0)
    {
        result = 0;
    }
    else
    {
        result =1;
    }
    return result;
}
/* checking period in IP address */
int checkperiodIP(char IP[])
{
    int i =0;               /* counting loop */
    int periodcount = 0;    /* count period */
    for(i=0;i<strlen(IP);i++)
    {
        if(IP[i] == '.')
        {
            periodcount++;
        }
    }
    return periodcount;
}
/* function for validating IP address */
int validateIPaddress(char IP[])
{
    char *token,*token2,*token3,*token4;    /* get char from string token */
	char first[32],sec[32],third[32],fourth[32]; 
    const char period[2] = ".";             /* constant char to separate the string */
    int checkperiod;                        /* for checking period */
    int len1,len2,len3,len4;                /* for holding length of strings */
    int num1,num2,num3,num4;                /* for holding integer from string */
    int digit;                              /* to receive return value from digit function */
	int result = 1;
	int i =0;
	int count = 0;
	char inputline[256];
	char tempIP[128];
	sscanf(IP,"%s",tempIP);
	FILE * pFile = NULL;
	COMPUTER2_T * computer2;
    checkperiod = checkperiodIP(IP);
    if(checkperiod == 3)
    {
        /* separating string */
        token = strtok(IP,period);
        token2 = strtok(NULL,period);
        token3 = strtok(NULL,period);
        token4 = strtok(NULL,period);
        if (token,token2,token3,token4 != NULL)
        {
        /* checking length of string */
        len1 = strlen(token);
        len2 = strlen(token2);
        len3 = strlen(token3);
        len4 = strlen(token4);
        if((len1 >= 1 && len1 <=3) && (len2 >= 1 && len2 <= 3) && (len3 >= 1 && len3 <= 3) && (len4 >= 1 && len4 <= 3))
        {
			/*sscanf(token,"%s",first);
			sscanf(token2,"%s",sec);
			sscanf(token3,"%s",third);
			sscanf(token4,"%s",fourth);*/
            digit = checkIPdigit(token,token2,token3,token4);
            if(digit == 0)
            {
                sscanf(token,"%d",&num1);
                sscanf(token2,"%d",&num2);
                sscanf(token3,"%d",&num3);
                sscanf(token4,"%d",&num4);
                if((num1 >= 1 && num1 <= 255) && (num2 >= 0 && num2 <= 255) && (num3 >= 0 && num3 <= 255) && (num4 >= 0 && num4 <= 255))
                {
					pFile = fopen("data.txt","r");
					if(pFile == NULL)
					{
						return result = 0;
					}
					while(fgets(inputline,sizeof(inputline),pFile) != NULL)
					{
						count++;
					}
					fclose(pFile);
					if(count == 0)
					{
						return result = 0;
					}
					computer2 = (COMPUTER2_T*) calloc(count,sizeof(COMPUTER2_T));
					if(computer2 == NULL)
					{
						printf("cannot allocate memory\n");
						exit(1);
					}
						pFile = fopen("data.txt","r");
					if(pFile == NULL)
					{
						printf("cannot open file\n");
						exit(0);
					}	
					for(i=0;i<count;i++)
					{
						fgets(inputline,sizeof(inputline),pFile);
						sscanf(inputline,"%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^\n]",computer2[i].datepurchased,computer2[i].ipaddress,computer2[i].ownername,
						computer2[i].ownerphone,computer2[i].roomnumber,computer2[i].typecomputer);
						if(strcmp(tempIP,computer2[i].ipaddress) == 0)
						{
							result = 1;
							printf("    Not valid - IP address already exist!\n");
							break;
						}
						else
						{
							result = 0;
						}
					}	
						fclose(pFile);
						free(computer2);
					
                }
                else
                {
                    printf("    Not valid - illegal numbers\n");
                }
            }
            else
            {
                printf("    Not valid - alphabetic characters\n");
            }
        }
        else
        {
            printf("    Not valid - illegal numbers\n");
        }
        }
        else
        {
            printf("    Not valid - illegal numbers\n");
        }
    }
    else
    {
        printf("    Not valid - illegal period\n");
    }

	return result;
}
