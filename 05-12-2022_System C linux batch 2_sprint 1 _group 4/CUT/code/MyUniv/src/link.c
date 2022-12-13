#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<common.h>

typedef  struct link link;

struct link{
	char* courseNo;
	char* chapterName;
	int serialNumber;
	link *next;
};
typedef struct {
	
link* front;
link* rear;

}links;

links *linkList;
/*
int getLastCourseId()
{
	if(course_list == NULL)
	{
		return FAILURE;
	}
	if(course_list->rear == NULL)
		return FAILURE;
	
	int lastId=atoi(subStr(course_list->rear->courseNo,1,strlen(course_list->rear->courseNo)-1));
	printf("Last Id : %d\n",lastId);
	return lastId;
}

char* generateCourseNo()
{
	char courseCountStr[10]; 
	sprintf(courseCountStr,"%d",(getLastCourseId()+1));
	char* paddingStr = leftpadzero(courseCountStr,10);
	char *courseNo = (char*)malloc(strlen(paddingStr)+1);
	sprintf(courseNo,"C%s",paddingStr);	
	return courseNo;
}
*/
link *createLink(char* courseNo,char *chapterName, int serialNumber)
{
	
	link *l = (link*)malloc(sizeof(link));
	
	
	l->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	l->chapterName =(char*)malloc(strlen(chapterName)*sizeof(char));
		
	strcpy(l->courseNo,courseNo);
	strcpy(l->chapterName,chapterName);
	l->serialNumber = serialNumber;
	l->next = NULL;
	return l;
		
}

int addLinkToList(link *newLink)
{
		if(linkList == NULL)
		{
			linkList = (links*)malloc(sizeof(links));
			linkList->front =NULL;
			linkList->rear = NULL;
			
		}
		if(linkList->front == NULL)
		{
			linkList->front = newLink;
			
		}
		if(linkList->rear == NULL)
		{
			linkList->rear = newLink;
		}			
		else{
			linkList->rear->next = newLink;
			linkList->rear = newLink;
			
		}
		return SUCCESS;
}



int loadLinks()
{
	FILE* file;
	
	char buffer[MAX_BUFFER];
	char **data;
	file = fopen("./data/contents.txt", "r");
	
	if(file == NULL)
		return FAILURE;

	link *l;
	//printf("entering whileLoop\n");
	// while(fgets(buffer, bufferLength, file))
	while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
	{
		//printf("%s,%ld\n",buffer,strlen(buffer));
		data = parseDataFromLine(buffer,",");
		l = createLink(data[0],data[1],atoi(data[2]));
		addLinkToList(l);
	}

    fclose(file);
	return SUCCESS;

}

int deleteLinkFromList(char* courseNo,char* chapterName) 
{
	//printf("Delete course number %s %s:\n",courseNo,chapterName);
    link *prev = NULL, *temp = NULL, *current= NULL;
	if(linkList==NULL)
	{
		printf("There is no course to delete\n");
		return FAILURE;
	}
	if(linkList->front == NULL && linkList->rear == NULL)
	{
		printf("\tThere is no course to delete\n");
		return FAILURE;
	}
	if(linkList->front == linkList->rear)
	{
		if(strcmp(linkList->front->courseNo,courseNo) == 0)
		{
			temp=linkList->front;
			free(temp);
			linkList->front = NULL;
			linkList->rear = NULL;
		}
		
	}
	else
	{
		current = linkList->front;
		
		while(current!=NULL)
		{
			if(strcmp(current->courseNo,courseNo) == 0)
			{
				temp = current;
				
				//temp->next = prev?temp->next:NULL;
				if(current == linkList->front)
				{
					//printf(" found in front\n");
					linkList->front = current->next;
					printf("\t!! Deletion Successfull !!\n");
				}
				else if(current == linkList->rear)
				{
					printf("\t!! Deletion Successfull !!\n");
					//printf("found in rear\n");
					linkList->rear = prev;
					linkList->rear->next = NULL;
				}
				else
				{
					printf("\t!! Deletion Successfull !!\n");
					//printf("found in middle\n");
					prev->next = current->next;
					
				}
				//course_list->courseCount--;
				free(temp);
				break;
			}
			else{
				prev = current ;
				current = current->next;
			}
		
		}
	}   
    
    return SUCCESS;
} 
void showCourseContents(char* courseNo)
{
	if(linkList == NULL)
	{
		printf("\t!! Nothing to display !!\n");
		return;
	}
	if(linkList->front == NULL)
	{
		printf("\t!! Nothing to display !!\n");
		return;
	}
	//printf("THE LIST OF links ARE\n");
	//printf("Total number of course : %d\n",course_list->courseCount);
	for(link* temp= linkList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(temp->courseNo,courseNo)==0)
		{
			printf("\tcourseNo : %s , chapterName : %s , Serial No : %d\n",temp->courseNo,temp->chapterName,temp->serialNumber);
		}
	}
	//printf("End of list\n");
}


void displayLinks()
{
	if(linkList == NULL)
	{
		//printf("!! Nothing to display !!\n");
		return;
	}
	if(linkList->front == NULL)
	{
		printf("\t!! Nothing to display !!\n");
		return;
	}
	printf("THE LIST OF links ARE\n");
	//printf("Total number of course : %d\n",course_list->courseCount);
	for(link* temp= linkList->front ; temp!= NULL; temp = temp->next)
	{
		printf("\tcourseNo : %s , chapterName : %s , Serial No : %d\n",temp->courseNo,temp->chapterName,temp->serialNumber);
	}
	//printf("End of list\n");
}

int saveLinks()
{
	if(linkList == NULL)
		return FAILURE;
	FILE *file;
	file = fopen("./data/contents.txt","wt");
	for(link* temp= linkList->front ; temp!= NULL; temp = temp->next)
	{		
		fprintf(file , "%s,%s,%d\n",temp->courseNo,temp->chapterName,temp->serialNumber);		
	}
	fclose(file);
	return SUCCESS;

}
int updateLink(char *courseNo,char *chapterName, int serialNumber)
{
	if(linkList == NULL)
		return FAILURE;
	for(link* temp= linkList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseNo,temp->courseNo) && strcmp(chapterName,temp->chapterName))
		{
			temp->serialNumber = serialNumber;
			return SUCCESS;
		}
	}
	return FAILURE;
}

int addLink()
{
	char courseNo[MAXBUFF_50], chapterName[MAXBUFF_50];
	int serialNo;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter chapter name :");
	scanf("%s",chapterName);
	printf("\tEnter serial number of the chapter in course : \n");
	scanf("%d",&serialNo);

	link *l = createLink(courseNo,chapterName,serialNo);
	addLinkToList(l);
	printf("\t!! Link added Successfully !!\n");
	return SUCCESS;

}
int modifyLink()
{
	char courseNo[MAXBUFF_50], chapterName[MAXBUFF_50];
	int serialNo,status;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter chapter name :");
	scanf("%s",chapterName);
	printf("\tEnter new serial number of the chapter in course : \n");
	scanf("%d",&serialNo);

	status = updateLink(courseNo,chapterName,serialNo);
	if(status == FAILURE)
		printf("\t!! Course `%s` & chapter `%s` not found to update serial number !!\n",courseNo,chapterName);
	else
		printf("\t!! Link modified Successfully !!\n");
	return status;

}
int deleteLink()
{
	char courseNo[MAXBUFF_50], chapterName[MAXBUFF_50];
	int status;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter chapter number :");
	scanf("%s",chapterName);
	

	status = deleteLinkFromList(courseNo,chapterName);
	if(status == 0)
		printf("\t!! Course `%s` & chapter `%s` not found to delete !!\n",courseNo,chapterName);
	else
		printf("\t!! Link delete Successfully !!\n");
	return status;
}
