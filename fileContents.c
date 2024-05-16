//This file was created as a test to print the contents of the file created by 1320project.c

#include <stdio.h>

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
    int locked;
};

int main() {
    FILE *file = fopen("user_data.txt", "r");

    if (file == NULL) {
        printf("Error: Unable to open the user data file.\n");
        return 1;
    }

    struct UserAccount user;

    printf("User Information:\n");

    while (fread(&user, sizeof(struct UserAccount), 1, file) == 1) {
        printf("Username: %s\n", user.username);
        printf("Password: %s\n", user.password);
        printf("Balance: %.2f\n", user.balance);
        printf("Name: %s\n", user.name);
        printf("Birthday: %s\n", user.birthday);
        printf("Social Security: %s\n", user.socialSecurity);
        printf("Phone Number: %s\n", user.phoneNum);
        printf("Street Address: %s\n", user.streetAddress);
        printf("PIN: %d\n", user.pin);
        printf("Account Number: %d\n", user.accNum);
        printf("Locked: %d\n", user.locked);
        printf("\n");
    }

    fclose(file);

    return 0;
}
