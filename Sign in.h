#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define CREDENTIALS_FILE "users.txt"


extern char current_username[MAX_USERNAME];

char current_username[MAX_USERNAME] = {0};

int logIn() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char buffer[100];
    FILE *fptr;

    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    fptr = fopen(CREDENTIALS_FILE, "r");
    if (fptr == NULL) {
        printf("Error: Could not open credentials file.\n");
        Sleep(2000);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fptr)) {
        char fileUsername[MAX_USERNAME];
        char filePassword[MAX_PASSWORD];
        sscanf(buffer, "%[^:]:%s", fileUsername, filePassword);

        if (strcmp(fileUsername, username) == 0 && strcmp(filePassword, password) == 0) {
            strcpy(current_username, username);
            fclose(fptr);
            printf("Login successful! Welcome back, %s.\n", username);
            Sleep(2000);
            return 1;
        }
    }

    fclose(fptr);
    printf("Error: Invalid username or password.\n");
    Sleep(2000);
    return 0;
}
