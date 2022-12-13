#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common.h"

typedef struct chapter chapter;
struct chapter {
	char* courseNo;
	char* chapterNo;
	char* chapterName;
	char* filePath;
	chapter* next;
};
typedef struct {
	chapter* front;
	chapter* rear; 
 }chapters;

chapters *chapterList;
typedef struct completedChapter completedChapter;
struct completedChapter {	
	char* userName;
	char* courseNo;
	char* chapterName;
	char* completionDate;
	completedChapter* next;
};
typedef struct {
	completedChapter* front;
	completedChapter* rear; 
 }completedChapters;

completedChapters *completedChaptersList;


int getLastChapterId(char* courseNo)
{
	if(chapterList == NULL)
	{
		return 0;
	}
	//if(chapterList->rear == NULL)
		//return 0;
	char* chapterNo = malloc(MAXBUFF_50);
	for(chapter* temp= chapterList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(temp->courseNo,courseNo)==0)
		{
			strcpy(chapterNo,temp->chapterNo);
		}
			
	}
	if(strlen(chapterNo)>0)
	{
		int lastId=atoi(subStr(chapterNo,2,strlen(chapterNo)-2));
		//printf("Last Id : %d\n",lastId);
		return lastId;
		
	}

	return 0;
}
char* generateChapterNo(char* courseNo)
{
	char chCountStr[2]; 
	sprintf(chCountStr,"%d",(getLastChapterId(courseNo)+1));
	char* paddingStr = leftpadzero(chCountStr,2);
	char *chapterNo = (char*)malloc(strlen(paddingStr)+2);
	sprintf(chapterNo,"CH%s",paddingStr);	
	return chapterNo;
}
chapter* createChapter(char *courseNo,char *chapterNo,char* chapterName, char* filePath)
{
	
	chapter* ch = (chapter *)malloc(sizeof(chapter));	
	
	ch->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	ch->chapterNo = (char*)malloc(strlen(chapterNo)*sizeof(char));
	ch->chapterName =(char*)malloc(strlen(chapterName)*sizeof(char));
	ch->filePath =(char*)malloc(strlen(filePath)*sizeof(char));
	strcpy(ch->courseNo,courseNo);
	strcpy(ch->chapterNo,chapterNo);
	strcpy(ch->chapterName,chapterName);
	strcpy(ch->filePath,filePath);
	ch->next = NULL;
	return ch;
		
}

int updateChapter(char *courseNo,char* chapterName, char* filePath)
{
	if(chapterList == NULL)
		return FAILURE;
	for(chapter* temp= chapterList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseNo,temp->courseNo)==0 && strcmp(chapterName,temp->chapterName)==0)
		{
			strcpy(temp->filePath, filePath);
			return SUCCESS;
		}
	}
	return FAILURE;
}

int addChapterToList(chapter* newChapter)
{
		if(chapterList == NULL)
		{
			chapterList = (chapters*)malloc(sizeof(chapters));
			chapterList->front =NULL;
			chapterList->rear = NULL;

		}
		if(chapterList->front == NULL)
		{
			chapterList->front = newChapter;
			
		}
		if(chapterList->rear == NULL)
		{
			chapterList->rear = newChapter;
		}			
		else{
			chapterList->rear->next = newChapter;
			chapterList->rear = newChapter;
			
		}
		return SUCCESS;
}



int loadChapters()
{
	FILE* file;
	char buffer[MAX_BUFFER];
	char **data;
	file = fopen("./data/chapters.txt", "r");
	
	if(file == NULL)
		return FAILURE;

	chapter *c;
	//printf("entering whileLoop\n");
	// while(fgets(buffer, bufferLength, file))
	while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
	{
		
		//printf("%s,%ld\n",buffer,strlen(buffer));
		data = parseDataFromLine(buffer,",");
		c = createChapter(data[0],data[1],data[2],data[3]);
		addChapterToList(c);

	}

	fclose(file);
	return SUCCESS;

}

int deleteChapterFromList(char* courseNo,char *chapterName) 
{
	//printf("Delete course number %s:\n",courseNo);
    chapter *prev = NULL, *temp = NULL, *current= NULL;
	if(chapterList==NULL)
	{
		printf("!! There is no chapter to delete !!\n");
		return FAILURE;
	}
	if(chapterList->front == NULL && chapterList->rear == NULL)
	{
		printf("!! There is no chapter to delete !!\n");
		return FAILURE;
	}
	if(chapterList->front == chapterList->rear)
	{
		if(strcmp(chapterList->front->courseNo,courseNo) == 0 
		&& strcmp(chapterList->front->chapterName,chapterName) == 0)
		{
			temp=chapterList->front;
			free(temp);
			chapterList->front = NULL;
			chapterList->rear = NULL;
			return SUCCESS;
		}
		
	}
	else
	{
		current = chapterList->front;
		
		while(current!=NULL)
		{
			if(strcmp(current->courseNo,courseNo) == 0  
			&& strcmp(chapterList->front->chapterName,chapterName) == 0)
			{
				temp = current;
				
				//temp->next = prev?temp->next:NULL;
				if(current == chapterList->front)
				{
					//printf("Chapter found in front\n");
					chapterList->front = current->next;
				}
				else if(current == chapterList->rear)
				{
					//printf("Chapter found in rear\n");
					chapterList->rear = prev;
					chapterList->rear->next = NULL;
				}
				else
				{
					//printf("Chapter found in middle\n");
					prev->next = current->next;
					
				}
				//course_list->courseCount--;
				free(temp);
				return SUCCESS;
			}
			else{
				prev = current ;
				current = current->next;
			}
		
		}
	}    
    
    return FAILURE;
} 



void displayChapterList()
{
	if(chapterList == NULL)
	{
		printf("\t!! No chapter to display !!\n");
		return;
	}
	if(chapterList->front == NULL)
	{
		printf("\t!! No chapter to display !!\n");
		return;
	}
	//printf("THE LIST OF chapters ARE\n");
	//printf("Total number of course : %d\n",course_list->courseCount);
	for(chapter* temp= chapterList->front ; temp!= NULL; temp = temp->next)
	{
		printf("\tcourseNo : %s , chapterNo : %s , chapterName : %s , filePath : %s\n",temp->courseNo,temp->chapterNo,temp->chapterName,temp->filePath);
	}
}
int isChapterExist(char* courseNo,char* chapterName)
{
	for(chapter* temp= chapterList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseNo,temp->courseNo) == 0 && strcmp(chapterName,temp->chapterName) == 0)
			return SUCCESS;
	}
	return FAILURE;
}
int saveChapters()
{
	if(chapterList == NULL)
		return FAILURE;
	FILE *file;
	file = fopen("./data/chapters.txt","wt");
	for(chapter* temp= chapterList->front ; temp!= NULL; temp = temp->next)
	{		
		fprintf(file , "%s,%s,%s,%s\n",temp->courseNo,temp->chapterNo,temp->chapterName,temp->filePath);		
	}
	fclose(file);
	return SUCCESS;

}
int addChapter()
{
	char courseNo[MAXBUFF_50],*chapterNo ,chapterName[MAXBUFF_50], filePath[MAXBUFF_50];
	//int serialNo;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter chapter name :");
	scanf("%s",chapterName);
	printf("\tEnter file path :");
	scanf("%s",filePath);
	chapterNo = generateChapterNo(courseNo);
	chapter* ch = createChapter(courseNo,chapterNo,chapterName,filePath);
	addChapterToList(ch);
	printf("\t!! Chapter added successfully !!\n");
	return SUCCESS;
}
int modifyChapter()
{
	char courseNo[MAXBUFF_50], chapterName[MAXBUFF_50], filePath[MAXBUFF_50];
	int status;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter chapter name :");
	scanf("%s",chapterName);
	printf("\tEnter new file path :");
	scanf("%s",filePath);
	status = updateChapter(courseNo,chapterName,filePath);
	if(status == FAILURE)
		printf("\t!! Course `%s` & chpter name `%s` not found to update serial number !!\n",courseNo,chapterName);
	else
		printf("\t!! Chapter updated successfully !!\n");
	return status;
	
}
int deleteChapter()
{
	char courseNo[MAXBUFF_50],chapterName[MAXBUFF_50];
	int status;
	printf("Enter course number : \n");
	scanf("%s",courseNo);
	printf("Enter chapter name : \n");
	scanf("%s",chapterName);
	status = deleteChapterFromList(courseNo,chapterName);
	if(status == FAILURE)
		printf("\t!! Chapter not found for course `%s` !!\n",courseNo);
	else
		printf("\t!! Chapter deleted successfully !!\n");

	return status;

}


/**** completed chapter logic ***/
completedChapter* createCompletedChapter(char *userName,char *courseNo,char *chapterName,char *completionDate)
{
	
	completedChapter* ch = (completedChapter *)malloc(sizeof(completedChapter));	
	
	ch->userName = (char*)malloc(strlen(userName)*sizeof(char));
	ch->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	ch->chapterName =(char*)malloc(strlen(chapterName)*sizeof(char));
	ch->completionDate =(char*)malloc(strlen(completionDate)*sizeof(char));
	strcpy(ch->userName,userName);
	strcpy(ch->courseNo,courseNo);
	strcpy(ch->chapterName,chapterName);
	strcpy(ch->completionDate,completionDate);
	ch->next = NULL;
	return ch;
		
}

int addCompletedChapterToList(completedChapter *cc)
{
	if(completedChaptersList == NULL)
		{
			completedChaptersList = (completedChapters*)malloc(sizeof(completedChapters));
			completedChaptersList->front =NULL;
			completedChaptersList->rear = NULL;

		}
		if(completedChaptersList->front == NULL)
		{
			completedChaptersList->front = cc;
			
		}
		if(completedChaptersList->rear == NULL)
		{
			completedChaptersList->rear = cc;
		}			
		else{
			completedChaptersList->rear->next = cc;
			completedChaptersList->rear = cc;
			
		}
		return SUCCESS;
}
int markChapterAsCompletedForUser(char *username,char *courseNo,char *chapterName)
{
	//char *courseNo = getCourseNumber(courseName);
	char *completionDate = getCurrentDateStr();
		
	if(!isChapterExist(courseNo,chapterName))
	{
		printf("\t!! Chapter %s not found under course %s !!",chapterName,courseNo);
		return FAILURE;
	}
	completedChapter *cc=createCompletedChapter(courseNo,chapterName,username,completionDate);
	addCompletedChapterToList(cc);	
	return SUCCESS;
}
int checkIfChapterIsCompletedForUser(char *userName,char *courseNo,char *chapterName)
{
	for(completedChapter *temp;temp!=NULL;temp=temp->next)
	{
		if(strcmp(temp->userName,userName) == 0 
		&& strcmp(temp->courseNo,courseNo) == 0
		&& strcmp(temp->chapterName,chapterName) == 0)
		{
			return 1;
		}
	}
	return 0;
}
int isAllChapterOfCourseCompletedForUser(char *userName,char *courseNo)
{
	int isCompleted =1;
	if(completedChaptersList == NULL)
	{
		isCompleted = 0;
	}
		
	else if(chapterList == 0)
	{
		isCompleted =  0;
	}		
	else{
		for(chapter *temp;temp!=NULL;temp=temp->next)
		{
			if(strcmp(temp->courseNo,courseNo) == 0)
			{
				if(checkIfChapterIsCompletedForUser(userName,courseNo,temp->chapterName) == 0)
				{
					isCompleted = 0;
					break;
					
				}
			}
		}
	}
	
	return isCompleted;
}

int loadCompletedChapters()
{
	FILE* file;
	char buffer[MAX_BUFFER];
	char **data;
	file = fopen("./data/completion.txt", "r");
	
	if(file == NULL)
		return FAILURE;

	completedChapter *c;
	//printf("entering whileLoop\n");
	// while(fgets(buffer, bufferLength, file))
	while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
	{
		
		//printf("%s,%ld\n",buffer,strlen(buffer));
		data = parseDataFromLine(buffer,",");
		c = createCompletedChapter(data[0],data[1],data[2],data[3]);
		addCompletedChapterToList(c);

	}

	fclose(file);
	return SUCCESS;

}
int saveCompletedChapters()
{
	if(completedChaptersList == NULL)
		return FAILURE;
	FILE *file;
	file = fopen("./data/completion.txt","wt");
	for(completedChapter* temp= completedChaptersList->front ; temp!= NULL; temp = temp->next)
	{		
		fprintf(file , "%s,%s,%s,%s\n",temp->userName,temp->courseNo,temp->chapterName,temp->completionDate);		
	}
	fclose(file);
	return SUCCESS;

}