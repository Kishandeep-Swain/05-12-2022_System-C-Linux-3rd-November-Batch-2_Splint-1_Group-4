#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <common.h>

typedef struct bookmark bookmark;

struct bookmark{
char *userName;
char* courseNo;
char *chapterName;
int pageNo;
char* completionDate;
bookmark *next;
};

typedef struct {
bookmark* front;
bookmark* rear;

}bookmarks;

bookmarks *bookMarkList;

bookmark *createBookmark(char *userName,char* courseNo,char *chapterName , int pageNo,char* completionDate)
{
	
	bookmark *b = (bookmark*)malloc(sizeof(bookmark));
	
	
	b->userName = (char*)malloc(strlen(userName)*sizeof(char));
	b->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	b->chapterName =(char*)malloc(strlen(chapterName)*sizeof(char));
	b->completionDate =(char*)malloc(strlen(completionDate)*sizeof(char));

	strcpy(b->userName,userName);
	strcpy(b->courseNo,courseNo);
	strcpy(b->chapterName,chapterName);
	strcpy(b->completionDate,completionDate);
	b->pageNo = pageNo;
	b->next = NULL;
	//printf("%s,%s,%s,%d\n",b->courseNo,b->chapterName,b->userName,b->pageNo);
	return b;
		
}

int addBookmarkToList(bookmark *newBookmark)
{
	if(bookMarkList == NULL)
	{
		bookMarkList = (bookmarks*)malloc(sizeof(bookmarks));
		bookMarkList->front =NULL;
		bookMarkList->rear = NULL;

	}
	if(bookMarkList->front == NULL)
	{
		bookMarkList->front = newBookmark;
		
	}
	if(bookMarkList->rear == NULL)
	{
		bookMarkList->rear = newBookmark;
	}			
	else{
		bookMarkList->rear->next = newBookmark;
		bookMarkList->rear = newBookmark;
		
	}
	return SUCCESS;
}



int loadBookamrks()
{
        FILE* file;
        //int bufferLength = 255;
        char buffer[MAX_BUFFER]; /* not ISO 90 compatible */
		char **data;
        file = fopen("./data/bookmarks.txt", "r");
		if(file == NULL)
			return FAILURE;

		bookmark *b;
		//printf("entering whileLoop\n");
       // while(fgets(buffer, bufferLength, file))
		while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
        {
			
		removeTrailing(buffer);
		//printf("%s,%ld\n",buffer,strlen(buffer));
		data = parseDataFromLine(buffer,",");
		b = createBookmark(data[0],data[1],data[2],atoi(data[3]),data[4]);
		addBookmarkToList(b);
        }

        fclose(file);
		
		return SUCCESS;


}

void displayBookMarkList()
{
	if(bookMarkList == NULL)
	{
		printf("\t!! No bookmarks to display !!\n");
		return;
	}
	if(bookMarkList->front == NULL)
	{
		printf("\t! No bookmarks to display !!\n");
		return;
	}
	printf("THE LIST OF BOOKMARKS ARE\n");
	//printf("Total number of course : %d\n",course_list->courseCount);
	for(bookmark* temp= bookMarkList->front ; temp!= NULL; temp = temp->next)
	{
		printf("userName :%s, courseNo : %s , chapterName : %s , page No : %d\n",temp->userName,temp->courseNo,temp->chapterName,temp->pageNo);
	}
	printf("\tEnd of list\n");
}



int updateBookMarkChapterCompletionDateForUser(char *userName,char* courseNo,char *chapterName,char* completionDate)
{
    if(bookMarkList == NULL)
		return FAILURE;
	for(bookmark* temp = bookMarkList->front;temp!=NULL;temp=temp->next)
	{
		if(strcmp(userName,temp->userName) == 0 && strcmp(courseNo,temp->courseNo) == 0
		&& strcmp(chapterName,temp->chapterName) == 0)
		{
			strcpy(temp->completionDate,completionDate);
			//return SUCCESS;
		}
	}
	return SUCCESS;
}

int saveBookmarks()
{
	if(bookMarkList == NULL)
		return FAILURE;
	FILE *file;
	file = fopen("./data/bookmarks.txt","wt");
	
	for(bookmark* temp= bookMarkList->front ; temp!= NULL; temp = temp->next)
	{
		
		fprintf(file , "%s,%s,%s,%d,%s\n",temp->userName,temp->courseNo,temp->chapterName,temp->pageNo,temp->completionDate);
		
	}
	fclose(file);
	return SUCCESS;

}
int addBookMarkForUser(char* courseNo,char* chapterName,char* username,int pageNo)
{
	//if(bookMarkList == NULL)
	//	return FAILURE;
	bookmark *b = createBookmark(username,courseNo,chapterName,pageNo,"NA");
	addBookmarkToList(b);
	return SUCCESS;
}