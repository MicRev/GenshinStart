#include<Windows.h>
#include<filesystem>

namespace Genshin
{
    bool startGenshinProcess(std::filesystem::path& genshin_path,
                             std::filesystem::path& genshin_name,
                             STARTUPINFOW& si, PROCESS_INFORMATION& pi);
} // namespace Genshin
