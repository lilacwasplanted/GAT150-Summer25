#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
namespace viper
{
	Engine& GetEngine()
	{
		static Engine engine;
		return engine;
	}
	bool Engine::Initialize() {
		_renderer = make_unique<Renderer>();
		_renderer->Initialize();
		_renderer->CreateWindow("Viper Engine", 1280, 1024);

		_input = make_unique<is>();
		_input->Initialize();

		_audio = make_unique<as>();
		_audio->Initialize();

		_particleSystem = make_unique<ps>();
		_particleSystem->Initialize(5000);

		return true;
	}

	void Engine::Shutdown() {
		_particleSystem->Shutdown();
		_audio->Shutdown();
		_input->Shutdown();
		_renderer->Shutdown();

	}

	void Engine::Update() {
		_time.Tick();
		_input->Update();
		_audio->Update();
		_particleSystem->Update(_time.GetDeltaTime());
	
	}

	void Engine::Draw()
	{
		//
	}

}

