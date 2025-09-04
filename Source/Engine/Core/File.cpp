#include "File.h"

namespace viper::file {
  /// <summary>
  /// Retrieves the current working directory as a string.
  /// </summary>
  /// <returns>A string containing the current working directory, or an empty string if an error occurs.</returns>
   string GetCurrentDirectory() {
     error_code ec;
    auto path = filesystem::current_path(ec);
    return ec ? string{} : path.string();
  }

  /// <summary>
  /// Sets the current working directory to the specified path.
  /// </summary>
  /// <param name="path">The path to set as the current working directory.</param>
  /// <returns>True if the current directory was successfully set; false otherwise.</returns>
  bool SetCurrentDirectory(const string& path) {
     error_code ec;
     filesystem::current_path(path, ec);

    return !ec;
  }

  /// <summary>
  /// Retrieves the file extension from a given file path.
  /// </summary>
  /// <param name="path">The file path as a string.</param>
  /// <returns>The file extension, including the leading dot, or an empty string if there is no extension.</returns>
   string GetExtension(const string& path) {
     filesystem::path p(path);
    return p.extension().string();
  }

  /// <summary>
  /// Extracts the filename from a given file path.
  /// </summary>
  /// <param name="path">The file path from which to extract the filename.</param>
  /// <returns>The filename component of the specified path as a string.</returns>
   string GetFilename(const string& path) {
     filesystem::path p(path);
    return p.filename().string();
  }

  /// <summary>
  /// Checks whether a file or directory exists at the specified path.
  /// </summary>
  /// <param name="path">The path to the file or directory to check.</param>
  /// <returns>True if the file or directory exists and no error occurred; otherwise, false.</returns>
  bool Exists(const string& path) {
     error_code ec;
    bool result = filesystem::exists(path, ec);

    return !ec && result;
  }

  /// <summary>
  /// Retrieves a list of regular files in the specified directory.
  /// </summary>
  /// <param name="path">The path to the directory to search for files.</param>
  /// <returns>A vector containing the paths of regular files found in the directory. Returns an empty vector if an error occurs.</returns>
   vector< string> GetFilesInDirectory(const string& path) {
     vector< string> files;
     error_code ec;

    auto iter = filesystem::directory_iterator(path, ec);
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
   vector< string> GetDirectoriesIn(const string& path) {
     vector< string> directories;
     error_code ec;

    auto iter = filesystem::directory_iterator(path, ec);
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
  bool ReadTextFile(const string& path, string& content) {
     ifstream file(path);
    if (!file.is_open()) {
      return false;
    }

    // read entire file into string
     stringstream buffer;
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
  bool WriteTextFile(const string& path, const string& content, bool append) {
     ios::openmode mode = append ? ios::app : ios::out;
     ofstream file(path, mode);
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
  bool ReadBinaryFile(const string& path, vector<uint8_t>& data) {
     ifstream file(path, ios::binary);
    if (!file.is_open()) {
      return false;
    }

    // Get file size
    file.seekg(0, ios::end);
    size_t size = file.tellg();
    file.seekg(0, ios::beg);

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
  bool WriteBinaryFile(const string& path, const vector<uint8_t>& data) {
     ofstream file(path, ios::binary);
    if (!file.is_open()) {
      return false;
    }

    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    return true;
  }
}



