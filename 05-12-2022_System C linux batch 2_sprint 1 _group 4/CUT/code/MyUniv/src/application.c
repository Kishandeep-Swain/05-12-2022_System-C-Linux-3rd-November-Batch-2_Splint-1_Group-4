#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "user.h"
#include "courses.h"
#include "chapters.h"
#include "bookmark.h"
#include "link.h"
void loadApplication()
{
	//printf("loadUsers\n");
	
	loadUsers();
	//printf("loadCourses\n");
	loadCourses();
	//printf("loadEnrollments\n");
	loadEnrollments();
	//printf("loadChapters\n");
	loadChapters();
	//	printf("loadLinks\n");

	loadLinks();
	//	printf("loadCompletedChapters\n");

	loadCompletedChapters();
	//	printf("loadBOOkmarks\n");

	loadBookamrks();
}
void saveApplication()
{
	saveUsers();
	saveCourses();
	saveEnrollments();
	saveChapters();
	saveCompletedChapters();
	saveBookmarks();
	saveLinks();
}