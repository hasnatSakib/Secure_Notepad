#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
extern char current_username[MAX_USERNAME];
void addFileContent()
{
    FILE *fptr;
    char filename[100];
    char filepath[250];
    char line[100];
    int index;


    if (strlen(current_username) == 0) {
        printf("Error: Please log in first!\n");
        Sleep(2000);
        return;
    }

    printf("Enter the filename (without path): ");
    scanf("%s", filename);

    snprintf(filepath, sizeof(filepath), "notes/%s/%s", current_username, filename);

    fptr = fopen(filepath, "w");

    if (fptr == NULL)
    {
        printf("Error: Could not open file for writing!\n");
        Sleep(2000);
        return;
    }
    system("cls");
    printf("Enter text for the file (press 'ESC' to save and exit):\n");
    getchar();

    while (1)
    {
        printf("\n> ");
        index = 0;

        while (1)
        {
            char ch = getch();
            if (ch == 27)
            {
                printf("\n[ESC detected. Exiting...]\n");
                Sleep(1500);
                fclose(fptr);
                printf("Text written to '%s' successfully!\n", filepath);
                printf("\n");
                printf("Press Enter to proceed...");
                getchar();
                return;
            }
            else if (ch == '\r')
            {
                line[index] = '\0';
                break;
            }
            else if (ch == '\b' && index > 0)
            {
                printf("\b \b");
                index--;
            }
            else if (ch != '\b')
            {
                printf("%c", ch);
                line[index++] = ch;
            }
        }

        fprintf(fptr, "%s\n", line);
    }
}
