#include "../include/layTopWindow.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam) {
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hwnd, &lpdwProcessId);
    if (lpdwProcessId == lParam) {
        SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        return FALSE;
    }
    return TRUE;
}

bool Genshin::layTopWindow(HANDLE pid) {
    return EnumWindows(EnumWindowsProc, (LPARAM)(pid));
}