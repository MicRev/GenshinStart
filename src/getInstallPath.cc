#include "../include/getInstallPath.h"
#include<iostream>
#include<Windows.h>

bool Genshin::getInstallPath(std::filesystem::path& out_path) {

    DWORD type = REG_SZ;
    wchar_t data[256] = {0};
    DWORD datasize = sizeof(data);
    LSTATUS res = RegGetValueW(HKEY_LOCAL_MACHINE, 
                               L"Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\原神",
                               L"InstallPath",
                               RRF_RT_REG_SZ, &type,
                               (LPBYTE)&data, &datasize);
    if (res == ERROR_SUCCESS) {
        out_path = data;
        return true;
    } else {
        std::cout << "ERROR CODE " << res << std::endl;
        return false;
    }
}
