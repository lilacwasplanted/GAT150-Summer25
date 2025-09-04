#pragma once
#include "Framework/Component.h"

using namespace std;

namespace viper {
	class AudioSource : public Component {
	public:
		string audioClipName;
		
		CLASS_PROTOTYPE(AudioSource)
	public:
		void Update(float dt) override;
		void Play();
	};
}