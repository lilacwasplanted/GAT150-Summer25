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

	// Get current directory path
	cout << "Directory Operations:\n";
	cout << "Current directory: " << file::GetCurrentDirectory() << "\n";

	// Set current directory path (current path + "Assets")
	cout << "Setting directory to 'Assets'...\n";
	viper::file::SetCurrentDirectory("Assets");
	cout << "New directory: " << viper::file::GetCurrentDirectory() << "\n\n";

	// Get filenames in the current directory
	cout << "Files in Directory:\n";
	auto filenames = viper::file::GetFilesInDirectory(viper::file::GetCurrentDirectory());
	for (const auto& filename : filenames) {
		cout << filename << "\n";
	}
	cout << "\n";

	// Get filename (filename.extension) only
	if (!filenames.empty()) {
		cout << "Path Analysis:\n";
		string filename = viper::file::GetFilename(filenames[0]);
		cout << "Filename only: " << filename << "\n";

		// Get extension only
		string ext = viper::file::GetExtension(filenames[0]);
		cout << "Extension: " << ext << "\n\n";
	}

	// Read and display text file
	cout << "Text File Reading:\n";
	string str;
	bool success = viper::file::ReadTextFile("test.txt", str);
	if (success) {
		cout << "Contents of test.txt:\n";
		cout << str << "\n";
	}
	else {
		cout << "Failed to read test.txt\n";
	}

	//Initialize Engine Systems
	viper::GetEngine().Initialize();

	//Create Audio System

	vector<viper::vec2> verts{
	{-4, 1 },
	{ 4, 1 },
	{-3, -4 },
	{0, 4 },
	{3, -4 },
	{-4, 1}
	};

	Font* font = new Font();
	font->Load("Farmshow.ttf", 80);

	Text* text = new Text(font);
	text->Create(RENDERER, "Chihiro", viper::vec3{ 1,1,1 });



	shared_ptr<viper::Model> model = make_shared<viper::Model>(verts, viper::vec3{ 255, 255, 255 });

	viper::Scene scene;
	for (int i = 0; i < 10; i++) {
		viper::Transform transform{ viper::vec2{ ran::getReal() * 1280, ran::getReal() * 1024}, 0.0f, 10.0f };
		unique_ptr<Player> player = make_unique<Player>(transform, model);
		scene.AddActor(move(player));
	}

	//Create Actors
	vector <unique_ptr<viper::Actor>> actors;
	for (int i = 0; i < 10; i++) {
		viper::Transform transform{ viper::vec2{ ran::getReal() * 1280, ran::getReal() * 1024}, 0.0f, 10.0f };
		unique_ptr<Player> player = make_unique<Player>( transform, model);
		actors.push_back(move(player));
	}

	vector<viper::vec2> stars;
	for (int i = 0; i < 100; i++) {
		stars.push_back(viper::vec2{ ran::getReal() * 1280, ran::getReal() * 1024 });
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

		viper::vec2 speeds{ -140.0f, 0.0f };
		float length = speeds.Length();

		for (auto& star : stars) {
			star += speeds * TIME.GetDeltaTime();

			if (star[0] > 1280)  star[0] = 0;
			if (star[0] < 0)  star[0] = 1280;

			RENDERER.SetColor((uint8_t)ran::getInt(256), ran::getInt(256), ran::getInt(256), 255);
			RENDERER.DrawPoint(star.x, star.y);
		}

		RENDERER.Present(); // Render the screen
	}
	viper::GetEngine().Shutdown(); // Shutdown the engine
	return 0;
}