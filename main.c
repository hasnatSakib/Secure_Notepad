#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "user_interface.h"

// Ensure notes directory exists
void ensureNotesDirectoryExists() {
    // Create base notes directory if it doesn't exist
    _mkdir("notes");
}

int main()
{
    // Create base notes directory
    ensureNotesDirectoryExists();

    // Main application loop
    while(1)
    {
        firstMenu();
    }
    return 0;
}
