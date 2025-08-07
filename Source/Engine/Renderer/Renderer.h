#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>

using namespace std;
namespace viper {

	class Renderer
	{
	public:
		Renderer() {}
		bool Initialize();
		void Shutdown();
		bool CreateWindow(const string& name, int width, int height);

		void Clear();
		void Present();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		void SetColor(float r, float g, float b, float a);

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(float x, float y);


		void DrawTexture(class Texture* texture, float x, float y);
		void DrawTexture(class Texture* texture, float x, float y, float angle = 0, float scale = 1);

	private:
		SDL_Window* _window{ nullptr };
		SDL_Renderer* _renderer{ nullptr };

	private:
	friend class Text;
	friend class Texture;
	};
};