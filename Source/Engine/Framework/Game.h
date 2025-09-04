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

		void AddPoints(int points) { _score += points; }
		int GetPoints() const { return _score; }

		void SetLives(int lives) { _lives = lives; }
		int GetLives() const { return _lives; }

	protected:
		int _score{ 0 };
		int _lives{ 0 };

		 unique_ptr<class Scene>_scene;
	};
}