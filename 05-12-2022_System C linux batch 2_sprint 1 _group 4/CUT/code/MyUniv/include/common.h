#ifndef COMMON_H
#define COMMON_H
#define MAX_BUFFER 1000
#define SUCCESS 1
#define FAILURE 0
#define MAXBUFF_50 50
#define NULL_STR "\0"
#define ENCRYPT_KEY 0xFACA
int loginMenu();
int courseMainMenu();
int chapterMainMenu();
int linkMainMenu();
int userMainMenu();
int adminMainMenu();
void removeLeading(char *str, char *str1);
void removeTrailing(char *str);
char** parseDataFromLine(char* line,char* delimeter);

char* subStr(char* str,int index, int size);
char* leftpadzero(char *myString, int pi_length);
char* getCurrentDateStr();
void encrypt(char* password,int key);

#endif