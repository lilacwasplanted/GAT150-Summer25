#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"

#include <vector>

bool SpaceGame::Initialize()
{
    _scene = std::make_unique<viper::Scene>();

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
        // create player
        shared_ptr<viper::Model> model = make_shared<viper::Model>(GameData::shipVerts, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{{ RENDERER.GetWidth() * 0.5f, RENDERER.GetHeight() * 0.5f }, 0, 5 };
       unique_ptr<Player> player = make_unique<Player>(transform, model);
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
            _enemySpawnTimer = 4;

            // create enemies
            shared_ptr<viper::Model> enemyModel = make_shared<viper::Model>(GameData::enemyVerts, viper::vec3{ viper::random::getReal(), viper::random::getReal(), viper::random::getReal() });
            viper::Transform transform{ viper::vec2{ viper::random::getReal() * viper::GetEngine().GetRenderer().GetWidth(), viper::random::getReal() * viper::GetEngine().GetRenderer().GetHeight() }, 0, 10 };
            unique_ptr<Enemy> enemy = make_unique<Enemy>(transform, enemyModel);
            enemy->damping = 0.2f;
            enemy->speed = (viper::random::getReal() * 800) + 500;
            enemy->tag = "enemy";
            _scene->AddActor(move(enemy));
        }

        break;
    case SpaceGame::GameState::PlayerDead:
        _lives--;
        if (_lives == 0) _gameState = GameState::GameOver;
        else {
            _gameState = GameState::StartLevel;
        }
        break;
    case SpaceGame::GameState::GameOver:
        break;
    default:
        break;
    }

    _scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw()
{
    _scene->Draw(viper::GetEngine().GetRenderer());
}

void SpaceGame::Shutdown()
{
    //
}