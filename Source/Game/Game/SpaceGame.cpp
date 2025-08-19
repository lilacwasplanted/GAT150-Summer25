#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include <vector>
using namespace std;


bool SpaceGame::Initialize()
{
    _scene = make_unique<viper::Scene>(this);

    _titleFont = make_shared<viper::Font>();
    _titleFont->Load("Farmshow.ttf", 32);

	_uiFont = make_shared<viper::Font>();
	_uiFont->Load("Farmshow.ttf", 16);

	_titleText = make_unique<viper::Text>(_titleFont);
	_scoreText = make_unique<viper::Text>(_uiFont);
	_livesText = make_unique<viper::Text>(_uiFont);

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
        if (INPUT.GetKeyPressed(SDL_SCANCODE_SPACE)) {
            _gameState = GameState::Start;
        }
        break;

    case SpaceGame::GameState::Start:
        _score = 0;
        _lives = 3;
        _gameState = GameState::StartLevel;
        break;

    case SpaceGame::GameState::StartLevel:
    {
		_scene->RemoveAllActors();
        // create player
        shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{{ RENDERER.GetWidth() * 0.5f, RENDERER.GetHeight() * 0.5f }, 0, 5 };
       auto player = make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        _scene->AddActor(std::move(player));
        _gameState = GameState::Game;
    }
    break;
    case SpaceGame::GameState::Game:
        _enemySpawnTimer -= dt;
        if (_enemySpawnTimer <= 0) {
            _enemySpawnTimer = 3;
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
            _gameState = GameState::StartLevel;

        }
		}
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }
    if (INPUT.GetKeyDown(SDL_SCANCODE_Q)) {
		TIME.SetTimeScale(0.5f);
    }
    else {
		TIME.SetTimeScale(1.0f);
    }
        _scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
    if (_gameState == GameState::Title)
    {
        _titleText->Create(renderer, "LVNDR", viper::vec3{ 1, 1, 1 });
        _titleText->Draw(renderer, 400, 400);
	}
    if (_gameState == GameState::GameOver)
    {
        _titleText->Create(renderer, "GMOVR", viper::vec3{ 1, 1, 1 });
        _titleText->Draw(renderer, 400, 400);
	}
	_scoreText->Create(renderer, "Score: " + to_string(_score),{ 1, 1, 1 });
    _scoreText->Draw(renderer, 20, 20);

    _livesText->Create(renderer,"Lives: " + to_string(_lives), {1, 1, 1});
	_livesText->Draw(renderer, (float)(renderer.GetWidth() - 200) , 20.0f);
    
    _scene->Draw(renderer);

	viper::GetEngine().GetParticle().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
	_gameState = GameState::PlayerDead;
    _stateTimer = 2;

}

void SpaceGame::SpawnEnemy()
{
	Player* player = _scene->GetActorByName<Player>("player");
    if (player) {
    // create enemies

    shared_ptr<viper::Model> enemyModel = make_shared<viper::Model>(GameData::enemyVerts, viper::vec3{ 1,0,0 });

	viper::vec2 position = player->transform.pos + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
    viper::Transform transform{ position, viper::random::getReal(0.0f, 360.0f), 10};
    
    unique_ptr<Enemy> enemy = make_unique<Enemy>(transform, enemyModel);
    enemy->damping = 0.2f;
    enemy->fireTime = 2;
    enemy->fireTimer = 5;
    enemy->speed = (viper::random::getReal() * 200) + 300;
    enemy->tag = "enemy";
    _scene->AddActor(move(enemy));
    }
}

void SpaceGame::Shutdown()
{
    //
}