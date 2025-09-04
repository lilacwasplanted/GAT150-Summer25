#include "Game/SpaceGame.h"
#include "Renderer/Texture.h"

using namespace std;

#define JSON_READ(value, data) viper::json::Read(value, #data, data)

int main(int argc, char* argv[]) {
  viper::file::SetCurrentDirectory("Assets");
  viper::Logger::Info("current directory {}", viper::file::GetCurrentDirectory());

  // load the json data from a file
  string buffer;
  viper::file::ReadTextFile("json.txt", buffer);
  // show the contents of the json file (debug)
  cout << buffer << endl;

  // create json document from the json file contents
  rapidjson::Document document;
  viper::json::Load("json.txt", document);

  // initialize engine
  viper::Logger::Warning("initialize engine ...");
  viper::GetEngine().Initialize();

  // initialize game
  unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
  game->Initialize();

  SDL_Event e;
  bool quit = false;

  // MAIN LOOP
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    //update
    viper::GetEngine().Update();
    game->Update(TIME.GetDeltaTime());

    if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

    // draw
    viper::vec3 color{ 0, 0, 0 };
    RENDERER.SetColor(color.r, color.g, color.b);
    RENDERER.Clear();

    game->Draw(RENDERER);
    //RENDERER.DrawTexture(texture.get(), 30.0f,30.0f,4.0f,45.0f);
    RENDERER.Present();
  }

  game->Shutdown();
  game.release();
  viper::GetEngine().Shutdown();

  return 0;
}
