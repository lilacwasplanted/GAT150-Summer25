#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"
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
 namespace ran = viper::random;
 namespace file = viper::file;

int main(int argc, char* argv[]) {
	viper::Scene scene;
	vector <unique_ptr<viper::Actor>> actors;


	//Initialize Engine Systems
	viper::GetEngine().Initialize();
	scene.Update(TIME.GetDeltaTime()); // Draw the scene

	//initialize Space Game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	//Create Audio System


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
		
		//model.Draw(renderer,input.GetMousePos(), 5.0f, 25.0f); // Draw the model at the center of the screen
		scene.Draw(RENDERER);// Draw the scene

		for(auto& actor : actors){
			actor->Draw(RENDERER); // Draw the actor
		}

		text->Draw(RENDERER, 40.0f, 40.0f);

		RENDERER.Present(); // Render the screen
	}
	viper::GetEngine().Shutdown(); // Shutdown the engine
	return 0;
}