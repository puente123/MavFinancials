#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//Define Transaction Structure
struct Transaction{
    char date[50];
    double amount;
};
// User accounts structure
struct UserAccount {
    char username[50];
    char password[50];
    double balance;
    char name[20];
    char birthday[11];
    char socialSecurity[10];
    char phoneNum[11];
    char streetAddress[50];
    int pin;
    int accNum;
    //0-Unlocked 1-Locked
    int locked;
    //Nested structure to search transactions;
    struct Transaction *transactions;
    int transactionNumber;
};

int checkUsername(FILE *file, char *username);
void getCurrentDate(char *print);
void viewTransactions(FILE *file, char* username);
void registerUser(FILE* file);
int login(FILE* file, char* username, char* password);
void transfer(FILE *file, char* username);
void viewBalance(FILE *file, char* username);
void viewAccount(FILE *file, char* username);
void lockcard(FILE *file, char* username);
void printLogo();
void removeNewline(char* str);
int isValidPassword(char *pass);




#endif