#include "File.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;
namespace fs = std::filesystem;

namespace viper::file
{


        string GetCurrentDirectory() {
            error_code ec;
            auto path = fs::current_path(ec);
            return ec ? string{} : path.string();
        }

        bool SetCurrentDirectory(const string& path) {
            error_code ec;
            fs::current_path(path, ec);

            return !ec;
        }

        string GetExtension(const string& path) {
            fs::path p(path);
            return p.extension().string();
        }

        string GetFilename(const string& path) {
            fs::path p(path);
            return p.stem().string();
        }

        bool Exists(const string& path) {  
            error_code ec;  
            bool result = fs::exists(path, ec); 
            return !ec && result;  
        }

        vector<string> GetFilesInDirectory(const string& path) {
            vector<string> files;
            error_code ec;

            auto iter = fs::directory_iterator(path, ec);
            if (ec) return files; // return empty vector on error

            for (const auto& entry : iter) {
                if (entry.is_regular_file(ec) && !ec) {
                    files.push_back(entry.path().string());
                }
            }

            return files;
        }

        vector<string> GetDirectoriesIn(const string& path) {
            vector<string> directories;
            error_code ec;

            auto iter = fs::directory_iterator(path, ec);
            if (ec) return directories; // return empty vector on error

            for (const auto& entry : iter) {
                if (entry.is_directory(ec) && !ec) {
                    directories.push_back(entry.path().string());
                }
            }

            return directories;
        }

        bool ReadTextFile(const string& path, string& content) {
            ifstream file(path);
            if (!file.is_open()) {
                cerr << "Error: Could not open the file.\n";
                return false;

            }

            // read entire file into string
            stringstream buffer;

            buffer << file.rdbuf();  // Read file contents into stringstream
            content = buffer.str();  // Convert stringstream to string

            file.close();
            return true;
        }

        bool WriteTextFile(const string& path, const string& content, bool append) {
            ios::openmode mode = append ? ios::app : ios::out;
            ofstream file(path, mode);
            if (!file.is_open()) {
                return false;
            }

            // Write content to file
            file << content;

            // Check if write operation was successful
            if (file.fail()) {
                return false;
            }

			// Close the file
			file.close();
            return true;
        }
   
}