#include "../include/screenshot.h"
#include "../include/getInstallPath.h"
#include "../include/getGamePath.h"
#include "../include/startGenshinProcess.h"
#include "../include/layTopWindow.h"

#include<iostream>
#include<fstream>
#include<string>
#include<filesystem>

#include <Mmsystem.h>
#include <mciapi.h>

namespace Genshin
{
    typedef int StartStatus;
    const StartStatus START_FAILED = 1;
    const StartStatus START_SUCCESS = 0;
} // namespace Genshin

void playMusic() {
    PlaySound("./start.wav", NULL, SND_ASYNC);
}

Genshin::StartStatus startGenshin() {

    std::filesystem::path install_path;

    if (!Genshin::getInstallPath(install_path)) {
        std::cout << "原神，找不到在哪！" << std::endl;
        return Genshin::START_FAILED;
    }

    std::filesystem::path genshin_path, genshin_name;

    if (!Genshin::getGamePath(install_path, genshin_path, genshin_name)) {
        std::cout << "原神，文件损坏！" << std::endl;
        return Genshin::START_FAILED;
    }

    STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

    playMusic();

    if (!Genshin::startGenshinProcess(genshin_path, genshin_name, si, pi)) {
        std::cout << "原神，启动失败！" << std::endl;
        return Genshin::START_FAILED;
    }

    std::cout << "原神，启动！！！" << std::endl;
    std::cout << "不要关闭此窗口。" << std::endl;

    WaitForInputIdle(pi.hProcess, INFINITE);  // wait for starting

    Genshin::layTopWindow(pi.hProcess);

    WaitForSingleObject(pi.hProcess, INFINITE);  // wait for ending

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    if (si.hStdInput != nullptr)
        CloseHandle(si.hStdInput);
    if (si.hStdOutput != nullptr)
        CloseHandle(si.hStdOutput);
    if (si.hStdError != nullptr)
        CloseHandle(si.hStdError);

    return Genshin::START_SUCCESS;
}

bool isAlmostWhite(cv::Mat img) {

    const int tot_pixels = img.rows * img.cols;
    int white_pixels = 0;

    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            auto cur_pixel = img.at<cv::Vec3b>(i, j);
            if (
                cur_pixel[0] >= 230 &&
                cur_pixel[1] >= 230 &&
                cur_pixel[2] >= 230
            ) {
                white_pixels++;
            }
        }
    }

    return white_pixels >= 0.8 * tot_pixels;

}

int main() {

    Screenshot screenshot;
    
    while(true) {
        std::cout << "原神准备启动！" << std::endl;
        cv::Mat img = screenshot.getScreenshot();
        if (isAlmostWhite(img)) {
            img.release();
            break;
        }
        img.release();
        Sleep(250);
    }

    if (startGenshin() == Genshin::START_SUCCESS) {
        std::cout << "原神似了。" << std::endl;
    }
    getchar();

    return 0;
}