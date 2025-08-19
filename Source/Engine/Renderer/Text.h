#pragma once  
#include "Renderer.h" // Add this include to ensure the Renderer class is fully defined  
#include "Math/Vector3.h"  
#include <string>  

using namespace std;  
struct SDL_Texture;  

namespace viper  
{  
	class Text {  
	public:  
		Text() = default;  
		Text(shared_ptr<class Font> font) : _font{ font } {}  
		~Text();  

		bool Create(viper::Renderer& renderer, const string& text, const viper::vec3& color);  
		void Draw(viper::Renderer& renderer, float x, float y);  

	private:  
		shared_ptr<class Font> _font{ nullptr };  
		SDL_Texture* _texture{ nullptr };  
	};  
}
