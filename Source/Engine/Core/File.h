#pragma once
#include <filesystem>

namespace viper::file {
   string GetCurrentDirectory();
  bool SetCurrentDirectory(const string& path);
   string GetExtension(const string& path);
   string GetFilename(const string& path);
  bool Exists(const string& path);

   vector< string> GetFilesInDirectory(const string& path);
   vector< string> GetDirectoriesIn(const string& path);

  bool ReadTextFile(const string& path, string& content);
  bool WriteTextFile(const string& path, const string& content, bool append = false);
  bool ReadBinaryFile(const string& path, vector<uint8_t>& data);
  bool WriteBinaryFile(const string& path, const vector<uint8_t>& data);
}
