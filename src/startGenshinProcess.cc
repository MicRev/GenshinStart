#include "../include/startGenshinProcess.h"

bool Genshin::startGenshinProcess(std::filesystem::path& genshin_path,
                                  std::filesystem::path& genshin_name,
                                  STARTUPINFOW& si, PROCESS_INFORMATION& pi) {

                                    BOOL res_process = CreateProcessW(
                                        (genshin_path / genshin_name).c_str(),
                                        NULL,
                                        NULL,
                                        NULL,
                                        FALSE,
                                        NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP,
                                        NULL,
                                        genshin_path.c_str(),
                                        &si,
                                        &pi);

                                    if (!res_process) {
                                        printf("CreateProcess failed (%d).\n", GetLastError());
                                        return false;
                                    }

                                    return true;
                                  }