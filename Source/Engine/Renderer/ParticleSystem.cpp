#include "ParticleSystem.h"
#include "Renderer/Renderer.h"

using namespace std;
namespace viper {
		
		bool ps::Initialize(int poolSize)
		{
			//reserve particles in pool
			_particles.reserve(poolSize); 
			return true;
		}
		void ps::Shutdown()
		{
			_particles.clear(); 
		}

		void ps::Update(float dt)
		{
			for (auto& particle : _particles) {
				if (particle.active) {
					particle.lifespan -= dt;
					particle.active = (particle.lifespan > 0.0f);
					particle.prevPos = particle.pos; // Store the previous position before updating
					particle.pos += particle.velocity * dt;
				}
			}
		}
		void ps::Draw(class Renderer& renderer)
		{
			for (const auto& particle : _particles) {
				if (particle.active) {
					renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
					renderer.DrawLine(particle.pos.x, particle.pos.y, particle.prevPos.x, particle.prevPos.y);
				}
			}
		}
		void ps::AddParticle(const Particle& particle)
		{
			Particle* ptrParticle = GetFreeParticle();
			if (ptrParticle) {
				*ptrParticle = particle; // Copy the particle data
				ptrParticle->active = true;
				ptrParticle->prevPos = ptrParticle->pos;

			}
		}
		Particle* ps::GetFreeParticle()
		{
			for (auto& particle : _particles) {
				if (!particle.active) return &particle;
				
			}
			return nullptr; // No available particle found
		}
}