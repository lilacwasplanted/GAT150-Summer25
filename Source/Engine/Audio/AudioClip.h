#pragma once
#include "Resources/Resource.h"

using namespace std;

namespace viper {
	class AudioClip : public Resource {
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const string& filename, class AudioSystem& audioSystem);

	private:
		friend class AudioSystem;

		FMOD::Sound* m_sound{ nullptr };
	};
}