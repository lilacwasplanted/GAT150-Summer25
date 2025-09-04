#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public viper::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
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
	float _enemySpawnTimer{ 0 };
	float _stateTimer{ 0 };
	
	 unique_ptr<class viper::Text>_titleText;
	 unique_ptr<class viper::Text> _scoreText;
	 unique_ptr<class viper::Text> _livesText;
};
