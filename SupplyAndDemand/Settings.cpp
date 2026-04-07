#include "Settings.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include <windows.h>

namespace settings
{
    static std::filesystem::path GAME_ASSET_PATH;
    static std::filesystem::path EXECUTABLE_PATH;
}

std::filesystem::path GetExecutableFolder()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::filesystem::path exePath(buffer);
    return exePath.parent_path(); // folder containing the exe
}

void LoadSettings()
{
    settings::EXECUTABLE_PATH = GetExecutableFolder();
    settings::GAME_ASSET_PATH = std::filesystem::current_path();
}

const std::filesystem::path& GetGameAssetPath()
{
    return settings::GAME_ASSET_PATH;
}

const std::string ResolveGameAssetPath(const std::string& assetPath)
{
	if (std::filesystem::exists(settings::GAME_ASSET_PATH / assetPath))
	{
		return (settings::GAME_ASSET_PATH / assetPath).string();
	}
	return "";
}
