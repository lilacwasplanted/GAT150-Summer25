#pragma once
#include <memory>

namespace viper {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;
		virtual void Shutdown() = 0;

		void AddPoints(int points) { m_score += points; }
		int GetPoints() const { return m_score; }

		void SetLives(int lives) { m_lives = lives; }
		int GetLives() const { return m_lives; }

	protected:
		int m_score{ 0 };
		int m_lives{ 0 };

		std::unique_ptr<class Scene> m_scene;
	};
}