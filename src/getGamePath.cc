#include "../include/getGamePath.h"

#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>

bool Genshin::getGamePath(std::filesystem::path& install_path, 
                          std::filesystem::path& game_path,
                          std::filesystem::path& game_name) {

                            std::ifstream ifs;
                            ifs.open(install_path / "config.ini");
                            std::string str;
                            std::getline(ifs, str);
                            if (str != "[launcher]") {
                                return false;
                            }

                            while (std::getline(ifs, str)) {
                                if (str.find("game_install_path") == std::string::npos &&
                                    str.find("game_start_name") == std::string::npos)
                                    continue;
                                
                                if (str.find("game_install_path") != std::string::npos)
                                    game_path = str.substr(str.find_first_of("=")+1);

                                if (str.find("game_start_name") != std::string::npos)
                                    game_name = str.substr(str.find_first_of("=")+1);

                            }

                            ifs.close();

                            return true;
                          }