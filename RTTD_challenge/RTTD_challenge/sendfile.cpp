#include <Windows.h>
#include "sendfile.h"
#include <winhttp.h>
#include <stdio.h>

#pragma comment(lib, "Winhttp.lib")

void sendfile(BYTE* data, DWORD dataSize) {
    DWORD dwBytesWritten = 0;
    BOOL  bResults = FALSE;
    HINTERNET hSession = NULL;
     HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example Program/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, ACE_SERVER,
            INTERNET_DEFAULT_HTTP_PORT, 0);

    // Create an HTTP Request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"POST",
            L"/writetst.txt",
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            0);

    // Send a Request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0, WINHTTP_NO_REQUEST_DATA, 0,
            dataSize, 0);

    // Write data to the server.
    if (bResults)
        bResults = WinHttpWriteData(hRequest, data,
            dataSize,
            &dwBytesWritten);

    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    // Report any errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());


    // Close any open handles.
    if (hRequest) {
        WinHttpCloseHandle(hRequest);
    }
    if (hConnect) {
        WinHttpCloseHandle(hConnect);
    }
    if (hSession) {
        WinHttpCloseHandle(hSession);
    }
}