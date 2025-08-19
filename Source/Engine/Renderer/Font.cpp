#include <iostream>
#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

using namespace std;
namespace viper {
	Font::~Font() {
		if (_ttfFont != nullptr) {
			TTF_CloseFont(_ttfFont);
		}
	}

	bool Font::Load(const string& name, float fontSize) {
		_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (_ttfFont == nullptr) {
			cerr << "Could not load font: " << name << endl;
			return false;
		}

		return true;
	}
}