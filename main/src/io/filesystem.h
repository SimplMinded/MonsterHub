#pragma once

#include <cstddef>

namespace monster_hub {

extern char PATH_SEPARATOR_CHAR;

bool dirname(char* result, size_t resultSize, const char* path);

bool mkdir(const char* path);
bool rmdir(const char* path);
bool chdir(const char* path);

} // namespace monster_hub

