#pragma once
#include <filesystem>
#include <string>

namespace afro
{
	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);
	bool setFilePath(const std::filesystem::path& path);
	std::string getFilePath();
	std::string getFileName(const std::filesystem::path& path);
}