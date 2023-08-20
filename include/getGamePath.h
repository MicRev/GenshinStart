#include<filesystem>

namespace Genshin
{
    bool getGamePath(std::filesystem::path& install_path, 
                     std::filesystem::path& game_path,
                     std::filesystem::path& game_name);
} // namespace Genshin
