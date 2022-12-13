#ifndef ENROLL_H
#define ENROLL_H
int loadCourses();
int saveCourses();
int addCourse();
int modifyCourse();
int deleteCourse();
void displayCourselist();
int searchCourse(char* courseName);
char* getCourseNumber(char * courseName);
int enrollCourse(char* courseName,char* username);
int updateEnrollmentStatus(char *courseNo,char *userName,char *status,char* completionDate);
int loadEnrollments();
int saveEnrollments();
void displayEnrollmentList();
#endif
