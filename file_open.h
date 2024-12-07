#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dirent.h>

extern char current_username[MAX_USERNAME];

void printFileContents(const char *filename)
{
    FILE *fptr;
    char ch;

    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error: Could not open file '%s'!\n", filename);
        Sleep(2000);
        return;
    }

    printf("\n--- Contents of the file '%s' ---\n", filename);
    while ((ch = fgetc(fptr)) != EOF)
    {
        putchar(ch);
    }

    fclose(fptr);
    printf("\n--- End of File ---\n");
    printf("Press any key to return to the menu...");
    getch();
}

void openNote()
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

    printf("Enter the filename to open (without path): ");
    scanf("%s", filename);


    snprintf(filepath, sizeof(filepath), "notes/%s/%s", current_username, filename);

    printFileContents(filepath);
}
