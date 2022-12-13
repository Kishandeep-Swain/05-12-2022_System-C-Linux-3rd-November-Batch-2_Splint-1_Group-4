
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "common.h"
#include "courses.h"
#include "chapters.h"
#include "bookmark.h"
#include "link.h"
#include <unistd.h>


typedef struct {
user* front;
user* rear; 

}users;

users *userList;

user *createUser(char *username , char *password)
{
	user *u = (user*)malloc(sizeof(user));
	
	u->username = (char*)malloc(strlen(username)*sizeof(char));
	u->password =(char*)malloc(strlen(password)*sizeof(char));
	strcpy(u->username,username);
	strcpy(u->password,password);
	u->next = NULL;
	return u;
		
}

void addUserToList(user *newUser)
{
	if(userList == NULL)
	{
		userList = (users*)malloc(sizeof(users));
		userList->front =NULL;
		userList->rear = NULL;
	}
	if(userList->front == NULL)
	{
		userList->front = newUser;
		
	}
	if(userList->rear == NULL)
	{
		userList->rear = newUser;
	}			
	else{
		userList->rear->next = newUser;
		userList->rear = newUser;
		
	}
}
int isUserExists(char* userName)
{
	for(user* temp= userList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(temp->username,userName)==0)
			return SUCCESS;
	}
	return 	FAILURE;	
}
int registerUser()
{
	char userName[MAXBUFF_50],pswd[MAXBUFF_50];
	printf("\tEnter Username : ");
	scanf("%s",userName);
	printf("\tEnter Password : ");
	scanf("%s",pswd);
	if(strcmp(userName,NULL_STR)==0 || strcmp(pswd,NULL_STR)==0)
	{
		printf("\t!! Username and Password cannot be empty !!\n");
		return FAILURE;
	}
	if(isUserExists(userName))
	{
		printf("\t!! User already exists !!\n");
		return FAILURE;
	}
	//printf("before encrpyt : %s :\n",pswd);
	encrypt(pswd,ENCRYPT_KEY);
	//printf("%s :\n",pswd);
	user *u = createUser(userName,pswd);
	addUserToList(u);
	return SUCCESS;
}



int loadUsers()
{
        FILE* file;
        char buffer[MAX_BUFFER]; 
		char **data;
        file = fopen("./data/users.txt", "r");
		if(file == NULL)
			return FAILURE;

		user *u;
		while(fscanf(file,"%255[^\n]\n",buffer)!= EOF)
        {
		data = parseDataFromLine(buffer,",");
		u = createUser(data[0],data[1]);
		addUserToList(u);
		}

        fclose(file);

return SUCCESS;
}

void displayUserList()
{
	if(userList == NULL)
	{
		printf("\tNo users to display\n");
		return;
	}
	if(userList->front == NULL)
	{
		printf("\tNo users to display\n");
		return;
	}
	printf("\tTHE LIST OF USERS ARE\n");
	for(user* temp= userList->front ; temp!= NULL; temp = temp->next)
	{
		printf("username : %s , password : %s\n",temp->username,temp->password);
	}
}

int isUserAdmin(char* userName){
	return strcmp(userName,"admin")== 0 ? 1:0;
}

user *isValidUser(char* username , char* password)
{
	for(user* temp= userList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(temp->username,username)==0 && strcmp(temp->password,password)==0)
			return temp;
	}
	return NULL;
}

user *loginUser()
{
	char* password;
	char userName[MAXBUFF_50];//,paswd[MAXBUFF_50];
	printf("\tEnter Username : ");
	scanf("%s",userName);
	//printf("\tEnter Password : ");
	//scanf("%s",pswd);
	//readPassword(pswd);
	//printf("%s\n",pswd);
	password = getpass("\tEnter password :");
	encrypt(password,ENCRYPT_KEY);

	return isValidUser(userName,password);
}

int saveUsers()
{
	if(userList == NULL)
		return FAILURE;
	FILE *file;
	
	file = fopen("./data/users.txt","wt");
	for(user* temp= userList->front ; temp!= NULL; temp = temp->next)
	{
		fprintf(file , "%s,%s\n",temp->username,temp->password);
		
	}
	fclose(file);
return	SUCCESS;

}


int showUserMenu(user *u)
{
	int choice;
	int status;
	char courseName[MAXBUFF_50];
	char chapterName[MAXBUFF_50];
	int pageNo;
	char *courseNo; 

	while(1)
	{
		choice = userMainMenu();
		if(choice!=0)
		{
			switch(choice)
			{
				case 1:
					printf("\tEnter course name : ");
					scanf("\t%s",courseName);
					courseNo= getCourseNumber(courseName);
					if(strcmp(courseNo,NULL_STR)==0)
						printf("!! Course not found !!\n");
					else
					{
						printf("\t%s\n",courseNo);
						showCourseContents(courseNo);
						printf("\t!! Course found !!\n");
					}
					break;
				case 2:
					printf("\tEnter course name : ");
					scanf("%s",courseName);
					status = enrollCourse(courseName,u->username);
					//printf("status : %d\n",status);
					if(status == SUCCESS)
						printf("\t!! Course enrolled successfully !!\n");
					else
						printf("\t!! Failed to enroll course !!\n");
					break;
				case 3:
				printf("\tEnter courseName:");
					scanf("%s",courseName);
					printf("\tEnter chapterName:");
					scanf("%s",chapterName);
					printf("\tBookmark page number:");
					scanf("%d",&pageNo);
					courseNo= getCourseNumber(courseName);
					if(strcmp(courseNo,NULL_STR)==0)
						printf("\t!! Course not found !!\n");
					else
					{
						if(isChapterExist(courseNo,chapterName)==1)
						{
							status = addBookMarkForUser(courseNo,chapterName,u->username,pageNo);
							if(status == SUCCESS)
								printf("\t!! Bookmark added successfully !!\n");
						}
						else
						{
							printf("\t!! Chapter not found for course  !!\n");	
							
						}
					}

					
					break;
				case 4:
					
				printf("\tEnter courseName :");
					scanf("%s",courseName);
					printf("\tEnter chapterName :");
					scanf("%s",chapterName);
					courseNo = getCourseNumber(courseName);
					if(strcmp(courseNo,NULL_STR)==0)
					{
						printf ("\t!! Course %s not found !!",courseName);
						break;
					}
					char* completionDate = getCurrentDateStr();
					status = markChapterAsCompletedForUser(u->username,courseNo,chapterName);
					updateBookMarkChapterCompletionDateForUser(u->username,courseNo,chapterName,completionDate);
					if(isAllChapterOfCourseCompletedForUser(u->username,courseNo))
					{
						updateEnrollmentStatus(courseNo,u->username,"completed",completionDate);
					}
					if(status == SUCCESS)
						printf("\t!! Chapter marked as completed !!\n");
					else
						printf("\t!! Failed to mark chapter as completed !!\n");
					break;
					case 5:
					displayCompletedCoursesForUser(u->username);
					break;
					default:
					printf("\t!! Wrong choice !!\n");
					break;
			}
		}
		else{
			printf("\tExiting User Menu\n");
			break;
		}
	}
	return 1;
}
