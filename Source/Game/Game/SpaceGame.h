#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

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
		void Draw(class viper::Renderer& renderer) override;

		void OnPlayerDeath();
	private:
		void SpawnEnemy();


	private:
		GameState _gameState = GameState::Initialize;
		float _enemySpawnTimer = 0.0f;
		float _stateTimer = 0.0f;

		shared_ptr<class Font> _titleFont;
		shared_ptr<class Font> _uiFont;

		unique_ptr<class Text> _titleText;
		unique_ptr<class Text> _scoreText;
		unique_ptr<class Text> _livesText;


	};
