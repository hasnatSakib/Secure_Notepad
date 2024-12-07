#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define CREDENTIALS_FILE "users.txt"
#define NOTES_BASE_DIR "notes\\"

void signUp()
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char buffer[100];
    char user_notes_dir[200];
    FILE *fptr;

    printf("Enter a new username: ");
    scanf("%s", username);


    fptr = fopen(CREDENTIALS_FILE, "r");
    if (fptr != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fptr))
        {
            char existingUsername[MAX_USERNAME];
            sscanf(buffer, "%[^:]", existingUsername);
            if (strcmp(existingUsername, username) == 0)
            {
                printf("Error: Username '%s' already exists.\n", username);
                fclose(fptr);
                return;
            }
        }
        fclose(fptr);
    }


    snprintf(user_notes_dir, sizeof(user_notes_dir), "%s%s", NOTES_BASE_DIR, username);
    if (_mkdir(user_notes_dir) != 0)
    {
        printf("Error: Could not create user directory.\n");
        return;
    }


    fptr = fopen(CREDENTIALS_FILE, "a");
    if (fptr == NULL)
    {
        printf("Error: Could not open credentials file.\n");
        Sleep(3000);
        return;
    }
    printf("Enter a new password: ");
    scanf("%s", password);

    fprintf(fptr, "%s:%s\n", username, password);
    fclose(fptr);

    printf("Sign-up successful! Welcome, %s.\n", username);
    Sleep(2000);
}
