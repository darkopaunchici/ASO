#include <windows.h>
#include <iostream>

int main()
{
    SC_HANDLE hSCManager = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ENUMERATE_SERVICE
    );

    if (hSCManager == NULL)
    {
        std::cout << "Eroare la deschiderea Service Control Manager.\n";
        return 1;
    }

    DWORD bytesNeeded = 0;
    DWORD servicesReturned = 0;
    DWORD resumeHandle = 0;

    EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        NULL,
        0,
        &bytesNeeded,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    BYTE* buffer = new BYTE[bytesNeeded];

    BOOL success = EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        buffer,
        bytesNeeded,
        &bytesNeeded,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    if (!success)
    {
        std::cout << "Eroare la enumerarea serviciilor.\n";
        delete[] buffer;
        CloseServiceHandle(hSCManager);
        return 1;
    }

    ENUM_SERVICE_STATUS_PROCESS* services =
        (ENUM_SERVICE_STATUS_PROCESS*)buffer;

    std::cout << "Servicii care ruleaza:\n";
    std::cout << "----------------------\n";

    for (DWORD i = 0; i < servicesReturned; i++)
    {
        std::wcout << L"Nume serviciu: "
                   << services[i].lpServiceName << L"\n";

        std::wcout << L"Descriere: "
                   << services[i].lpDisplayName << L"\n\n";
    }

    delete[] buffer;
    CloseServiceHandle(hSCManager);

    return 0;
}