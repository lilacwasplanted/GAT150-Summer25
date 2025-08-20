#include "AudioSystem.h"
#include "AudioClip.h"

namespace viper {
	/// <summary>
	/// Checks if an FMOD operation was successful and logs an error message if it was not.
	/// </summary>
	/// <param name="result">The FMOD_RESULT value returned by an FMOD function call.</param>
	/// <returns>True if the FMOD operation was successful (FMOD_OK); otherwise, false.</returns>
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			Logger::Error("FMOD error {}", FMOD_ErrorString(result));
			return false;
		}

		return true;
	}

	/// <summary>
	/// Initializes the audio system using FMOD.
	/// </summary>
	/// <returns>True if the audio system was successfully initialized; otherwise, false.</returns>
	bool AudioSystem::Initialize() {

		FMOD_RESULT result = FMOD::System_Create(&m_system);
		if (!CheckFMODResult(result)) return false;

		void* extradriverdata = nullptr;
		result = m_system->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}

	/// <summary>
	/// Shuts down the audio system and releases associated resources.
	/// </summary>
	void AudioSystem::Shutdown() {
		CheckFMODResult(m_system->release());
	}

	/// <summary>
	/// Updates the audio system state by processing pending audio operations.
	/// </summary>
	void AudioSystem::Update() {
		CheckFMODResult(m_system->update());
	}

	/// <summary>
	/// Attempts to add a new sound to the audio system from a file, associating it with a specified name or the filename if no name is provided.
	/// </summary>
	/// <param name="filename">The path to the audio file to load.</param>
	/// <param name="name">The name to associate with the loaded sound. If empty, the filename is used as the key.</param>
	/// <returns>Returns false if the sound could not be added (e.g., if the name already exists or loading fails).</returns>
	bool AudioSystem::AddSound(const std::string& filename, const std::string& name)
	{
		std::string key = (name.empty()) ? filename : name;
		key = tolower(key);

		// check if key exists in sounds map
		if (m_sounds.find(key) != m_sounds.end()) {
			Logger::Warning("Audio System : name already exists {}", key);
			return false;
		}

		// create sound from key
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) return false;

		// insert sound into map
		m_sounds[key] = sound;

		return true;
	}

	bool AudioSystem::PlaySound(const std::string& name) {
		std::string key = name;
		key = tolower(key);

		// check if sound exists in sounds map
		if (m_sounds.find(key) == m_sounds.end()) {
			Logger::Warning("Audio System : name doesn exist {}", key);
			return false;
		}

		// play sound from key
		FMOD_RESULT result = m_system->playSound(m_sounds[key], 0, false, nullptr);
		if (!CheckFMODResult(result)) return false;

		return true;
	}

	bool AudioSystem::PlaySound(AudioClip& audioClip) {
		FMOD_RESULT result = m_system->playSound(audioClip.m_sound, 0, false, nullptr);
		if (!CheckFMODResult(result)) return false;

		return true;
	}
}