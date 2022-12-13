#ifndef USER_H
#define USER_H


typedef struct user user;

struct user{
char* username;
char *password;
user *next;
};


int showUserMenu(user *u);
int isUserAdmin(char* userName);
int registerUser();
int loadUsers();
int saveUsers();
void displayUserList();
user* loginUser();
#endif
