#pragma once  
#include <string>  
#include <SDL3_ttf/SDL_ttf.h> // Add this include to resolve the incomplete type issue  

using namespace std;  

struct TTF_Font;  
namespace viper {  
	class Font {  
	public:  
		Font() = default;  
		~Font();  

		bool Load(const string& name, float fontSize);  

	private:  
		friend class Text;  

		TTF_Font* _ttfFont{ nullptr };  
	};  
}