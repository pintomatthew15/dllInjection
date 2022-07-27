#pragma once
#include <Windows.h>
#include <iostream>

void take_screenshot(const WCHAR* filename);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);