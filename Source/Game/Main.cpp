#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
#include "Framework/Game.h"
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "Math/Math.h"
#include "Core/Time.h"
#include "Core/File.h"
#include "Engine.h"

#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/SpaceGame.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <fmod.hpp>
#include <iostream>
#include <memory>
#include <random> // Add this include directive at the top of the file
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
	viper::file::SetCurrentDirectory("Assests");

	viper::GetEngine().Initialize();

	//initialize Space Game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	vector<viper::vec2> stars;
	for (int i = 0; i < 100; ++i) {
		stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024});
	}

	SDL_Event e;
	bool quit = false;

	//MAIN LOOP HERE--------------------------------------------------------------------------------------
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}
		viper::GetEngine().Update(); // Update the engine time
		game->Update(TIME.GetDeltaTime());

		if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

		//Draw
		viper::vec3 color{ 0, 0, 0 };
		RENDERER.SetColor(color.r, color.g, color.b);			//Background color
		RENDERER.Clear();

		game->Draw(RENDERER);
		RENDERER.Present(); 
	}
	game->Shutdown(); 
	game.release();
	viper::GetEngine().Shutdown(); // Shutdown the engine
	return 0;
}