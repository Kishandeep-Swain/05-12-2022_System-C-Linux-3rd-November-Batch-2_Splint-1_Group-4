/***********************************************************
** FILENAME : common.c
**
** DESCRIPTION: Perform the function for Main Menu Customer Menu Driver Menu 
**
** Revision History :
** DATE                NAME            REFERENCE          REASON
** ----------------------------------------------------------------------
** 09 DEC 2022         GROUP 4       	 New        Initial Creation
**
**
** Copyright @ 2019 Altran Group All Rights Reserved
**
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include <time.h>
/******************************************************************************
*
*       Function Name   : mainMenu
*
*       Description     : Display the Main Menu
*
*       Returns         : Success 
*
*******************************************************************************/

int loginMenu()
{
	int ch;
	printf("\n\t*******************************************************\n");
	printf("\n\t                 WELCOME TO MyUniv          \n");
	printf("\n\t*******************************************************\n");
	printf("\n\t==================Login Screen========================\n");
	printf("\n\t1. Register New User");
	printf("\n\t2. Login");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;
}

int courseMainMenu()
{
	int ch;
	printf("\n\t==================Course Screen========================\n");
	printf("\n\t1. Add Courses");
	printf("\n\t2. Modify Courses");
	printf("\n\t3. Delete Courses");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;
}

int chapterMainMenu()
{
	int ch;
	printf("\n\t==================Chapter Screen========================\n");
	printf("\n\t1. Add Chapters");
	printf("\n\t2. Modify Chapters");
	printf("\n\t3. Delete Chapters");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;
}

int linkMainMenu()
{
	int ch;
	printf("\n\t==================Link Screen========================\n");
	printf("\n\t1. Add Link");
	printf("\n\t2. Modify Link");
	printf("\n\t3. Delete Link");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;
}


/******************************************************************************
*
*       Function Name   : UserMenu
*
*       Description     : Display the User Main Menu
*
*       Returns         : Success 
*
*******************************************************************************/

int userMainMenu()
{
	int ch;
	printf("\n\t================== User Screen ========================\n");
	printf("\n\t1. Search Course");
	printf("\n\t2. Enroll Course");
	printf("\n\t3. Add BookMark");
	printf("\n\t4. Mark Completed Chapter");
	printf("\n\t5. Display Completed Courses");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;	
}

/******************************************************************************
*
*       Function Name   : AdminMenu
*
*       Description     : Display the Admin Menu
*
*       Returns         : Success 
*
*******************************************************************************/


int adminMainMenu()
{
	int ch = 0;
	printf("\n\t========== Admin Screen ===============\n");
	printf("\n\t1. Manage Courses");
	printf("\n\t2. Manage Chapters");
	printf("\n\t3. Link Chapters to Courses");
	printf("\n\t4. Display  enrolled courses statistics");
    printf("\n\t5. Display user statistics");
	printf("\n\t0. Quit");
	printf("\n\tChoice: ");
	scanf("%d",&ch);
	return ch;
}




/******************************************************************************
*
*       Function Name   : removeLeading
*
*       Description     : Removing the space
*
*       Returns         : Success 
*
*******************************************************************************/

void removeLeading(char *str, char *str1)
{
    int idx = 0, j, k = 0;
 
    /* Iterate String until last */
    /* leading space character*/
    while (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n')
    {
        idx++;
    }
 
    /* Run a for loop from index until the original */
    /* string ends and copy the content of str to str1*/
    for (j = idx; str[j] != '\0'; j++)
    {
        str1[k] = str[j];
        k++;
    }
 
    /* Insert a string terminating character */
    /* at the end of new string */
    str1[k] = '\0';
 
}

/******************************************************************************
*
*       Function Name   : removeTrailing
*
*       Description     : Removing the space
*
*       Returns         : Success 
*
*******************************************************************************/

void removeTrailing(char *str)
{
	if((str[strlen(str)-1] == ' ' || str[strlen(str)-1] == '\t' || str[strlen(str)-1] == '\n'))
    {
    	str[strlen(str)-1] = '\0';
    }

}

/******************************************************************************
*
*       Function Name   : parseDataFromLine
*
*       Description     : Break delimeter string into array
*
*       Returns         : string array 
*
*******************************************************************************/
char** parseDataFromLine(char* line,char* delimeter)
{
    char ** res  = NULL;
    char *  p    = strtok (line, delimeter);
    int n_delimeter = 0;

    while (p) {
		res = realloc (res, sizeof (char*) * ++n_delimeter);

	if (res == NULL)
		exit (-1); /* memory allocation failed */

	res[n_delimeter-1] = p;

	p = strtok (NULL, delimeter);
	
}
res = realloc (res, sizeof (char*) * (n_delimeter+1));
res[n_delimeter] = 0;
return res;

}

char* subStr(char* str,int index, int size)
{
	char* s = malloc(size);
	strncpy(s,str+index,size);
	return s;

}

char* leftpadzero(char *myString, int pi_length)
{
    
    char *fout;
    const char *padding="0000000000000000000000000000000000000000";

    int padLen = pi_length - strlen(myString); 

    if(padLen < 0) padLen = 0;   

    fout= (char *)malloc(pi_length*sizeof(char));

    sprintf(fout,"%*.*s%s", padLen, padLen, padding, myString);
	return fout;
}

char* getCurrentDateStr()
{
	time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char* currentDate = (char*)malloc(10);
    sprintf(currentDate, "%d/%d/%d", t->tm_mday, t->tm_mon+1,t->tm_year + 1900);
	return currentDate;
}

void encrypt(char* password,int key)
{
    unsigned int i;
	//printf("%s :\n",password);
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] - key;
    }
		//printf("%s :\n",password);

}