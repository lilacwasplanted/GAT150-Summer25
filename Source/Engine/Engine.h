#pragma once
#include "Core/Time.h"
#include <memory>
#define RENDERER viper::GetEngine().GetRenderer()
#define INPUT viper::GetEngine().GetInput()
#define TIME viper::GetEngine().GetTime()
using namespace std;

namespace viper {
	class Renderer;
	class as;
	class is;

	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		as& GetAudio() { return *_audio; }
		is& GetInput() { return *_input; }
		Renderer& GetRenderer()  { return *_renderer; }

		Time& GetTime() { return _time; }

	private:
		Time _time;
		unique_ptr<Renderer> _renderer;
		unique_ptr<as> _audio;
		unique_ptr<is> _input;
	};
	Engine& GetEngine();
}