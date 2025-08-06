#pragma once
#include <string>

using namespace std;

struct TTF_Font;
class Font {
public:
	Font() = default;
	~Font();

	bool Load(const string& name, float fontSize);

private:
	friend class Text;

	TTF_Font* _ttfFont{ nullptr };
};