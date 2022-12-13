/*************************************************************************
*
*  FILE NAME    : main.c
*
*  DESCRIPTION  : Main method of the Program
*
*  DATE      		NAME   		 REFERENCE          REASON
*
*  09-DEC-2022      GROUP 4   	New			   Initial Creation.
*
*  Copyright 2010, Aricent Technologies (Holdings) Ltd
*
**************************************************************************/

/*************************************************************************
                               MAIN FILES
*************************************************************************/
#include <stdio.h>
#include <common.h>
#include <user.h>
#include <admin.h>
#include <application.h>

//#include <string.h>
//#include <stdlib.h>
// #include <courses.h>
// #include <chapters.h>
// #include <link.h>
// #include <bookmarks.h>

/******************************************************************************
*
*       Function Name   : main
*
*       Description     : Calling all the function in main method
*
*       Returns         : Success 
*
*******************************************************************************/
int main()
{
	int ch = 0;	
	int status;
	int isAppLoaded=0;
	while(1)
	{
		ch=loginMenu();
		if(ch!=0)
		{
			if(isAppLoaded==0)
			{
				loadApplication();
				isAppLoaded = 1;
			}
			switch(ch)
			{
				case 1:
					status = registerUser();
					if(status == 0)
						printf("\t!! User registartion failed !!\n");
					else
						printf("\t!! Registration successfully !!\n");
					break;
				case 2:
					user *u = loginUser();
					//int u = 0;
					if(u == NULL)
						printf("\t!! Invalid username or password !!\n");
					else{
						if(isUserAdmin(u->username))
						{
							printf("\t!! Welcome Admin !!\n");
							showAdminMenu();
						}
						else{
							printf("\t!! Welcome %s !!\n",u->username);  
							showUserMenu(u);
						}
					}
					
					break;
				default:printf("\t!! wrong choice !!\n");
					break;
			}
		}
		else{
			saveApplication();
			printf("\t!! Exiting from Application !!\n");
			break;
		}
	}
	
	printf("\n\n");

	return 0;

}
