#include "Texture.h"
#include "Renderer.h"

namespace viper {
  Texture::~Texture() {
    // if texture exists, destroy texture
    if (m_texture) SDL_DestroyTexture(m_texture);
  }

  bool Texture::Load(const string& filename, Renderer& renderer) {
    // load image onto surface
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) {
      Logger::Error("Could not load image: {}", filename);
      return false;
    }

    // create texture from surface, texture is a friend class of renderer
    m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
    // once texture is created, surface can be freed up
    SDL_DestroySurface(surface);
    if (!m_texture) {
      Logger::Error("Could not create texture: {}", filename);
      return false;
    }

    return true;
  }

  vec2 Texture::GetSize() {
    // query the texture for the size
    float w, h;
    SDL_GetTextureSize(m_texture, &w, &h);

    return vec2{ w, h };
  }
}