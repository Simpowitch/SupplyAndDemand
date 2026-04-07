#pragma once

#include <filesystem>

void LoadSettings();
const std::filesystem::path& GetGameAssetPath();
const std::string ResolveGameAssetPath(const std::string& anAsset);
