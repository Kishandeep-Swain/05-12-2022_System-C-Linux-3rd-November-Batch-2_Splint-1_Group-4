#ifndef CHAPTER_H
#define CHAPTER_H
int loadChapters();
int saveChapters();
int addChapter();
int modifyChapter();
int deleteChapter();
int loadCompletedChapters();
int isChapterExist(char* courseNo,char* chapterName);
int saveCompletedChapters();
int markChapterAsCompletedForUser(char *username,char *courseName,char *chapterName);
int addCompletedChapter(char *username,char *courseNo,char *chapterName,char *completionDate);
int isAllChapterOfCourseCompletedForUser(char *userName,char *courseNo);
#endif