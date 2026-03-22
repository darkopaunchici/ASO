#include <windows.h>
#include <stdio.h>

int main() {
    HKEY hKey;
    LONG result;
    
    const char *subKey = "Software";

    result = RegOpenKeyEx(
        HKEY_CURRENT_USER,  
        subKey,          
        0,
        KEY_READ,
        &hKey
    );

    if (result != ERROR_SUCCESS) {
        printf("Eroare la deschiderea cheii!\n");
        return 1;
    }

    printf("Subcheile din HKEY_CURRENT_USER\\%s:\n\n", subKey);

    DWORD index = 0;
    CHAR name[256];
    DWORD nameSize;

    while (1) {
        nameSize = sizeof(name);

        result = RegEnumKeyEx(
            hKey,
            index,
            name,
            &nameSize,
            NULL,
            NULL,
            NULL,
            NULL
        );

        if (result == ERROR_NO_MORE_ITEMS) {
            break;
        }

        if (result == ERROR_SUCCESS) {
            printf("%s\n", name);
        } else {
            printf("Eroare la enumerare!\n");
            break;
        }

        index++;
    }

    RegCloseKey(hKey);
    return 0;
}
