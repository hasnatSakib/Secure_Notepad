#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "headers.h"

void firstMenu();
void mainMenu();
void clear_screen();
int getValidIntChoice();
void createNote();
void deleteNote();

void firstMenu()
{
    clear_screen();
    printf("Secure Notepad\n");
    printf("--------------\n");
    printf("              \n");
    printf("1. Sign In\n");
    printf("2. Sign Up\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    int choice = getValidIntChoice();
    switch (choice)
    {
    case 1:
        if(logIn() == 1){
            getchar();
            mainMenu();
        }
        break;
    case 2:
        signUp();
        getchar();
        firstMenu();
        break;
    case 0:
        exit(0);
    default:
        printf("Invalid choice! Please try again.\n");
        Sleep(2000);
        firstMenu();
        break;
    }
}

void mainMenu()
{
    clear_screen();
    printf("Main Menu\n");
    printf("---------\n");
    printf("         \n");
    printf("1. Create Note\n");
    printf("2. Open Note\n");
    printf("3. Delete Note\n");
    printf("0. Log Out\n");
    printf("Enter your choice: ");
    int choice = getValidIntChoice();
    switch (choice)
    {
    case 1:
        createNote();
        mainMenu();
        break;
    case 2:
        openNote();
        mainMenu();
        break;
    case 3:
        deleteNote();
        mainMenu();
        break;
    case 0:
        memset(current_username, 0, sizeof(current_username));
        return;
    default:
        printf("Invalid choice! Please try again.\n");
        Sleep(3000);
        mainMenu();
        break;
    }
}

void clear_screen()
{
    system("cls");
}

int getValidIntChoice()
{
    char input[10];
    int choice;
    while (1)
    {
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) == 1)
        {
            return choice;
        }
        else
        {
            printf("Invalid input. Please enter a number: ");
        }
    }
}

void createNote()
{
    printf("Create Note\n");
    Sleep(1000);
    addFileContent();
}

void deleteNote()
{
    if (strlen(current_username) == 0) {
        printf("Error: Please log in first!\n");
        Sleep(2000);
        return;
    }

    char filename[100];
    char filepath[250];
    DIR *dir;
    struct dirent *ent;
    char user_notes_path[200];

    snprintf(user_notes_path, sizeof(user_notes_path), "notes/%s", current_username);

    dir = opendir(user_notes_path);
    if (dir == NULL) {
        printf("Error: Could not open user's notes directory.\n");
        Sleep(2000);
        return;
    }

    printf("Available notes:\n");
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            printf("- %s\n", ent->d_name);
        }
    }
    closedir(dir);

    printf("Enter the filename to delete (without path): ");
    scanf("%s", filename);

    snprintf(filepath, sizeof(filepath), "notes/%s/%s", current_username, filename);

    if (remove(filepath) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        printf("Error: Could not delete file '%s'.\n", filename);
    }

    Sleep(2000);
}

#endif // USER_INTERFACE_H
