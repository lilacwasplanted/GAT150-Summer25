#pragma once
#include <vector>
#include <memory>


using namespace std;


namespace viper{
	class Scene {
	public: 
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(unique_ptr<class Actor> actor);
		

	private:
		vector<unique_ptr<class Actor>> _actors;
	};
}