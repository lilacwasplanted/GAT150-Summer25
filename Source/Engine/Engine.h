#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Resources/ResourceManager.h"

#include <memory>

#define RENDERER viper::GetEngine().GetRenderer()
#define INPUT viper::GetEngine().GetInput()
#define TIME viper::GetEngine().GetTime()
#define AUDIO viper::GetEngine().GetAudio()

namespace viper {
	class Engine : public Singleton<Engine> {
	public:
		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		AudioSystem& GetAudio() { return *m_audio; }
		InputSystem& GetInput() { return *m_input; }
		ParticleSystem& GetPS() { return *m_particleSystem;  }

		Time& GetTime() { return m_time; }

	private:
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
}
