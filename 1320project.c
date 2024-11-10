//This is the main source file
//It handles how the menu is displayed and how each function is called and interacts with each other.

#include "project.c"
#include "project.h"


int main() {
    //Opens file to store structures
    FILE* userFile = fopen("user_data.txt", "a+");

    if (userFile == NULL) {
        printf("Error: Unable to open the user data file.\n");
        return 1;
    }

    int choice, exit = 0;
    //struct UserAccount mainUser;
    
    char username[50], password[50];

    //While loop for entry screen
    while (1) {
        exit = 0;
        
        //Did not include logo becuase it caused code to glitch on ocassions.
        printLogo();

        printf(BLUE"\nWelcome to Mav Financials!\n"RESET);
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                registerUser(userFile);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                                    
                if (login(userFile, username, password) == 1) {

                    //Insert functions here
                    while(!exit){
                        printf("\n1. Transfer Money\n");
                        printf("2. View Balance\n");
                        printf("3. View Previous Transactions\n");
                        printf("4. View Account Information\n");
                        printf("5. Lock/Unlock Card\n");
                        printf("6. Logout\n");
                        printf("Enter your choice: ");

                        if (scanf("%d", &choice) != 1) {
                            printf("Invalid input. Please enter a number.\n");
                            
                            while (getchar() != '\n');
                            continue;
                        }

                        switch(choice) {
                            case 1:
                                //Transfers money between users
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                transfer(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;

                            case 2:
                                viewBalance(userFile, username);
                                break;
                            
                            case 3:
                                viewTransactions(userFile, username);
                                break;
                            
                            case 4:
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                viewAccount(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;
                            
                            case 5:
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                lockcard(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;

                            case 6:
                                exit = 1;
                        } 
                    }
                }
                break;
            case 3:
                fclose(userFile);
                
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}

