// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <crtdbg.h>

void popScreenshot() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi)); // Setting the startup info and process information to zero, they don't need to have value, they just need to exist, if a NULL was passed it would not work 
    _RPTW0(0, L"Calling screenShot.exe");


    CreateProcess(L"C:\\Windows\\System32\\screenshot.exe", (LPWSTR)L"", NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi); //A lot of these arguments do not matter 
    //This creates the screenshot.exe process 

    CloseHandle(&si);
    CloseHandle(&pi); //Need to free the memory, we don't want to leave handles dangling 
}

BOOL WINAPI DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        _RPTW0(0, L"DLL_PROCESS_ATTACH");
        popScreenshot(); //calls the function to start call, not a good idea to call anything from DLL main. We should export the function
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

