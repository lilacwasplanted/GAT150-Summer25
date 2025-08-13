using namespace std;
#pragma once
#include <memory>


using namespace std;

namespace viper {
	class Game {
		public:
		Game() = default;
		
		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Draw() = 0;
		virtual void Update(float dt) = 0;

		protected:
			int _score{ 0 };
			int _lives{ 0 };
		unique_ptr<class Scene> _scene;
	};
}