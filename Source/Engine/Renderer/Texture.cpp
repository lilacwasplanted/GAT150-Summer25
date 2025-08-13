#include "Texture.h"
#include "Renderer.h"
#include <iostream>

namespace viper
{


	Texture::~Texture()
	{
		// if texture exists, destroy texture
		if (_texture != NULL) SDL_DestroyTexture(_texture);
	}

	bool Texture::Load(const string& filename, Renderer& renderer)
	{
		// load image onto surface  
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (surface == NULL)
		{
			std::cerr << "Could not load image: " << filename << std::endl;
			return false;
		}

		// create texture from surface, texture is a friend class of renderer  
		//_texture = SDL_CreateTextureFromSurface(renderer, surface);
		// once texture is created, surface can be freed up  
		SDL_DestroySurface(surface);
		if (_texture == NULL)
		{
			cerr << "Could not create texture: " << filename << endl;
			return false;
		}

		return true;
	}

	viper::vec2 Texture::GetSize()
	{
		float w, h;
		if (_texture != nullptr) {
			SDL_GetTextureSize(_texture, &w, &h);
		}
		return viper::vec2(w, h);

	}
}