#pragma once

#include <string>
#include <vector>

using namespace std;

namespace viper::file {
        string GetCurrentDirectory();
        bool SetCurrentDirectory(const string& path);
        string GetExtension(const string& path);
        string GetFilename(const string& path);
        bool Exists(const string& path);

        vector<string> GetFilesInDirectory(const string& path);
        vector<string> GetDirectoriesIn(const string& path);

        bool ReadTextFile(const string& path, string& content);
        bool WriteTextFile(const string& path, const string& content, bool append = false);
 }