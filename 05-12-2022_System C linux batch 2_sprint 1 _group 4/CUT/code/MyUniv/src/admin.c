/*************************************************************************
*
*  FILE NAME    : admin.c
*
*  DESCRIPTION  : Perform the function of Admin
*
*  DATE     	 NAME  		  REFERENCE          REASON
*
*  09-DEC-2022  GROUP 4    	New       Initial Creation.
*  
*
*  Copyright 2010, Aricent Technologies (Holdings) Ltd
*
**************************************************************************/

/*************************************************************************
*                               HEADER FILES
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "user.h"
#include "courses.h"
#include "chapters.h"
#include "link.h"
/******************************************************************************
*
*       Function Name   : showCourseMenu
*
*       Description     : This function use for showing Course Menu
*
*       Returns         : Success or Failure
*
*******************************************************************************/


int showCourseMenu()
{
	int choice;

	
	while(1)
	{
		choice = courseMainMenu();
		if(choice!=0)
		{
			switch(choice)
			{
				case 1:
					addCourse();
					break;
				case 2:
					modifyCourse();
					break;
				case 3:
					deleteCourse();
					break;
				default:printf("\t!! wrong choice !!\n");

					break;
			}
		}
		else{
			printf("\tExiting Course Menu\n");
			break;
		}
	}
	return SUCCESS;
}

/******************************************************************************
*
*       Function Name   : showChapterMenu
*
*       Description     : This function use for showing Chapter Menu
*
*       Returns         : Success or Failure
*
*******************************************************************************/


int showChapterMenu()
{
	int choice;
	
	
	while(1)
	{
	choice = chapterMainMenu();
		if(choice!=0)
		{
			switch(choice)
			{
				case 1:
						addChapter();
					break;
				case 2:
						modifyChapter();
					break;
				case 3:
						deleteChapter();
					break;
				default:printf("\t!! wrong choice !!\n");
					break;
			}
		}
		else{
			printf("\tExiting Chapter Menu\n");
			break;
		}
	}
	return SUCCESS;
}

/******************************************************************************
*
*       Function Name   : showLinkMenu
*
*       Description     : This function use for showing Link Menu
*
*       Returns         : Success or Failure
*
*******************************************************************************/

int showLinkMenu()
{
	int choice;
	
	
	while(1)
	{
		choice = linkMainMenu();
		if(choice!=0)
		{
			switch(choice)
			{
				case 1:
						addLink();
					break;
				case 2:
						modifyLink();
					break;
				case 3:
						deleteLink();
					break;
				default:printf("!! wrong choice !!\n");
					break;
			}
		}
		else{
			printf("\tExiting Link Menu\n");
			break;
		}
	}
	return SUCCESS;
}

/******************************************************************************
*
*       Function Name   : showAdminMenu
*
*       Description     : This function use for showing Admin Menu
*
*       Returns         : Success or Failure
*
*******************************************************************************/

int showAdminMenu()
{
	
	int choice;
	
	while(1)
	{
		choice = adminMainMenu();
		if(choice!=0)
		{
			switch(choice)
			{
				case 1:
					showCourseMenu();
					break;
				case 2:
					showChapterMenu();
					break;
				case 3:
					showLinkMenu();
					break;
				case 4:
					printf("\tDisplaying total number of enrolled courses\n");
					displayEnrollmentList();
					break;
				case 5:
					printf("\tDisplaying user statistics\n");
					displayUserList();
					break;
				
				default:printf("\t!! wrong choice !!\n");
					break;
			}
		}
		else{
			printf("\tExiting Admin Menu\n");
			break;
		}
	}
	return 1;
	
}



