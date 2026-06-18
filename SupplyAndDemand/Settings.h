#pragma once

#include <filesystem>
#include <string>

namespace settings 
{
	void LoadSettings();
	const std::filesystem::path& GetGameAssetPath();
	const std::string ResolveGameAssetPath(const std::string& anAsset);
	const std::string GetApplicationName();
	const std::pair<unsigned int, unsigned int> GetResolution();
}

