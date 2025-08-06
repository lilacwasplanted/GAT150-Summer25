#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

using namespace std;
namespace viper {
	class as {

	public:

		void AudioSystem() {};

		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const string& filename, const string& name = "");
		bool PlaySound(const string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);

	private:

		FMOD::System* _system = nullptr;
		map<string, FMOD::Sound*> _sounds;

	};
}