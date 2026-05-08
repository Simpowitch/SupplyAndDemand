#pragma once
#include <string_view>
#include <cstdint>

constexpr uint64_t FNV_OFFSET_BASIS = 14695981039346656037ull;
constexpr uint64_t FNV_PRIME = 1099511628211ull;

constexpr uint64_t HashString(const std::string_view& str)
{
    uint64_t hash = FNV_OFFSET_BASIS;

    for (char c : str)
    {
        hash ^= static_cast<uint64_t>(c);
        hash *= FNV_PRIME;
    }

    return hash;
}

