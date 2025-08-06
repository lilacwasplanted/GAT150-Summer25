#include "AudioSystem.h"
#include "../Core/StringHelper.h"
#include <fmod_errors.h>
#include <iostream>

using namespace std;
namespace viper {
	/// <summary>
	/// Checks if an FMOD operation was successful and logs an error message if it was not.
	/// </summary>
	/// <param name="result">The FMOD_RESULT vaule returned by an FMOD function call.</param>
	/// <returns>True if the FMOD operation was successful (FMOD_OK); otherwise, false.</returns>
	bool as::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			cerr << FMOD_ErrorString(result) << endl;
			return true;
		}
	}
		/// <summary>
		/// Initializes the audio system using FMOD.
		/// </summary>
		/// <returns>True if the audio system was successfully initilalized; otherwise false. </returns>
		bool as::Initialize() {
			FMOD_RESULT result = FMOD::System_Create(&_system);
			if (!CheckFMODResult(result)) return false;
			
			void* extradriverdata = nullptr;
			result = _system->init(32, FMOD_INIT_NORMAL, extradriverdata);
			if (!CheckFMODResult(result)) return false;


			return true;
		}
		/// <summary>
		/// Shuts down the audio system and releases associated resources.
		/// </summary>
		void as::Shutdown() {
			FMOD_RESULT result = _system->release();
			CheckFMODResult(result);
		}
		/// <summary>
		/// Updates the audio system by processing pending audio operations.
		/// </summary>
		void as::Update() {
			CheckFMODResult(_system->update());
		}
		/// <summary>
		/// Attempst to add a new sound to the audio system from a file, associating it with a specified name
		/// </summary>
		/// <param name="filename">The part to the audio to load.</param>
		/// <param name="name">The name to associaate with the loaded sound. If empty, the filename is used</param>
		/// <returns>Returns false if the sound could not be added (e.g., if the name already exists or load)</returns>
		bool as::AddSound(const string& filename, const string& name)
		{
			string key = (name.empty()) ? filename : name;
			key = toLower(key);

			//Check If Key Exists In Sounds Map
			if (_sounds.find(key) != _sounds.end()) {
				cerr << "Audio System: Name Already Exists - " << key << endl;
				return false;
			}
			//Create Sound From Key
			FMOD::Sound* sound = nullptr;
			FMOD_RESULT result = _system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			if (!CheckFMODResult(result)) return false;

			//Insert Sound Into Map
			_sounds[key] = sound;

			return true;
		}

		bool as::PlaySound(const string& name)
		{
			string key = name;
			//convert to lowercase
			for (char& c : key) {
				c = tolower(c);
			}

			//Check If Sound Exists In Sound Map
			if (_sounds.find(name) == _sounds.end()) {
				cerr << "Audio System : Name Does Not Exist -  " << key << endl;
				return false;
			}
			//Play Sound From Key
			FMOD_RESULT result = _system->playSound(_sounds[key], 0, false, nullptr);
			if (!CheckFMODResult(result)) return false;
			return true;
		}


}