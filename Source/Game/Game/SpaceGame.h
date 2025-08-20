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
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer{ 0 };
	float m_stateTimer{ 0 };
	
	std::unique_ptr<class viper::Text> m_titleText;
	std::unique_ptr<class viper::Text> m_scoreText;
	std::unique_ptr<class viper::Text> m_livesText;
};
