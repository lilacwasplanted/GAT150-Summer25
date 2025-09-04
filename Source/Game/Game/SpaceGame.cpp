#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/Texture.h"

using namespace std;

bool SpaceGame::Initialize()
{
 _scene = make_unique<viper::Scene>(this);

  viper::json::document_t document;
  viper::json::Load("scene.json", document);
 _scene->Read(document);

 _titleText = make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "Farmshow.ttf", 128.0f));
  _scoreText = make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Farmshow.ttf", 48.0f));
  _livesText = make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Farmshow.ttf", 48.0f));


  return true;
}

void SpaceGame::Update(float dt)
{
  switch (_gameState)
  {
  case SpaceGame::GameState::Initialize:
    _gameState = GameState::Title;
    break;

  case SpaceGame::GameState::Title:
    if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
      _gameState = GameState::StartGame;
    }
    break;

  case SpaceGame::GameState::StartGame:
    _score = 0;
    _lives = 3;
    _gameState = GameState::StartRound;
    break;

  case SpaceGame::GameState::StartRound:
  {
   _scene->RemoveAllActors();
   
   auto player = viper::Factory::Instance().Create<viper::Actor>("player");
   _scene->AddActor(move(player));

    _gameState = GameState::Game;
  }
    break;
  case SpaceGame::GameState::Game:
    _enemySpawnTimer -= dt;
    if (_enemySpawnTimer <= 0) {
      _enemySpawnTimer = 2;
      SpawnEnemy();
    }

    break;
  case SpaceGame::GameState::PlayerDead:
	  _stateTimer -= dt;
    if (_stateTimer <= 0) {
      _lives--;
      if (_lives == 0) {
        _gameState = GameState::GameOver;
       _stateTimer = 3;
      }
      else {
        _gameState = GameState::StartRound;
      }
    }
    break;
  case SpaceGame::GameState::GameOver:
   _stateTimer -= dt;
    if (_stateTimer <= 0) {
      _gameState = GameState::Title;
    }
    break;
  default:
    break;
  }

  if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
    viper::GetEngine().GetTime().SetTimeScale(0.15f);
  }
  else {
    viper::GetEngine().GetTime().SetTimeScale(1.0f);
  }

 _scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {
  if (_gameState == GameState::Title) {
 _scene->Draw(renderer);

   _titleText->Create(renderer, "Chihiro", viper::vec3{ 0, 0, 1 });
   _titleText->Draw(renderer, 500, 400);
  }
  if (_gameState == GameState::GameOver) {
   _titleText->Create(renderer, "GAME OVER", viper::vec3{ 1, 0, 0 });
   _titleText->Draw(renderer, 400, 400);
  }

  _scoreText->Create(renderer, "SCORE " + to_string(_score), { 1, 1, 1 });
  _scoreText->Draw(renderer, 20, 20);

  _livesText->Create(renderer, "LIVES " + to_string(_lives), {1, 1, 1});
  _livesText->Draw(renderer, (float)(renderer.GetWidth() - 200), (float)20);

  viper::GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath() {
  _gameState = GameState::PlayerDead;
 _stateTimer = 2;
}

void SpaceGame::SpawnEnemy() {
    viper::Actor* player = _scene->GetActorByName<viper::Actor>("player");
    if (player) {

    // spawn at random position away from player
        viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
        viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 2.0f };

        auto enemy = viper::Instantiate("enemy", transform);
        _scene->AddActor(move(enemy));
    }

	// For Enemy Ship Variation
    //enemy->GetComponent<viper::SpriteRenderer>()->textureName = "otherTexture.png";
}

void SpaceGame::Shutdown() {
  //
}
