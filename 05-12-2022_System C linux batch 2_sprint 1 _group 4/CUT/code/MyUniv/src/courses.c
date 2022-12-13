#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <common.h>


typedef struct course course;

struct course{
char* courseNo;
char *courseName;
course *next;
};

typedef struct {
course* front;
course* rear;
}courses;

courses *courseList;

typedef struct enrollment enrollment;

struct enrollment{
char *courseNo;
char *userName;
char *enrollDate;
char *status;
char* completionDate;
enrollment *next;
};

typedef struct {
enrollment* front;
enrollment* rear;
}enrollments;

enrollments *enrollmentList;


int getLastCourseId()
{
	if(courseList == NULL)
	{
		return 0;
	}
	if(courseList->rear == NULL)
		return 0;
	
	int lastId=atoi(subStr(courseList->rear->courseNo,1,strlen(courseList->rear->courseNo)-1));
	printf("\tLast Id : %d\n",lastId);
	return lastId;
}

char* generateCourseNo()
{
	char courseCountStr[4]; 
	sprintf(courseCountStr,"%d",(getLastCourseId()+1));
	char* paddingStr = leftpadzero(courseCountStr,4);
	char *courseNo = (char*)malloc(strlen(paddingStr)+1);
	sprintf(courseNo,"C%s",paddingStr);	
	return courseNo;
}
course *createCourse(char* courseNo,char *courseName)
{
	
	course *co = (course*)malloc(sizeof(course));	
	co->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	co->courseName =(char*)malloc(strlen(courseName)*sizeof(char));
	strcpy(co->courseNo,courseNo);
	strcpy(co->courseName,courseName);
	co->next = NULL;
	return co;
		
}
int updateCourse(char *courseNo,char* courseName)
{
	if(courseList == NULL)
		return FAILURE;
	for(course *temp = courseList->front;temp!=NULL;temp=temp->next)
	{
		if(strcmp(temp->courseNo,courseNo) == 0)
		{
			strcpy(temp->courseName,courseName);
			return SUCCESS;
		}
	}
	return FAILURE;
}
int addCourseToList(course *newCourse)
{
		if(courseList == NULL)
		{
			courseList = (courses*)malloc(sizeof(courses));
			courseList->front =NULL;
			courseList->rear = NULL;
			//courseList->courseCount=0;

		}
		if(courseList->front == NULL)
		{
			courseList->front = newCourse;
			
		}
		if(courseList->rear == NULL)
		{
			courseList->rear = newCourse;
		}			
		else{
			courseList->rear->next = newCourse;
			courseList->rear = newCourse;
			
		}
		return SUCCESS;
}



int loadCourses()
{
        FILE* file;
        
        char buffer[MAX_BUFFER]; /* not ISO 90 compatible */
		char **data;
        file = fopen("./data/courses.txt", "r");
		
		if(file == NULL)
			return FAILURE;

		course *c;
		//printf("entering whileLoop\n");
       // while(fgets(buffer, bufferLength, file))
		while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
        {
			//printf("%s,%ld\n",buffer,strlen(buffer));
			data = parseDataFromLine(buffer,",");
			c = createCourse(data[0],data[1]);
			addCourseToList(c);
        }
        fclose(file);
		return SUCCESS;

}

int deleteCourseFromList(char* courseNo) {
	//printf("Delete course number %s:\n",courseNo);
    course *prev = NULL, *temp = NULL, *current= NULL;
	if(courseList==NULL)
	{
		printf("\tThere is no course to delete\n");
		return FAILURE;
	}
	if(courseList->front == NULL && courseList->rear == NULL)
	{
		printf("\tThere is no course to delete\n");
		return FAILURE;
	}
	if(courseList->front == courseList->rear)
	{
		if(strcmp(courseList->front->courseNo,courseNo) == 0)
		{
			temp=courseList->front;
			free(temp);
			courseList->front = NULL;
			courseList->rear = NULL;
			return SUCCESS;
		}
		
	}
	else
	{
		current = courseList->front;
		
		while(current!=NULL)
		{
		if(strcmp(current->courseNo,courseNo) == 0)
		{
			temp = current;
			
			//temp->next = prev?temp->next:NULL;
			if(current == courseList->front)
			{
				//printf("Course found in front\n");
				courseList->front = current->next;
			}
			else if(current == courseList->rear)
			{
				//printf("Course found in rear\n");
				courseList->rear = prev;
				courseList->rear->next = NULL;
			}
			else
			{
				//printf("Course found in middle\n");
				prev->next = current->next;
				
			}
			//courseList->courseCount--;
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



void displayCourselist()
{
	if(courseList == NULL)
	{
		printf("\t!! No courses to display !!\n");
		return;
	}
	if(courseList->front == NULL)
	{
		printf("\t!! No courses to display !!\n");
		return;
	}
	printf("\tTHE LIST OF courses ARE\n");
	//printf("Total number of course : %d\n",courseList->courseCount);
	for(course* temp= courseList->front ; temp!= NULL; temp = temp->next)
	{
		printf("\tcourseNo : %s , courseName : %s\n",temp->courseNo,temp->courseName);
	}
}

int saveCourses()
{
	if(courseList == NULL)
		return FAILURE;
	FILE *file;
	file = fopen("./data/courses.txt","wt");
	for(course* temp= courseList->front ; temp!= NULL; temp = temp->next)
	{
		
		fprintf(file , "%s,%s\n",temp->courseNo,temp->courseName);
		
	}
	fclose(file);	
return SUCCESS;
}
char* getCourseNumber(char* courseName)
{
	char *courseNo= (char*)malloc(MAXBUFF_50);
	if(courseList == NULL)
	{
		return NULL_STR;
	}
	if(courseList->front == NULL)
	{
		return NULL_STR;
	}
	//printf("searching course\n");
	
	for(course* temp= courseList->front ; temp!= NULL; temp = temp->next)
	{
		//printf("for loop : %s\n",temp->courseName);
		if(strcmp(courseName,temp->courseName)==0)
		{
			strcpy(courseNo,temp->courseNo);
			return courseNo;
		}
	}
	return NULL_STR;
}

int isCourseExists(char* courseName)
{
	char *courseNo = getCourseNumber(courseName);
	printf("%s\n",courseNo);
	if(strcmp(courseNo,NULL_STR)!=0)
		return SUCCESS;
	return FAILURE;
}
char* getCourseName(char* courseNo)
{
	char *courseName = malloc(MAXBUFF_50);
	if(courseList == NULL)
	{
		return NULL_STR;
	}
		
	for(course* temp= courseList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseNo,temp->courseNo)==0)
		{
			strcpy(courseName,temp->courseName);
			return courseName;
		}
	}
	
	return NULL_STR;
}
int addCourse()
{
	char courseName[MAXBUFF_50];
	char *courseNo;
	printf("\tEnter course name :");
	scanf("%s",courseName);
	//fgets(courseName,MAXBUFF_50,stdin);
	printf("\tentered course name  = %s\n",courseName);
//printf("course is saving\n");
	if(isCourseExists(courseName)==1)
	{
		printf("\t!! Course already exists !!\n");
		return FAILURE;
	}
	//printf("course Added\n");
	courseNo = generateCourseNo();
	//printf("course Added\n");
	
	course *c = createCourse(courseNo,courseName);
	addCourseToList(c);
	//printf("course Added\n");
	
	displayCourselist();
	return SUCCESS;
}
int modifyCourse()
{
	char courseName[MAXBUFF_50];
	char courseNo[MAXBUFF_50];	
	int status;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	printf("\tEnter new course name :");
	scanf("%s",courseName);
	status = updateCourse(courseNo,courseName);
	if(status == 0)
	{
		printf("\t!! CourseNo `%s` not found to update!!\n",courseNo);
		return FAILURE;
	}
	printf("\t!! Course updated successfully !!\n");
	return SUCCESS;
	
}
int deleteCourse()
{
	char courseNo[MAXBUFF_50];	
	int status;
	printf("\tEnter course number :");
	scanf("%s",courseNo);
	status = deleteCourseFromList(courseNo);
	if(status == 0)
		printf("\t!! Course No `%s` not found to delete !!\n",courseNo);
	else
		printf("\t!! Course deleted Successfully !!\n");
	return status;
}


/***** Enrollment Course logic ****/


enrollment* createEnrollment(char* courseNo, char* userName,char* enrollmentDate,char* status,char* completionDate)
{
	
	enrollment* en = (enrollment *)malloc(sizeof(enrollment));
	
	en->courseNo = (char*)malloc(strlen(courseNo)*sizeof(char));
	en->enrollDate =(char*)malloc(strlen(enrollmentDate)*sizeof(char));
	en->userName=(char*)malloc(strlen(userName)*sizeof(char));
	en->status=(char*)malloc(strlen(status)*sizeof(char));
	en->completionDate=(char*)malloc(strlen(completionDate)*sizeof(char));


	strcpy(en->courseNo,courseNo);
	strcpy(en->enrollDate,enrollmentDate);
	strcpy(en->userName,userName);
	strcpy(en->status,status);
	strcpy(en->completionDate,completionDate);

	

	en->next = NULL;
	return en;
		
}

int addEnrollmentToList(enrollment *newEnrollment)
{
	if(enrollmentList == NULL)
	{
		enrollmentList = (enrollments*)malloc(sizeof(enrollments));
		enrollmentList->front =NULL;
		enrollmentList->rear = NULL;

	}
	if(enrollmentList->front == NULL)
	{
		enrollmentList->front = newEnrollment;
		
	}
	if(enrollmentList->rear == NULL)
	{
		enrollmentList->rear = newEnrollment;
	}			
	else{
		enrollmentList->rear->next = newEnrollment;
		enrollmentList->rear = newEnrollment;
		
	}
	return SUCCESS;
}

int loadEnrollments()
{
	FILE* file;
	char buffer[MAX_BUFFER]; /* not ISO 90 compatible */
	char **data;
	file = fopen("./data/enrollments.txt", "r");
	if(file == NULL)
		return FAILURE;
	enrollment *e;
	//printf("entering whileLoop\n");       
	while(fscanf(file,"%[^\n]\n",buffer)!= EOF)
	{
		
		//printf("%s,%ld\n",buffer,strlen(buffer));
		data = parseDataFromLine(buffer,",");
		e = createEnrollment(data[0],data[1],data[2],data[3],data[4]);
		addEnrollmentToList(e);

	}

	fclose(file);
	return SUCCESS;

}

void displayCompletedCoursesForUser(char *userName)
{
	if(enrollmentList == NULL)
	{
		printf("\t!! No enrollments to display !!\n");
		return;
	}
	
	//printf("Total number of course : %d\n",course_list->courseCount);
	for(enrollment* temp= enrollmentList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(userName,temp->userName) == 0 && strcmp("completed",temp->status) == 0)
		{
			printf("\tcourseNo : %s , courseName : %s, completedOn : %s\n",temp->courseNo,getCourseName(temp->courseNo),temp->completionDate);
		}
		
	}
	
}
int updateEnrollmentStatus(char *courseNo,char *userName,char *status,char* completionDate)
{
	if(enrollmentList == NULL)
		return FAILURE;
	for(enrollment* temp= enrollmentList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseNo,temp->courseNo) == 0  && strcmp(userName,temp->userName) == 0)
		{
			strcpy(temp->status,status);
			strcpy(temp->completionDate,completionDate);
			break;
		}
		
	}
	return SUCCESS;
}

int saveEnrollments()
{
	if(enrollmentList == NULL)
		return FAILURE;

	FILE *file;
	file = fopen("./data/enrollments.txt","wt");
	for(enrollment* temp= enrollmentList->front ; temp!= NULL; temp = temp->next)
	{		
		fprintf(file , "%s,%s,%s,%s,%s\n",temp->courseNo,temp->userName,temp->enrollDate,temp->status,temp->completionDate);		
	}
	fclose(file);
	return SUCCESS;

}

int addEnrollmentForUser(char *courseNo,char *username,char *date,char *status,char* completionDate)
{
	//if(enrollmentList == NULL)
	//	return FAILURE;
	//printf("%s ,%s ,%s , %s\n",courseNo,username, date , status);
	enrollment *en = createEnrollment(courseNo,username,date,status,completionDate);
	addEnrollmentToList(en);
	return SUCCESS;
}
int enrollCourse(char* courseName,char* username)
{
	char *courseNo = getCourseNumber(courseName);
	char* date = getCurrentDateStr();
	char status[MAXBUFF_50] = "inprogress";
	//printf("courseNo : %s\n",courseNo);
	if(strcmp(courseNo,NULL_STR)==0)
	{
		
		printf ("/t!! Course `%s` not found to enroll !!\n",courseName);
		return FAILURE;
	}
	return addEnrollmentForUser(courseNo,username,date,status,"NA");

}

int searchCourse(char * courseName)
{
	int courseFound = 0;

	if(courseList == NULL)
	{
		return courseFound;
	}
	if(courseList->front == NULL)
	{
		return courseFound;
	}
	
	for(course* temp= courseList->front ; temp!= NULL; temp = temp->next)
	{
		if(strcmp(courseName,temp->courseName))
		{
			courseFound = 1;
			break;
		}
	}
	
	return courseFound;
	
	
}

void displayEnrollmentList()
{
	if(enrollmentList == NULL)
	{
		printf("\t!! No enrollments to display !!\n");
		return;
	}
	if(enrollmentList->front == NULL)
	{
		printf("\t!! No enrollments to display !!\n");
		return;
	}
	//printf("\t|\tCourseNo\t|\tUserName\t|\tEnrolmentDate\t|\tStatus\t|\tCompletionDate\t|\n");
	//printf("Total number of course : %d\n",courseList->courseCount);
	for(enrollment* temp= enrollmentList->front ; temp!= NULL; temp = temp->next)
	{
		//printf("\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\n",temp->courseNo,temp->userName,temp->enrollDate,temp->status , temp->completionDate);
		printf("\tcourseNo : %s , userName : %s , enrollmentDate : %s , status : %s , completionDate : %s\n",temp->courseNo,temp->userName,temp->enrollDate,temp->status , temp->completionDate);
	}
}






