#include "Json.h"
#include "File.h"
#include "Logger.h"

#include <rapidjson/istreamwrapper.h>
#include <iostream>

using namespace std;

namespace viper::json
{
    bool Load(const string& filename, document_t& document) {
        // read the file into a string
        string buffer;
        if (!file::ReadTextFile(filename, buffer)) {
            Logger::Error("Could not read file: {}.", filename);
            return false;
        }


        Logger::Info("JSON: {}", buffer);
        // convert the string into a json stream
        stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);
        // check if the parse was successful
        if (!document.IsObject()) {
            Logger::Error("Could not parse Json: {}.", filename);
            return false;
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, int& data) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
            Logger::Error("Could not read Json value (int): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }

    bool json::Read(const value_t& value, const std::string& name, float& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber()) {
            Logger::Error("Could not read Json value (float): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetFloat();

        return true;
    }

    bool json::Read(const value_t& value, const string& name, string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            Logger::Error("Could not read Json value (string): {}.", name);
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }

    bool Read(const value_t& value, const string& name, bool& data) {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            Logger::Error("Could not read Json value (bool): {}.", name);
            return false;
        }

        // get the data
        data = value[name.c_str()].GetBool();

        return true;
    }

    bool Read(const value_t& value, const string& name, vec2& data) {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
            Logger::Error("Could not read Json value (vec2): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }

    bool json::Read(const value_t& value, const string& name, vec3& data)
    {
        // check if the value has the "<name>" and is an array with 3 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3) {
            Logger::Error("Could not read Json value (vec2): {}.", name);
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++) {
            if (!array[i].IsNumber()) {
                Logger::Error("Could not read Json value: {}.", name);
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
}
