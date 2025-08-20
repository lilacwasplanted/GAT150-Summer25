#pragma once
#include <filesystem>

namespace viper::file {
    std::string GetCurrentDirectory();
    bool SetCurrentDirectory(const std::string& path);
    std::string GetExtension(const std::string& path);
    std::string GetFilename(const std::string& path);
    bool Exists(const std::string& path);

    std::vector<std::string> GetFilesInDirectory(const std::string& path);
    std::vector<std::string> GetDirectoriesIn(const std::string& path);

    bool ReadTextFile(const std::string& path, std::string& content);
    bool WriteTextFile(const std::string& path, const std::string& content, bool append = false);
    bool ReadBinaryFile(const std::string& path, std::vector<uint8_t>& data);
    bool WriteBinaryFile(const std::string& path, const std::vector<uint8_t>& data);
}
