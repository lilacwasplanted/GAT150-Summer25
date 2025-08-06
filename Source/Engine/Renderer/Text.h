#pragma once
#include "Math/Vector3.h"
#include "Renderer.h"
#include "Font.h"
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;	
struct SDL_Texture;


class Text {
public:
	Text() = default;
	Text(Font* font) : _font{ font } {}
	~Text();

	bool Create(viper::Renderer& renderer, const string& text, const viper::vec3& color);
	void Draw(viper::Renderer& renderer, float x, float y);

private:
	Font* _font{ nullptr };
	SDL_Texture* _texture{ nullptr };
};
