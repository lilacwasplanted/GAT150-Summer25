#include "File.h"

namespace viper::file {
    /// <summary>
    /// Retrieves the current working directory as a string.
    /// </summary>
    /// <returns>A string containing the current working directory, or an empty string if an error occurs.</returns>
    std::string GetCurrentDirectory() {
        std::error_code ec;
        auto path = std::filesystem::current_path(ec);
        return ec ? std::string{} : path.string();
    }

    /// <summary>
    /// Sets the current working directory to the specified path.
    /// </summary>
    /// <param name="path">The path to set as the current working directory.</param>
    /// <returns>True if the current directory was successfully set; false otherwise.</returns>
    bool SetCurrentDirectory(const std::string& path) {
        std::error_code ec;
        std::filesystem::current_path(path, ec);

        return !ec;
    }

    /// <summary>
    /// Retrieves the file extension from a given file path.
    /// </summary>
    /// <param name="path">The file path as a string.</param>
    /// <returns>The file extension, including the leading dot, or an empty string if there is no extension.</returns>
    std::string GetExtension(const std::string& path) {
        std::filesystem::path p(path);
        return p.extension().string();
    }

    /// <summary>
    /// Extracts the filename from a given file path.
    /// </summary>
    /// <param name="path">The file path from which to extract the filename.</param>
    /// <returns>The filename component of the specified path as a string.</returns>
    std::string GetFilename(const std::string& path) {
        std::filesystem::path p(path);
        return p.filename().string();
    }

    /// <summary>
    /// Checks whether a file or directory exists at the specified path.
    /// </summary>
    /// <param name="path">The path to the file or directory to check.</param>
    /// <returns>True if the file or directory exists and no error occurred; otherwise, false.</returns>
    bool Exists(const std::string& path) {
        std::error_code ec;
        bool result = std::filesystem::exists(path, ec);

        return !ec && result;
    }

    /// <summary>
    /// Retrieves a list of regular files in the specified directory.
    /// </summary>
    /// <param name="path">The path to the directory to search for files.</param>
    /// <returns>A vector containing the paths of regular files found in the directory. Returns an empty vector if an error occurs.</returns>
    std::vector<std::string> GetFilesInDirectory(const std::string& path) {
        std::vector<std::string> files;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return files; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_regular_file(ec) && !ec) {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }

    /// <summary>
    /// Retrieves a list of directories within the specified path.
    /// </summary>
    /// <param name="path">The path to the directory whose subdirectories are to be listed.</param>
    /// <returns>A vector of strings containing the paths of all subdirectories found in the specified directory. Returns an empty vector if an error occurs.</returns>
    std::vector<std::string> GetDirectoriesIn(const std::string& path) {
        std::vector<std::string> directories;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return directories; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_directory(ec) && !ec) {
                directories.push_back(entry.path().string());
            }
        }

        return directories;
    }

    /// <summary>
    /// Reads the contents of a text file into a string.
    /// </summary>
    /// <param name="path">The path to the text file to be read.</param>
    /// <param name="content">A reference to a string where the file's contents will be stored.</param>
    /// <returns>True if the file was successfully read; false otherwise.</returns>
    bool ReadTextFile(const std::string& path, std::string& content) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return false;
        }

        // read entire file into string
        std::stringstream buffer;
        buffer << file.rdbuf();
        content = buffer.str();

        return true;
    }

    /// <summary>
    /// Writes the specified content to a text file at the given path.
    /// </summary>
    /// <param name="path">The path to the file where the content will be written.</param>
    /// <param name="content">The text content to write to the file.</param>
    /// <returns>True if the file was successfully written; false otherwise.</returns>
    bool WriteTextFile(const std::string& path, const std::string& content, bool append) {
        std::ios::openmode mode = append ? std::ios::app : std::ios::out;
        std::ofstream file(path, mode);
        if (!file.is_open()) {
            return false;
        }

        file << content;

        return true;
    }

    /// <summary>
    /// Reads the contents of a binary file into a vector of bytes.
    /// </summary>
    /// <param name="path">The path to the binary file to read.</param>
    /// <param name="data">A reference to a vector that will be filled with the file's contents.</param>
    /// <returns>True if the file was successfully read; false otherwise.</returns>
    bool ReadBinaryFile(const std::string& path, std::vector<uint8_t>& data) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        // Get file size
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (!file.good()) {
            return false;
        }

        // Resize vector and read file
        data.resize(size);
        file.read(reinterpret_cast<char*>(data.data()), size);

        return true;
    }

    /// <summary>
    /// Writes binary data to a file at the specified path.
    /// </summary>
    /// <param name="path">The path to the file where the data will be written.</param>
    /// <param name="data">The binary data to write to the file.</param>
    /// <returns>True if the file was successfully written; false otherwise.</returns>
    bool WriteBinaryFile(const std::string& path, const std::vector<uint8_t>& data) {
        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }
}



