#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include <vector>

using namespace std;

namespace viper {
	struct Particle {
		bool active{ false };
		float lifespan{ 1 };
		vec2 prevPos{ 0, 0 };
		vec2 pos{ 0, 0 };
		vec2 velocity{ 0, 0 };
		vec3 color{ 0, 0, 0 };
	};
	class ps {
	public:
		void ParticleSystem() {};
		bool Initialize(int poolSize = 100);
		void Shutdown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();

		vector<Particle> _particles;
		};
}