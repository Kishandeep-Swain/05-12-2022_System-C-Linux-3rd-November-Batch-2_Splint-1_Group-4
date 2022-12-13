#ifndef BOOKMARK_H
#define BOOKMARK_H
int loadBookamrks();
int saveBookmarks();
void displayCompletedCoursesForUser(char *userName);
int updateBookMarkChapterCompletionDateForUser(char *userName,char* courseNo,char *chapterName,char* completionDate);
int addBookMarkForUser(char* courseNo,char* chapterName,char* username,int pageNo);
#endif