#pragma once
#include "Framework/Game.h"

using namespace std;

	class SpaceGame : public viper::Game {
	public:
		enum GameState {
			Initialize,
			Title,
			Start,
			StartLevel,
			Game,
			PlayerDead,
			GameOver,
		};
	public:
		SpaceGame() = default;

		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw();

	private:
		GameState _gameState = GameState::Initialize;
		float _enemySpawnTimer = 0.0f;

	};
