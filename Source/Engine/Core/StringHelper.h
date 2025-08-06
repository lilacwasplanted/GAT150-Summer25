#pragma once
#include <string>

using namespace std;

namespace viper {
	/// <summary>
	/// Converts all characters in a string to lowercase.
	/// </summary>
	/// <param name="str">The input string to convert</param>
	/// <returns>A new string with all characters converted to lowercase.</returns>
	inline string toLower(const string str){
		string result = str;
		for (char& c : result) {
			c = tolower(c);
		}
		return result;
	}
/// <summary>
/// Converts All Characters In A String To Uppercase.
/// </summary>
/// <param name="str">The input string to convert</param>
/// <returns>A new string with all characters converted to uppercase.</returns>
	inline string toUpper(const string str){
		string result = str;
		for (char& c : result) {
			c = toupper(c);
		}
		return result;
	}
}