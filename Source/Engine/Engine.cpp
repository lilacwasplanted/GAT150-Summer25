#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
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


		return true;
	}

	void Engine::Shutdown() {
		_audio->Shutdown();
		_input->Shutdown();
		_renderer->Shutdown();

	}

	void Engine::Update() {
		_time.Tick();
		_input->Update();
		_audio->Update();
	
	}
	void Engine::Draw()
	{
		//
	}

}

