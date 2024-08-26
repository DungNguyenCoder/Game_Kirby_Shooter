
#ifndef TEXT_H_
#define TEXT_H_

#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class Text : public BaseObject
{
public:
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
	};
	Text();
	~Text();

	void SetText(const std::string &text) {str_val_ = text;}
	void SetColor(const int &type);
	void CreateGameText(TTF_Font* font, SDL_Surface *des);
private:
	std::string str_val_;
	SDL_Color text_color_;
};

#endif