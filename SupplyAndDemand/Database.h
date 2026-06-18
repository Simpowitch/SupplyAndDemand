#pragma once
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Settings.h"
#include <json.hpp>
#include "Hasher.h"

template<typename Type>
class Database
{
public:
	void Load(const std::string& path)
	{
		elements.clear();

		std::string fullPath = settings::ResolveGameAssetPath(path);

		if (!std::filesystem::exists(fullPath))
		{
			std::cerr << "Database loading: path/directory does not exist: " << path << std::endl;
			return;
		}

		for (const auto& entry : std::filesystem::directory_iterator(fullPath))
		{
			if (!entry.is_regular_file())
				continue;

			if (entry.path().extension() != ".json")
				continue;

			auto filePath = entry.path();

			std::ifstream file(filePath);
			if (!file.is_open())
				continue;

			std::stringstream buffer;
			buffer << file.rdbuf();
			std::string content = buffer.str();
			if (content.empty())
			{
				continue;
			}

			nlohmann::json j = nlohmann::json::parse(content);

			elements.emplace(HashString(j["id"]), Type(j));
		}
	}

	const Type* TryGetElement(uint64_t id) const
	{
		auto it = elements.find(id);
		if (it == elements.end())
		{
			return nullptr;
		}
		return &it->second;
	}

private:
	std::unordered_map<uint64_t, Type> elements;
};

