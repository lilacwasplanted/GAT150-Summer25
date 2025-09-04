#pragma once
#include <fmod.hpp>
#include <string>
#include <map>
using namespace std;

namespace viper {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		bool AddSound(const string& filename, const string& name = "");
		bool PlaySound(const string& name);
		bool PlaySound(class AudioClip& audioClip);

	private:
		static bool CheckFMODResult(FMOD_RESULT result);

	private:
		friend class AudioClip;

		FMOD::System* m_system = nullptr;
		map<string, FMOD::Sound*> m_sounds;
	};

}
