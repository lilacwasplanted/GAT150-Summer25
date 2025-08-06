#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include "Font.h"
#include "Text.h"
#include "Renderer.h"
#include "Math/Vector3.h"
using namespace std;


Text::~Text() {
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
	}
};

bool Text::Create(viper::Renderer& renderer, const string& text, const viper::vec3& color) {
	// create a surface using the font, text string and color
	SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(_font->_ttfFont, text.c_str(), text.size(), c);
	if (surface == nullptr) {
		cerr << "Could not create surface.\n";
		return false;
	}

	// create a texture from the surface, only textures can render to the renderer
	_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
	if (_texture == nullptr) {
		SDL_DestroySurface(surface);
		cerr << "Could not create texture" << SDL_GetError() << endl;
		return false;
	}

	// free the surface, no longer needed after creating the texture
	SDL_DestroySurface(surface);

	return true;
}

void Text::Draw(viper::Renderer& renderer, float x, float y) {
	// get the texture width and height
	float width, height;
	bool success = SDL_GetTextureSize(_texture, &width, &height);
	assert(success);

	// set the texture into the renderer at rect 
	SDL_FRect rect{ x, y, width, height };
	success = SDL_RenderTexture(renderer._renderer, _texture, NULL, &rect);
	assert(success);
}