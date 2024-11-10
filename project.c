#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

//Returns 1 if Username exists
int checkUsername(FILE *file, char *username){
    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file) == 1){
        if(strcmp(user.username, username) == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void printLogo(){
    printf(RED"   *                (                                         \n");
    printf(" (  `               )\\ )                                (     \n");
    printf(" )\\))(     )  )    (()/( (           )          (     ) )\\    \n");
    printf("((_)()\\ ( /( /((    /(_)))\\  (    ( /(  (     ( )\\ ( /(((_|   \n");
    printf("(_()((_))(_)|_))\\  (_))_((_) )\\ ) )(_)) )\\ )  )((_))(_))_ )\\  \n");
    printf(BLUE"|  \\/  ((_)__)((_) | |_  (_)_(_/(((_)_ _(_/( ((_|_|(_)_| ((_) \n");
    printf("| |\\/| / _` \\ V /  | __| | | ' \\)) _` | ' \\)) _|| / _` | (_-< \n");
    printf("|_|  |_\\__,_|\\_/   |_|   |_|_||_|\\__,_|_||_|\\__||_\\__,_|_/__/ \n"RESET);
}

//Returns month-day-year
void getCurrentDate(char *print){
    time_t t;
    struct tm* tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(print, 20, "%m-%d-%Y", tm_info);
}

//Prints the transactions for the current user
void viewTransactions(FILE *file, char* username){
    struct UserAccount user;

    fseek(file, 0, SEEK_SET);
    while(fread(&user, sizeof(struct UserAccount), 1, file) ==1 ){
        if(strcmp(user.username, username) == 0){
            printf(BLUE"DATE\t\tAMOUNT\n"RESET);
            for(int i=0; i < user.transactionNumber; i++){
               // printf("DATE\tAMOUNT");
               printf("%s\t%.2f\n", user.transactions[i].date, user.transactions[i].amount);
            }
        }
    }
}


//Creates a new user and saves their information to the file
void registerUser(FILE* file) {
    struct UserAccount user;
    int userExists = 1;
    fseek(file, 0, SEEK_END);
    
    while(userExists){
        printf("Enter username: ");
        scanf("%s", user.username);
        //Checks if username already exists
        if(checkUsername(file, user.username) == 1){
            printf(RED"Username Already Exists! Please Enter a Different Username.\n"RESET);
        }
        else{
            userExists = 0;
        }
    }
    
    fseek(file, 0, SEEK_END);

    int passwordValid=0;
    char tempPass[50];
    while(passwordValid==0)
    {
      printf("Enter password: ");
      scanf("%s", tempPass);  
      passwordValid= isValidPassword(tempPass);
    }
    strcpy(user.password, tempPass);


    printf(YELLOW"Username and Password Set Succesfully!!\n\n"RESET);
    printf(MAGENTA"Now Input your Personal Information: \n"RESET);

    getchar();
    
    //Setting up Personal Information
    printf("Enter your full name: ");
    fgets(user.name, 20, stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    printf("Enter your birthday in the formath MM/DD/YYYY: ");
    scanf("%s", user.birthday);
    printf("Enter your 9 digit Social Security Number: ");
    scanf("%s", user.socialSecurity);
    printf("Enter your 10 digit Phone Number: ");
    scanf("%s", user.phoneNum);
    getchar();
    printf("Enter your full address: ");
    fgets(user.streetAddress, 30, stdin);
    user.streetAddress[strcspn(user.streetAddress, "\n")] = '\0';
    user.locked = 0;
    user.balance = 400.0;
    user.transactionNumber = 0;

    user.transactions = malloc(10 * sizeof(struct Transaction));
    if (user.transactions == NULL) {
        perror("Error allocating memory for transactions");
        exit(EXIT_FAILURE);
    }

   
    if (fwrite(&user, sizeof(struct UserAccount), 1, file) != 1) {
        perror("Error writing to file");
    } else {
        printf(YELLOW"Account created successfully!\n"RESET);
    }

}


//Verifies that the username and password match the one saved in the file
int login(FILE* file, char* username, char* password) {
    struct UserAccount user;

    //Sets file pointer to beggining of file
    fseek(file, 0, SEEK_SET);
    
    while (fread(&user, sizeof(struct UserAccount), 1, file) == 1) {
        
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            printf(YELLOW"Login successful. Welcome, %s!\n"RESET, user.username);
            return 1;
        }
    
    }

    printf(RED"Invalid username or password. Please try again.\n"RESET);
    return 0;
}

//Transfers money from one user to another user
void transfer(FILE *file, char* username){
    struct UserAccount user, user2;
    double transferAmount;
    char reciever[20];

    printf("Enter the username of the person you wish to send money to \n");
    scanf("%s", reciever);
    printf("How much would you like to send to %s \n", reciever);
    scanf("%lf", &transferAmount);
    
    //Sets file pointer to beggining of file
    fseek(file, 0, SEEK_SET);

    
    while (fread(&user, sizeof(struct UserAccount), 1, file) == 1) {
        if (strcmp(user.username, username) == 0) {

            long userPosition = ftell(file);
            fseek(file, 0, SEEK_SET);
            
            while (fread(&user2, sizeof(struct UserAccount), 1, file) == 1) {
                if (strcmp(user2.username, reciever) == 0) {

                    //Adjust the balance for each account
                    user.balance -= transferAmount;
                    user2.balance += transferAmount;
                    
                    //Adjust Transaction Details(In progress)
                    user.transactions[user.transactionNumber].amount = 0 - transferAmount;
                    getCurrentDate(user.transactions[user.transactionNumber].date);
                    user.transactionNumber++;

                    user2.transactions[user2.transactionNumber].amount = transferAmount;
                    getCurrentDate(user2.transactions[user2.transactionNumber].date);
                    user2.transactionNumber++;

                    /*
                     if (user.transactionNumber % 10 == 0) {
                        user.transactions = realloc(user.transactions, (user.transactionNumber + 10) * sizeof(struct Transaction));
                        if (user.transactions == NULL) {
                            perror("Error reallocating memory for transactions");
                            exit(EXIT_FAILURE);
                        }
                    }

                    // If the number of transactions exceeds the allocated capacity for user2, reallocate memory
                    if (user2.transactionNumber % 10 == 0) {
                        user2.transactions = realloc(user2.transactions, (user2.transactionNumber + 10) * sizeof(struct Transaction));
                        if (user2.transactions == NULL) {
                            perror("Error reallocating memory for transactions");
                            exit(EXIT_FAILURE);
                        }
                    }*/
                    
                
                    //Send information to file
                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    fwrite(&user2, sizeof(struct UserAccount), 1, file);

                    fseek(file, userPosition, SEEK_SET);
                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    fwrite(&user, sizeof(struct UserAccount), 1, file);

                    
                    printf(CYAN"Money Transferred Succesfully\n"RESET);
                    return;
                }
            }
             printf(RED"Reciever not found\n"RESET);
        }
    }
}


//This function prints the current users balance
void viewBalance(FILE *file, char* username){

    //Resets file pointer to beggining
    struct UserAccount u;
    fseek(file, 0, SEEK_SET);

    //Finds the user with the same username, and prints their balance
    while(fread(&u, sizeof(struct UserAccount), 1, file) == 1)
        if(strcmp(u.username, username) == 0){
            printf(GREEN"Balance: $%.2f\n"RESET, u.balance);
        }    
}

//This function allows the user to view their account and make changes to information if necessary
void viewAccount(FILE *file, char* username){
    
    int input;
    int choice, exit=0;

    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file) == 1){
        if(strcmp(user.username, username) == 0){
            
            //The print statements display the current informmation
            printf("\nName: %s\n", user.name);
            printf("Username: %s\n", user.username);
            printf("Password: %s\n", user.password);
            printf("Birthday: %s\n", user.birthday);
            printf("Phone Number: %s\n", user.phoneNum);
            printf("Social Security %s\n", user.socialSecurity);
            printf("Address: %s\n", user.streetAddress);
            printf("Would you like to change this information?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Enter your choice: ");

            //If the user selected to edit information a new display pops up to select options
            while(1){
                scanf(" %d", &input);
                if(input == 1){
                    printf("\nSelect The Information to be Edited\n");
                    while(!exit){
                        printf("1. Username\n");
                        printf("2. Password\n");
                        printf("3. Birthday\n");
                        printf("4. Phone Number\n");
                        printf("5. Address\n");
                        printf("6. Exit\n");


                        if (scanf("%d", &choice) != 1) {
                            printf(RED"Invalid input. Please enter a number.\n"RESET);
                            //Prevents an infinite loop by clearing buffer
                            while (getchar() != '\n');
                            continue;
                        }

                        switch(choice){
                            case 1:
                                printf("Enter New Username: ");
                                scanf("%s", user.username);
                                break;
                            case 2:
                                printf("Enter New Password: ");
                                scanf("%s", user.password);
                                break;
                            case 3: 
                                printf("Edit your Birthday: ");
                                scanf("%s", user.birthday);
                                break;
                            case 4:
                                printf("Enter New Phone Number: ");
                                scanf("%s", user.phoneNum);
                                break;
                            case 5:
                                printf("Enter New Address: ");
                                getchar();
                                fgets(user.streetAddress, 30, stdin);
                                user.streetAddress[strcspn(user.streetAddress, "\n")] = '\0';
                                break;
                            case 6:
                                exit = 1;
                                break;
                            default:
                                printf("Invalid Choice\n");
                                break;
                        }  
                    }

                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    if (fwrite(&user, sizeof(struct UserAccount), 1, file) != 1) {
                        perror("Error writing to file");
                    } else {
                        printf(YELLOW"Information Edited successfully!\n"RESET);
                    }
                    return;
                }
                else if(input == 2){
                    return;
                }
                else{
                    printf(RED"Invalid Choice\n"RESET);
                }
            }
        }
    }
}

//If the user wishes to lock their card to avoid any transactions from occuring this function is called
void lockcard(FILE *file, char* username){
    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file)== 1){
        if(strcmp(user.username, username) == 0){
            if(user.locked == 1){
                user.locked = 0;
                printf(YELLOW"Card is now unlocked.\n"RESET);
                fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                fwrite(&user, sizeof(struct UserAccount), 1, file);
                return;
            }
            else if(user.locked == 0){
                user.locked = 1;
                printf(RED"Card is now locked.\n"RESET);
                fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                fwrite(&user, sizeof(struct UserAccount), 1, file);
                return;
            }
        }
    }
}


//This function checks if the password is valid
//It must be longer than 10 characters
//1 upercase, 1 lowercase, 1 number, 1 symbol
int isValidPassword(char *pass){

    int upercase=0,lowercase=0,num=0,sym=0,length=0;  
    if (strlen(pass)>10)
    {
        length=1;
    }
    else
    {
        printf(RED"Password too short.\n"RESET);
    }
    for (int i=0; i<strlen(pass);i++)
    {
        if((upercase==0) && isalpha(pass[i])!=0 && isupper(pass[i])!=0)
        {
            upercase=1;
        }
        else if((lowercase==0) && isalpha(pass[i])!=0 && islower(pass[i])!=0)
        {
            lowercase=1;
        }
        else if((num==0) && isdigit(pass[i])!=0)
        {
            num=1;
        }
        else if((sym==0) && ispunct(pass[i])!=0)
        {
            sym=1;
        }
        
    }
    if ((upercase==0))
    {
        printf(RED"Password must contain atleast one uppercase character.\n"RESET);
    }    
    if((lowercase==0))
    {
        printf(RED"Password must contain atleast one lowercase character.\n"RESET);
    }
    if ((num==0))
    {
        printf(RED"Password must contain atleast one digit [0-9].\n"RESET);
    }
    if ((sym==0))
    {
        printf(RED"Password must contain atleast one symbol.\n"RESET);
    }

    if(upercase==1 && lowercase==1 && num==1 && sym==1 && length==1){
        return 1;
    }
    else{
        return 0;
    }
}

