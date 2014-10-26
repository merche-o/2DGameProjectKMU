#include "TextMenu.h"


TextMenu::TextMenu(float X, float Y, std::string t, int s, int r, int g, int b)
	: x(X), y(Y), text(t), size(s), color(r, g, b)
{
}


TextMenu::~TextMenu(void)
{
}
