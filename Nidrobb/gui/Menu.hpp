#ifndef MENU_HPP
#define MENU_HPP

//Représente un menu
class Menu
{
protected:
	int m_fontSize;
    string m_fontPath;
    SDL_Color m_colorHover;
    SDL_Color m_colorNormal;

public:
	Menu();
	~Menu();
	
};

#endif